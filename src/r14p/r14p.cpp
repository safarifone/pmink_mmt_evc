#include <iostream>
#include <r14p.h>
#include <sctp.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>

// R14PCallbackArgs
r14p::R14PCallbackArgs::R14PCallbackArgs(){
	arg_count = 0;
	args = NULL;
}

r14p::R14PCallbackArgs::R14PCallbackArgs(void* _args, int _arg_count){
	arg_count = _arg_count;
	args = _args;
}

// R14PCallbackMethod
r14p::R14PCallbackMethod::R14PCallbackMethod(){}

r14p::R14PCallbackMethod::~R14PCallbackMethod(){}

void r14p::R14PCallbackMethod::run(R14PCallbackArgs* args){}

// R14PCallbackHandler
r14p::R14PCallbackHandler::R14PCallbackHandler(){

}

r14p::R14PCallbackHandler::~R14PCallbackHandler(){
	callback_map.clear();

}

void r14p::R14PCallbackHandler::set_callback(R14PEventType type, R14PCallbackMethod* method){
	callback_map[type] = method;
}

void r14p::R14PCallbackHandler::remove_callback(R14PEventType type){
	callback_map.erase(type);

}

void r14p::R14PCallbackHandler::clear(){
	callback_map.clear();
}

void r14p::R14PCallbackHandler::process_callback(R14PEventType type, R14PCallbackArgs* args){
	// find callback
	std::map<R14PEventType, R14PCallbackMethod*>::iterator it = callback_map.find(type);
	// check if found
	if(it != callback_map.end()){
		// run callback
		it->second->run(args);
	}


}

// R14PPayload
r14p::R14PPayload::R14PPayload(){
	raw_data = NULL;
	raw_data_length = 0;
	extra_data = NULL;
	sctp_sid = 0;
	r14p_stream_type = R14P_ST_UNKNOWN;
	client = NULL;
}

r14p::R14PPayload::~R14PPayload(){

}


void r14p::R14PPayload::process_callback(R14PEventType type, R14PCallbackArgs* args){
	callback_handler.process_callback(type, args);
}

void r14p::R14PPayload::remove_callback(R14PEventType callback_type){
	callback_handler.remove_callback(callback_type);

}

void r14p::R14PPayload::clear_callbacks(){
	callback_handler.clear();
}

void r14p::R14PPayload::set_callback(R14PEventType callback_type, R14PCallbackMethod* callback_method){
	callback_handler.set_callback(callback_type, callback_method);
}


// R14PClient
void r14p::R14PClient::init(){
	memset(end_point_address, 0, 16);
	memset(local_point_address, 0, 16);
	client_socket = -1;
	active = false;
	in_thread = 0;
	out_thread = 0;
	end_point_port = 0;
	local_point_port = 0;
	thread_count = 0;
	direction = R14P_CD_UNKNOWN;
	r14p_session_id = 0;

	// mutexes
	pthread_mutex_init(&mtx_queue_in, NULL);
	pthread_mutex_init(&mtx_queue_out, NULL);
	pthread_mutex_init(&mtx_thread_count, NULL);
	pthread_mutex_init(&mtx_activity, NULL);
	pthread_mutex_init(&mtx_streams, NULL);
	pthread_mutex_init(&mtx_callback, NULL);
	pthread_mutex_init(&mtx_mc_pool, NULL);
	pthread_mutex_init(&mtx_pld_pool, NULL);
	pthread_mutex_init(&mtx_r14pm_pool, NULL);
	pthread_mutex_init(&mtx_session_id, NULL);
	pthread_mutex_init(&mtx_stream_pool, NULL);

	// random generator
	timespec tmp_time;
	clock_gettime(0, &tmp_time);
	ran_mt19937.seed(tmp_time.tv_nsec + tmp_time.tv_sec);
	random_generator = new boost::uuids::random_generator(ran_mt19937);


	// memory pools
	mc_pool.init(100);
	mc_pool.construct_objects();

	pld_pool.init(100);
	pld_pool.construct_objects();

	r14pm_pool.init(10);
	r14pm_pool.construct_objects();


	stream_pool.init(100);
	stream_pool.construct_objects();
	// set random generator
	R14PStream* tmp_stream[stream_pool.get_chunk_count()];
	for(int i = 0; i<stream_pool.get_chunk_count(); i++){
		tmp_stream[i] = stream_pool.allocate_constructed();
		tmp_stream[i]->set_random_generator(random_generator);
	}
	for(int i = 0; i<stream_pool.get_chunk_count(); i++) stream_pool.deallocate_constructed(tmp_stream[i]);

}

r14p::R14PClient::R14PClient(){
	// main init
	init();

}

r14p::R14PClient::R14PClient(int _client_socket, const char* _end_point_address, unsigned int _end_point_port, const char* _local_point_address, unsigned int _local_point_port, R14PConnectionDirection _direction){
	// main init
	init();

	// connection params
	direction = _direction;
	client_socket = _client_socket;
	strcpy(end_point_address, _end_point_address);
	strcpy(local_point_address, _local_point_address);
	end_point_port = _end_point_port;
	local_point_port = _local_point_port;

	// set as active
	set_activity(true);
	// init threads
	init_threads();

}

r14p::R14PClient::~R14PClient(){
	// set as inactive
	set_activity(false);
	// wait for threads
	while(get_thread_count() > 0){
		//std::cout << "sleeping.." << std::endl;
		sleep(1);
	}
	// disconnect just in case
	if(client_socket > 0) disconnect();
	// destory mutexes
	pthread_mutex_destroy(&mtx_queue_in);
	pthread_mutex_destroy(&mtx_queue_out);
	pthread_mutex_destroy(&mtx_thread_count);
	pthread_mutex_destroy(&mtx_activity);
	pthread_mutex_destroy(&mtx_streams);
	pthread_mutex_destroy(&mtx_callback);
	pthread_mutex_destroy(&mtx_mc_pool);
	pthread_mutex_destroy(&mtx_pld_pool);
	pthread_mutex_destroy(&mtx_r14pm_pool);
	pthread_mutex_destroy(&mtx_session_id);
	pthread_mutex_destroy(&mtx_stream_pool);

	// destroy streams
	for(unsigned int i = 0; i<streams.size(); i++) if(streams[i] != NULL) delete streams[i];
	streams.clear();


	// random generator
	delete random_generator;

}

int r14p::R14PClient::deallocate_mc_pool(memory::MemChunk<1024>* mem_chunk){
	if(mem_chunk != NULL){
		pthread_mutex_lock(&mtx_mc_pool);
		int res = mc_pool.deallocate_constructed(mem_chunk);
		pthread_mutex_unlock(&mtx_mc_pool);
		return res;

	}
	return -1;

}

memory::MemChunk<1024>* r14p::R14PClient::allocate_mc_pool(){
	pthread_mutex_lock(&mtx_mc_pool);
	memory::MemChunk<1024>* tmp = mc_pool.allocate_constructed();
	pthread_mutex_unlock(&mtx_mc_pool);
	return tmp;
}



int r14p::R14PClient::deallocate_pld_pool(R14PPayload* r14ppld){
	if(r14ppld != NULL){
		pthread_mutex_lock(&mtx_pld_pool);
		int res = pld_pool.deallocate_constructed(r14ppld);
		pthread_mutex_unlock(&mtx_pld_pool);
		return res;

	}
	return -1;

}

r14p::R14PPayload* r14p::R14PClient::allocate_pld_pool(){
	pthread_mutex_lock(&mtx_pld_pool);
	R14PPayload* tmp = pld_pool.allocate_constructed();
	pthread_mutex_unlock(&mtx_pld_pool);
	return tmp;
}



int r14p::R14PClient::deallocate_r14pm_pool(asn1::R14PMessage* r14pm){
	if(r14pm != NULL){
		pthread_mutex_lock(&mtx_r14pm_pool);
		int res = r14pm_pool.deallocate_constructed(r14pm);
		pthread_mutex_unlock(&mtx_r14pm_pool);
		return res;

	}
	return -1;

}

asn1::R14PMessage* r14p::R14PClient::allocate_r14pm_pool(){
	pthread_mutex_lock(&mtx_r14pm_pool);
	asn1::R14PMessage* tmp = r14pm_pool.allocate_constructed();
	pthread_mutex_unlock(&mtx_r14pm_pool);
	return tmp;
}

int r14p::R14PClient::deallocate_stream_pool(R14PStream* stream){
	if(stream != NULL){
		pthread_mutex_lock(&mtx_stream_pool);
		int res = stream_pool.deallocate_constructed(stream);
		pthread_mutex_unlock(&mtx_stream_pool);
		return res;

	}
	return -1;

}

r14p::R14PStream* r14p::R14PClient::allocate_stream_pool(){
	pthread_mutex_lock(&mtx_stream_pool);
	R14PStream* tmp = stream_pool.allocate_constructed();
	pthread_mutex_unlock(&mtx_stream_pool);
	return tmp;
}


int r14p::R14PClient::push_in_queue(R14PPayload* payload){
	if(payload != NULL){
		pthread_mutex_lock(&mtx_queue_in);
		in_queue.push_back(payload);
		pthread_mutex_unlock(&mtx_queue_in);
		return 0;

	}
	return -1;
}

int r14p::R14PClient::push_out_queue(R14PPayload* payload){
	if(payload != NULL){
		pthread_mutex_lock(&mtx_queue_out);
		out_queue.push_back(payload);
		pthread_mutex_unlock(&mtx_queue_out);
		return 0;

	}

	return -1;
}

r14p::R14PPayload* r14p::R14PClient::pop_in_queue(){
	pthread_mutex_lock(&mtx_queue_in);
	if(!in_queue.empty()){
		R14PPayload* tmp = in_queue.front();
		in_queue.pop_front();
		pthread_mutex_unlock(&mtx_queue_in);
		return tmp;

	}
	pthread_mutex_unlock(&mtx_queue_in);
	return NULL;
}

r14p::R14PPayload* r14p::R14PClient::pop_out_queue(){
	pthread_mutex_lock(&mtx_queue_out);
	if(!out_queue.empty()){
		R14PPayload* tmp = out_queue.front();
		out_queue.pop_front();
		pthread_mutex_unlock(&mtx_queue_out);
		return tmp;

	}
	pthread_mutex_unlock(&mtx_queue_out);
	return NULL;
}


bool r14p::R14PClient::is_active(){
	pthread_mutex_lock(&mtx_activity);
	bool tmp = active;
	pthread_mutex_unlock(&mtx_activity);
	return tmp;

}

void r14p::R14PClient::set_activity(bool _is_active){
	pthread_mutex_lock(&mtx_activity);
	active = _is_active;
	pthread_mutex_unlock(&mtx_activity);

}

int r14p::R14PClient::get_client_socket(){
	return client_socket;

}
char* r14p::R14PClient::get_end_point_address(){
	return end_point_address;
}

unsigned int r14p::R14PClient::get_end_point_port(){
	return end_point_port;
}

char* r14p::R14PClient::get_local_point_address(){
	return local_point_address;
}

unsigned int r14p::R14PClient::get_local_point_port(){
	return local_point_port;
}

uint64_t r14p::R14PClient::next_session_id(){
	pthread_mutex_lock(&mtx_session_id);
	uint64_t tmp = ++r14p_session_id;
	pthread_mutex_unlock(&mtx_session_id);
	return tmp;

}

int r14p::R14PClient::send(unsigned int sctp_stream_id, const unsigned char* data, unsigned int data_length){
	if(data != NULL){
		return sctp::send_sctp(client_socket, data, data_length, htonl(sctp::R14P), sctp_stream_id);
	}
	// err
	return -1;
}

int r14p::R14PClient::send_datagram(int payload_type, unsigned char* payload, int payload_length, R14PCallbackMethod* on_sent_callback_method){
	// allocate memory
	memory::MemChunk<1024>* tmp_buffer_1 = allocate_mc_pool();
	memory::MemChunk<1024>* tmp_buffer_2 = allocate_mc_pool();
	memory::MemChunk<1024>* tmp_buffer_3 = allocate_mc_pool();
	R14PPayload* r14pp = allocate_pld_pool();
	asn1::R14PMessage* r14p_out_message = allocate_r14pm_pool();
	R14PStream* r14ps = allocate_stream_pool();

	// next session id
	uint64_t tmp_session_id = next_session_id();

	// set optional
	r14p_out_message->_header->_source->set_id();
	r14p_out_message->_header->_destination->set_id();
	r14p_out_message->set_body();
	r14p_out_message->_body->_data->set_payload();
	r14p_out_message->prepare();

	// header
	int ver = _VERSION_;
	r14p_out_message->_header->_version->set_linked_data(1, (unsigned char*)&ver, 1);
	r14p_out_message->_header->_source->_id->set_linked_data(1, (unsigned char*)"test_id", 7);
	r14p_out_message->_header->_source->_type->set_linked_data(1, (unsigned char*)"test_type", 9);
	r14p_out_message->_header->_destination->_id->set_linked_data(1, (unsigned char*)"test_id", 7);
	r14p_out_message->_header->_destination->_type->set_linked_data(1, (unsigned char*)"test_type", 9);

	r14ps->generate_uuid();
	r14p_out_message->_header->_uuid->set_linked_data(1, r14ps->get_uuid(), 16);

	r14p_out_message->_header->_sequence_num->set_linked_data(1, (unsigned char*)&ver, 1);
	r14p_out_message->_header->_sequence_flag->set_linked_data(1, (unsigned char*)&ver, 1);

	// body
	r14p_out_message->_body->_data->_payload_type->tlv->value = tmp_buffer_1->buffer;
	r14p_out_message->_body->_data->_payload_type->tlv->value[0] = 3;
	r14p_out_message->_body->_data->_payload_type->tlv->value[1] = 0xe8;
	r14p_out_message->_body->_data->_payload_type->tlv->value_length = 2;
	r14p_out_message->_body->_data->_payload_type->set_linked_data(tmp_session_id);

	r14p_out_message->_body->_data->_payload->tlv->value = tmp_buffer_2->buffer;
	memcpy(r14p_out_message->_body->_data->_payload->tlv->value, payload, payload_length);
	r14p_out_message->_body->_data->_payload->tlv->value_length = payload_length;
	r14p_out_message->_body->_data->_payload->set_linked_data(tmp_session_id);


	// r14p payload
	r14pp->r14p_stream_type = R14P_ST_STATELESS_NO_REPLY;
	r14pp->raw_data = tmp_buffer_3->buffer;
	r14pp->raw_data_length = asn1::encode(r14pp->raw_data, 1024, r14p_out_message, tmp_session_id);
	r14pp->client = this;
	r14pp->clear_callbacks();
	if(on_sent_callback_method != NULL){
		r14pp->set_callback(R14P_ET_PAYLOAD_SENT, on_sent_callback_method);

	}

	// return mem to pool
	deallocate_mc_pool(tmp_buffer_1);
	deallocate_mc_pool(tmp_buffer_2);
	deallocate_r14pm_pool(r14p_out_message);
	deallocate_stream_pool(r14ps);

	// send to queue
	push_out_queue(r14pp);


	return 0;
}

int r14p::R14PClient::send(R14PStreamType stream_type, R14PPayload* payload){
	if(payload != NULL){
		payload->r14p_stream_type = stream_type;
		push_out_queue(payload);
		return 0;

	}

	return -1;
}

r14p::R14PStream* r14p::R14PClient::create_stream(){
	R14PStream* stream = new R14PStream(random_generator);
	pthread_mutex_lock(&mtx_streams);
	streams.push_back(stream);
	pthread_mutex_unlock(&mtx_streams);
	return stream;
}

r14p::R14PStream* r14p::R14PClient::get_stream(int index){
	pthread_mutex_lock(&mtx_streams);
	if(streams.size() > index){
		R14PStream* stream = streams[index];
		pthread_mutex_unlock(&mtx_streams);
		return stream;
	}
	pthread_mutex_unlock(&mtx_streams);

	return NULL;
}

r14p::R14PStream* r14p::R14PClient::get_stream(const unsigned char* _uuid){
	if(_uuid == NULL) return NULL;
	R14PStream* stream = NULL;
	pthread_mutex_lock(&mtx_streams);
	for(int i = 0; i<streams.size(); i++){
		stream = streams[i];
		if(memcmp(stream->get_uuid(), _uuid, 16) == 0){
			pthread_mutex_unlock(&mtx_streams);
			return stream;
		}
	}
	pthread_mutex_unlock(&mtx_streams);
	return NULL;
}

void r14p::R14PClient::remove_callback(R14PEventType callback_type){
	pthread_mutex_lock(&mtx_callback);
	callback_handler.remove_callback(callback_type);
	pthread_mutex_unlock(&mtx_callback);

}

void r14p::R14PClient::set_callback(R14PEventType callback_type, R14PCallbackMethod* callback_method){
	pthread_mutex_lock(&mtx_callback);
	callback_handler.set_callback(callback_type, callback_method);
	pthread_mutex_unlock(&mtx_callback);
}


void r14p::R14PClient::process_callback(R14PEventType type, R14PCallbackArgs* args){
	pthread_mutex_lock(&mtx_callback);
	callback_handler.process_callback(type, args);
	pthread_mutex_unlock(&mtx_callback);
}


int r14p::R14PClient::disconnect(){
	// set as inactive
	set_activity(false);
	// shutdown client
	int res = sctp::shutdown_sctp_client(client_socket);
	// socket closed
	if(res == 0) {
		client_socket = -1;
		return 0;
	}
	// error while closing socket
	return -1;
}

void r14p::R14PClient::init_threads(){
    if(pthread_create(&in_thread, NULL, &in_loop, this) == 0) inc_thread_count();
    if(pthread_create(&out_thread, NULL, &out_loop, this) == 0) inc_thread_count();

}


void* r14p::R14PClient::in_loop(void* args){

	if(args != NULL){
		// session pointer
		R14PClient* r14pc = (R14PClient*)args;
		int res;
		// sleep params, 1ms
		timespec sleep_params;
		sleep_params.tv_sec = 0;
		sleep_params.tv_nsec = 1000000;
		pollfd fds_lst[1];
		// monitor POLLIN event
		fds_lst[0].events = POLLIN;
		// update socket in poll structure
		fds_lst[0].fd = r14pc->client_socket;
		// set poll timeout to 5 sec
		int poll_timeout = 5000;
		unsigned char tmp_buff[8192];

		// loop
		while(r14pc->is_active()){
			// poll
			res = poll(fds_lst, 1, poll_timeout);
			// check for timeout
			if(res > 0){
				// check for POLLIN event
				if((fds_lst[0].revents & POLLIN) == POLLIN){
					res = sctp::rcv_sctp(r14pc->client_socket, tmp_buff, 512, sizeof(tmp_buff), NULL);
					if(res > 0){
						// TODO
					}

				}
			}
			//nanosleep(&sleep_params, NULL);
		}

		// detach thread
		pthread_detach(r14pc->in_thread);
		r14pc->in_thread = 0;
		r14pc->dec_thread_count();

	}

	return NULL;
}

void* r14p::R14PClient::out_loop(void* args){
	// check for args
	if(args != NULL){
		// sleep params, 1ms
		timespec sleep_params;
		sleep_params.tv_sec = 0;
		sleep_params.tv_nsec = 1000000;
		R14PCallbackArgs cb_args(NULL, 1);
		// session pointer
		R14PClient* r14pc = (R14PClient*)args;
		// payload pointer
		R14PPayload* r14ppld = NULL;
		//R14PStream* stream = NULL;

		// loop
		while(r14pc->is_active()){
			// pop
			r14ppld = r14pc->pop_out_queue();
			// check if not NULL
			if(r14ppld != NULL){
				// generate stream if not using R14P_ST_STATELESS_NO_REPLY
				if(r14ppld->r14p_stream_type != R14P_ST_STATELESS_NO_REPLY){
					r14pc->create_stream();
				}
				// send through socket
				r14pc->send(r14ppld->sctp_sid, r14ppld->raw_data, r14ppld->raw_data_length);
				// process client callbacks
				cb_args.args = r14pc;
				switch(r14ppld->r14p_stream_type){
					// stateful
					case R14P_ST_STATEFUL:
						r14pc->process_callback(R14P_ET_STATEFUL_OUTBOUND_NEW, &cb_args);
						break;
					// stateless
					case R14P_ST_STATELESS:
					case R14P_ST_STATELESS_NO_REPLY:
						r14pc->process_callback(R14P_ET_STATELESS_OUTBOUND_NEW, &cb_args);
						break;
				}
				// process payload callbacks
				cb_args.args = r14ppld;
				r14ppld->process_callback(R14P_ET_PAYLOAD_SENT, &cb_args);

				// free memory, return back to pool

				// * r14ppld->raw_data points to MemChunk.buffer
				// * deallocate_mc_pool expects a pointer to MemChunk
				// * buffer is the first field in MemChunk class so both MemChunk class and MemChunk.buffer field share the same address
				// * this makes type casting the MemChunk.raw_data to MemChunk valid
				r14pc->deallocate_mc_pool((memory::MemChunk<1024>*)r14ppld->raw_data);
				r14pc->deallocate_pld_pool(r14ppld);


			}else{
				// sleep
				nanosleep(&sleep_params, NULL);

			}
		}

		// detach thread
		pthread_detach(r14pc->out_thread);
		r14pc->out_thread = 0;
		r14pc->dec_thread_count();

	}

	return NULL;
}

unsigned int r14p::R14PClient::inc_thread_count(){
	pthread_mutex_lock(&mtx_thread_count);
	unsigned int tmp = ++thread_count;
	pthread_mutex_unlock(&mtx_thread_count);
	return tmp;

}

unsigned int r14p::R14PClient::dec_thread_count(){
	pthread_mutex_lock(&mtx_thread_count);
	unsigned int tmp = --thread_count;
	pthread_mutex_unlock(&mtx_thread_count);
	return tmp;

}


unsigned int r14p::R14PClient::get_thread_count(){
	pthread_mutex_lock(&mtx_thread_count);
	unsigned int tmp = thread_count;
	pthread_mutex_unlock(&mtx_thread_count);
	return tmp;

}


// R14PStream
r14p::R14PStream::R14PStream(){
	memset(uuid, 0, 16);
	sequence_num = 0;
	sequence_flag = R14P_SF_UNKNOWN;
	client = NULL;
	random_generator = NULL;
}

r14p::R14PStream::R14PStream(boost::uuids::random_generator* _random_generator){
	memset(uuid, 0, 16);
	sequence_num = 0;
	sequence_flag = R14P_SF_UNKNOWN;
	client = NULL;
	random_generator = _random_generator;

	generate_uuid();

}

void r14p::R14PStream::set_random_generator(boost::uuids::random_generator* _random_generator){
	random_generator = _random_generator;
}

unsigned char* r14p::R14PStream::get_uuid(){
	return uuid;
}

void r14p::R14PStream::generate_uuid(){
    boost::uuids::uuid _uuid = (*random_generator)(); // operator ()
    memcpy(uuid, _uuid.data, 16);

}
r14p::R14PStream::~R14PStream(){

}

// R14PSession
r14p::R14PSession::R14PSession(){
	server_socket = -1;
	server_mode = false;
	server_thread = 0;
	thread_count = 0;
	pthread_mutex_init(&mtx_thread_count, NULL);
	pthread_mutex_init(&mtx_server_socket, NULL);
	pthread_mutex_init(&mtx_server_mode, NULL);
	pthread_mutex_init(&mtx_callback, NULL);
	pthread_mutex_init(&mtx_clients, NULL);
	clients.reserve(100);
}

r14p::R14PSession::~R14PSession(){
	// children
	for(unsigned int i = 0; i<clients.size(); i++) if(clients[i] != NULL) delete clients[i];
	clients.clear();
	// mutexes
	pthread_mutex_destroy(&mtx_thread_count);
	pthread_mutex_destroy(&mtx_server_socket);
	pthread_mutex_destroy(&mtx_server_mode);
	pthread_mutex_destroy(&mtx_callback);
	pthread_mutex_destroy(&mtx_clients);


}

int r14p::R14PSession::stop_server(){
	if(get_server_mode() && (get_server_socket() > 0)){
		// shutdown connection
		int res = sctp::shutdown_sctp_client(get_server_socket());
		// socket closed
		if(res == 0) {
			set_server_mode(false);
			set_server_socket(-1);
			return 0;
		}
		// error while closing socket
		return -1;
	}
	// error
	return -1;
}

void r14p::R14PSession::remove_callback(R14PEventType callback_type){
	pthread_mutex_lock(&mtx_callback);
	callback_handler.remove_callback(callback_type);
	pthread_mutex_unlock(&mtx_callback);

}

void r14p::R14PSession::set_callback(R14PEventType callback_type, R14PCallbackMethod* callback_method){
	pthread_mutex_lock(&mtx_callback);
	callback_handler.set_callback(callback_type, callback_method);
	pthread_mutex_unlock(&mtx_callback);
}


void r14p::R14PSession::process_callback(R14PEventType type, R14PCallbackArgs* args){
	pthread_mutex_lock(&mtx_callback);
	callback_handler.process_callback(type, args);
	pthread_mutex_unlock(&mtx_callback);
}


unsigned int r14p::R14PSession::inc_thread_count(){
	pthread_mutex_lock(&mtx_thread_count);
	unsigned int tmp = ++thread_count;
	pthread_mutex_unlock(&mtx_thread_count);
	return tmp;

}

unsigned int r14p::R14PSession::dec_thread_count(){
	pthread_mutex_lock(&mtx_thread_count);
	unsigned int tmp = --thread_count;
	pthread_mutex_unlock(&mtx_thread_count);
	return tmp;

}


unsigned int r14p::R14PSession::get_thread_count(){
	pthread_mutex_lock(&mtx_thread_count);
	unsigned int tmp = thread_count;
	pthread_mutex_unlock(&mtx_thread_count);
	//std::cout << "get_thread_count: " << tmp << std::endl;
	return tmp;

}

void r14p::R14PSession::set_server_socket(int _socket){
	pthread_mutex_lock(&mtx_server_socket);
	server_socket = _socket;
	pthread_mutex_unlock(&mtx_server_socket);


}

int r14p::R14PSession::get_server_socket(){
	pthread_mutex_lock(&mtx_server_socket);
	int socket =  server_socket;
	pthread_mutex_unlock(&mtx_server_socket);
	return socket;
}

void r14p::R14PSession::set_server_mode(bool _server_mode){
	pthread_mutex_lock(&mtx_server_mode);
	server_mode = _server_mode;
	pthread_mutex_unlock(&mtx_server_mode);

}

bool r14p::R14PSession::get_server_mode(){
	pthread_mutex_lock(&mtx_server_mode);
	bool tmp = server_mode;
	pthread_mutex_unlock(&mtx_server_mode);
	return tmp;
}

void* r14p::R14PSession::server_loop(void* args){
	if(args != NULL){
		// session pointer
		R14PSession* r14ps = (R14PSession*)args;
		int tmp_c = -1;
		sockaddr_in si, pi;
		int size_si = sizeof(sockaddr_in);
		int tmp_s;
		int res;
		pollfd fds_lst[1];
		R14PCallbackArgs cb_args(NULL, 1);
		// set poll timeout to 5 sec
		int poll_timeout = 5000;

		// monitor POLLIN event
		fds_lst[0].events = POLLIN;

		// loop
		while(r14ps->get_server_mode()){
			// get server socket
			tmp_s = r14ps->get_server_socket();
			// update socket in poll structure
			fds_lst[0].fd = tmp_s;
			// poll
			res = poll(fds_lst, 1, poll_timeout);
			// check for timeout
			if(res > 0){
				// check for POLLIN event
				if((fds_lst[0].revents & POLLIN) == POLLIN){
					// get client socket and remote peer info
					tmp_c = sctp::get_client(tmp_s, &pi);
					// check if socket is valid
					if(tmp_c > 0) {
						// get local socket info
						getsockname(tmp_c, (sockaddr*)&si, (socklen_t*)&size_si);
						// add client
						R14PClient* client = new R14PClient(tmp_c, inet_ntoa(pi.sin_addr), ntohs(pi.sin_port), inet_ntoa(si.sin_addr), ntohs(si.sin_port), R14P_CD_INBOUND);
						r14ps->add_client(client);
						// process callback(s)
						cb_args.args = client;
						r14ps->process_callback(R14P_ET_CLIENT_INBOUND_NEW, &cb_args);

					}
				}


			}

		}
		// detach thread
		pthread_detach(r14ps->server_thread);
		r14ps->server_thread = 0;
		r14ps->dec_thread_count();

	}

	return NULL;

}
int r14p::R14PSession::start_server(const char* bind_address, unsigned int bind_port){
	// server not started
	if(!get_server_mode() && (get_server_socket() < 0)){
		// bind to specific address
		if(bind_address != NULL){
			set_server_socket(sctp::init_sctp_server(inet_addr(bind_address), bind_port));
			set_server_mode(true);
		// bind to INADDR_ANY
		}else{
			set_server_socket(sctp::init_sctp_server(0, bind_port));
			set_server_mode(true);
		}
		// start server thread
		if(get_server_mode()){
			/*
	        pthread_attr_t attr;
	        pthread_attr_init(&attr);
	        pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	        pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	        sched_param sp;
	        sp.__sched_priority = 99;
	        pthread_attr_setschedparam(&attr, &sp);
			*/
	        if(pthread_create(&server_thread, NULL, &server_loop, this) == 0) inc_thread_count();

	        // pthread name
			//char *pthread_name = new char[30];
			//strcpy(pthread_name,  "sctp_server_thread\0");
			//pthread_setname_np(thread, pthread_name);

		}

	}

	// return server socket
	return get_server_socket();
}

r14p::R14PClient* r14p::R14PSession::get_client(unsigned int client_index){
	pthread_mutex_lock(&mtx_clients);
	R14PClient* tmp = NULL;
	if(clients.size() > client_index) tmp = clients[client_index];
	pthread_mutex_unlock(&mtx_clients);
	return tmp;
}

void r14p::R14PSession::add_client(R14PClient* client){
	pthread_mutex_lock(&mtx_clients);
	clients.push_back(client);
	pthread_mutex_unlock(&mtx_clients);

}

int r14p::R14PSession::get_client_count(){
	pthread_mutex_lock(&mtx_clients);
	int tmp = clients.size();
	pthread_mutex_unlock(&mtx_clients);
	return tmp;
}

int r14p::R14PSession::remove_client(unsigned int client_index){
	// lock mutex
	pthread_mutex_lock(&mtx_clients);
	// validate index
	if(clients.size() > client_index){
		// save pointer to erased client
		R14PClient* tmp = clients[client_index];
		// erase
		clients.erase(clients.begin() + client_index);
		// unlock mutex
		pthread_mutex_unlock(&mtx_clients);
		// free mem
		delete tmp;
		// ok
		return 0;
	}
	//unlock mutex
	pthread_mutex_unlock(&mtx_clients);
	// return error, not found
	return -1;

}

int r14p::R14PSession::remove_client(R14PClient* r14p_client){
	if(r14p_client != NULL){
		//lock mutex
		pthread_mutex_lock(&mtx_clients);
		for(unsigned int i = 0; i<clients.size(); i++) if(clients[i] == r14p_client) {
			// erase
			clients.erase(clients.begin() + i);
			// unlock mutex
			pthread_mutex_unlock(&mtx_clients);
			// free mem
			delete r14p_client;
			// found, return ok
			return 0;
		}
	}
	// unlock mutex
	pthread_mutex_unlock(&mtx_clients);
	// return error, not found
	return -1;
}

r14p::R14PClient* r14p::R14PSession::connect(const char* end_point_address, unsigned int end_point_port, int stream_count, const char* local_address, unsigned int local_port){
	if(end_point_address == NULL || end_point_port == 0 || stream_count == 0) return NULL;
	// client
	//unsigned long remote_address = inet_addr(end_point_address);
	int client_id = -1;
	if(local_address == NULL || local_port == 0){
		// connect
		client_id = sctp::init_sctp_client(inet_addr(end_point_address), end_point_port, stream_count);
	}else{
		// connect and bind to specific ip:port
		client_id = sctp::init_sctp_client_bind(inet_addr(end_point_address), inet_addr(local_address), local_port, end_point_port, stream_count);

	}
	// create client if socket is valid
	if(client_id > 0){
		// socket info
		sockaddr_in si;
		int size_si = sizeof(sockaddr_in);
		// get local socket info
		getsockname(client_id, (sockaddr*)&si, (socklen_t*)&size_si);
		// add client
		R14PClient* client = new R14PClient(client_id, end_point_address, end_point_port, inet_ntoa(si.sin_addr), ntohs(si.sin_port), R14P_CD_OUTBOUND);
		add_client(client);
		// return client
		return client;
	}
	// connection error
	return NULL;
}


// namespace methods
r14p::R14PSession* r14p::init_session(){
	return new R14PSession();
}

int r14p::destroy_session(R14PSession* r14p_session){
	if(r14p_session != NULL){
		while(r14p_session->get_thread_count() > 0){
			sleep(1);
		}
		delete r14p_session;
		// ok
		return 0;
	}
	// error
	return 1;

}
