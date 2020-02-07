/**
 * @file r14p.h
 * @brief R14P library
 * @details R14P implementation
 * @version 1.0
 * @date 2012
 * @author Damir Franusic <df@release14.org>
 */
#ifndef R14P_H_
#define R14P_H_

#include <vector>
#include <map>
#include <deque>
#include <pthread.h>
#include <r14p_asn1.h>
#include <pool.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace r14p {
	// current R14P version
	const int _VERSION_ = 1;

	/**
	 * <pre>
	 * R14P Stream type
	 *	0 - STATEFUL stream
	 *	1 - STATELESS stream (single packet, no stream)
	 *
	 * </pre>
	 */
	enum R14PStreamType {
		/** <b>-1</b> - Unknown stream */
		R14P_ST_UNKNOWN = -1,
		/** <b>0x00</b> - Stateful stream */
		R14P_ST_STATEFUL = 0x00,
		/** <b>0x01</b> - Stateless stream (single packet, no stream) */
		R14P_ST_STATELESS = 0x01,
		/** <b>0x02</b> - Stateless stream without reply confirmation (single packet, no stream) */
		R14P_ST_STATELESS_NO_REPLY = 0x02,

	};

	/**
	 * <pre>
	 * R14P Event type
	 * 	0 - New INBOUND client connection
	 * 	1 - New OUTBOUND client connection
	 * 	2 - INBOUND STATEFUL stream initialization
	 * 	3 - INBOUND STATEFUL stream continuation
	 * 	4 - INBOUND STATEFUL stream ending
	 * 	5 - OUTBOUND STATEFUL stream initialization
	 * 	6 - OUTBOUND STATEFUL stream continuation
	 * 	7 - OUTBOUND STATEFUL stream ending
	 * 	8 - New INBOUND STATELESS packet
	 * 	9 - New OUTBOUND STATELESS packet
	 * </pre>
	 */
	enum R14PEventType {
		/** <b>0</b> - New INBOUND client connection */
		R14P_ET_CLIENT_INBOUND_NEW = 0,
		/** <b>1</b> - New OUTBOUND client connection */
		R14P_ET_CLIENT_OUTBOUND_NEW = 1,
		/** <b>2</b> - INBOUND STATEFUL packet */
		R14P_ET_STATEFUL_INBOUND_NEW = 2,
		/** <b>3</b> - OUTBOUND STATEFUL packet */
		R14P_ET_STATEFUL_OUTBOUND_NEW = 3,
		/** <b>4</b> - New INBOUND STATELESS packet */
		R14P_ET_STATELESS_INBOUND_NEW = 4,
		/** <b>5</b> - New OUTBOUND STATELESS packet */
		R14P_ET_STATELESS_OUTBOUND_NEW = 5,
		/** <b>6</b> - Reply received (R14P_ST_STATEFUL and R14P_ST_STATELESS) */
		R14P_ET_REPLY_RECEIVED = 6,



		R14P_ET_PAYLOAD_SENT = 10,

	};

	/**
	 * <pre>
	 * R14P Connection direction
	 * 	-1 	- Unknown/ERR
	 * 	0 	- INBOUND
	 *	1	- OUTBOUND
	 * </pre>
	 */
	enum R14PConnectionDirection {
		R14P_CD_UNKNOWN = -1,
		R14P_CD_INBOUND = 0x00,
		R14P_CD_OUTBOUND= 0x01
	};


	enum R14PSequenceFlag {
		R14P_SF_UNKNOWN = -1,
		R14P_SF_START = 0,
		R14P_SF_CONTINUE = 1,
		R14P_SF_END = 2

	};

	// R14P Callback arguments
	class R14PCallbackArgs {
	public:
		R14PCallbackArgs();
		R14PCallbackArgs(void* _args, int _arg_count);
		// pointer to argument(s)
		void* args;
		// number of arguments
		int arg_count;

	};

	// R14P Callback method
	class R14PCallbackMethod {
	public:
		R14PCallbackMethod();
		virtual ~R14PCallbackMethod();
		virtual void run(R14PCallbackArgs* args);
	};

	// R14P Callback Handler
	class R14PCallbackHandler {
	private:
		std::map<R14PEventType, R14PCallbackMethod*> callback_map;
	public:
		R14PCallbackHandler();
		~R14PCallbackHandler();
		void set_callback(R14PEventType type, R14PCallbackMethod* method);
		void remove_callback(R14PEventType type);
		void clear();
		void process_callback(R14PEventType type, R14PCallbackArgs* args);
	};

	// fwd declaration
	class R14PClient;
	class R14PPayload;



	/**
	 * R14P Stream
	 */
	class R14PStream {
	private:
		boost::uuids::random_generator* random_generator;
		// stream uuid
		unsigned char uuid[16];
		// stream sequence number
		unsigned int sequence_num;
		// current sequence position
		R14PSequenceFlag sequence_flag;
		// client connection
		R14PClient* client;

	public:
		R14PStream();
		R14PStream(boost::uuids::random_generator* _random_generator);
		~R14PStream();

		void set_random_generator(boost::uuids::random_generator* _random_generator);
		unsigned char* get_uuid();
		void generate_uuid();


	};

	/** R14P Client connection
	 *
	 */
	class R14PClient {
	private:
		// uuid generator
		boost::mt19937 ran_mt19937;
		// due to boost related valgrind warnings, declared as a pointer to heap allocated memory
		// when this gets fixed, random_generator should be stack declared as an offset of R14PClient class
		boost::uuids::random_generator* random_generator;


		void init();
		R14PConnectionDirection direction;
		int client_socket;
		char end_point_address[16];
		unsigned int end_point_port;
		char local_point_address[16];
		unsigned int local_point_port;


		bool active;
		std::vector<R14PStream*> streams;
		std::deque<R14PPayload*> in_queue;
		std::deque<R14PPayload*> out_queue;

		// r14p asn1 related
		uint64_t r14p_session_id;


		// thread related
		unsigned int thread_count;
		pthread_t in_thread;
		pthread_t out_thread;
		void init_threads();

		// callback related
		R14PCallbackHandler callback_handler;
		void process_callback(R14PEventType type, R14PCallbackArgs* args);

		// mutexes
		pthread_mutex_t mtx_queue_in;
		pthread_mutex_t mtx_queue_out;
		pthread_mutex_t mtx_thread_count;
		pthread_mutex_t mtx_activity;
		pthread_mutex_t mtx_streams;
		pthread_mutex_t mtx_callback;
		pthread_mutex_t mtx_mc_pool;
		pthread_mutex_t mtx_pld_pool;
		pthread_mutex_t mtx_r14pm_pool;
		pthread_mutex_t mtx_stream_pool;
		pthread_mutex_t mtx_session_id;

		// thread methods
		static void* in_loop(void* args);
		static void* out_loop(void* args);

		// memory pool
		memory::Pool<memory::MemChunk<1024> > mc_pool;
		memory::Pool<R14PPayload> pld_pool;
		memory::Pool<asn1::R14PMessage> r14pm_pool;
		memory::Pool<R14PStream> stream_pool;


		// other
		bool is_active();
		void set_activity(bool _is_active);

		// socket related
		int send(unsigned int sctp_stream_id, const unsigned char* data, unsigned int data_length);

		// queue methods
		int push_in_queue(R14PPayload* payload);
		int push_out_queue(R14PPayload* payload);
		R14PPayload* pop_in_queue();
		R14PPayload* pop_out_queue();

		// session
		uint64_t next_session_id();

	public:
		// constructor(s) and destructor
		R14PClient();
		R14PClient(int _client_socket, const char* end_point_address, unsigned int end_point_port, const char* _local_point_address, unsigned int _local_point_port, R14PConnectionDirection _direction);
		~R14PClient();
		// methods
		int get_client_socket();
		int disconnect();
		char* get_end_point_address();
		unsigned int get_end_point_port();
		char* get_local_point_address();
		unsigned int get_local_point_port();

		// thread related
		unsigned int get_thread_count();
		unsigned int inc_thread_count();
		unsigned int dec_thread_count();

		// streams
		R14PStream* create_stream();
		R14PStream* get_stream(const unsigned char* _uuid);
		R14PStream* get_stream(int index);
		int destroy_stream(R14PStream* stream);

		// data
		int send(R14PStreamType stream_type, R14PPayload* payload);
		// similar to UDP datagram but reliable due to SCTP, no correlated reply is received from the peer
		int send_datagram(int payload_type, unsigned char* payload, int payload_length, R14PCallbackMethod* on_sent_callback_method);


		// callback related
		void set_callback(R14PEventType callback_type, R14PCallbackMethod* callback_method);
		void remove_callback(R14PEventType callback_type);

		// mem pool
		int deallocate_mc_pool(memory::MemChunk<1024>* mem_chunk);
		memory::MemChunk<1024>* allocate_mc_pool();

		int deallocate_pld_pool(R14PPayload* r14ppld);
		R14PPayload* allocate_pld_pool();

		int deallocate_r14pm_pool(asn1::R14PMessage* r14pm);
		asn1::R14PMessage* allocate_r14pm_pool();

		int deallocate_stream_pool(R14PStream* stream);
		R14PStream* allocate_stream_pool();


	};

	// R14P payload
	class R14PPayload {
	private:
		// callback related
		R14PCallbackHandler callback_handler;

	public:
		// Memory Chunk Pool callback
		// returns payload object back to pool
		/*
		class PoolMemClean : public r14p::R14PCallbackMethod {
		public:
			void run(R14PCallbackArgs* args) {
				if(args != NULL){
					R14PPayload* r14pld = (R14PPayload*)args->args;
					if(r14pld->extra_data != NULL){
						if(r14pld->client != NULL){
							int res = r14pld->client->deallocate_mc_pool((memory::MemChunk<1024>*)r14pld->extra_data);
							std::cout << "PayloadSentCallback: " << res << std::endl;
						}
					}

				}

			}
		};
		*/

		R14PPayload();
		~R14PPayload();
		unsigned int sctp_sid;
		R14PStreamType r14p_stream_type;
		// raw byte stream
		unsigned char* raw_data;
		unsigned int raw_data_length;
		void* extra_data;
		// client connection
		R14PClient* client;
		// pool mem clean callback
		//PoolMemClean mem_clean_callback;

		// callback related

		void process_callback(R14PEventType type, R14PCallbackArgs* args);
		void set_callback(R14PEventType callback_type, R14PCallbackMethod* callback_method);
		void remove_callback(R14PEventType callback_type);
		void clear_callbacks();

	};

	/** R14P Session information
	 *
	 */
	class R14PSession {
	private:
		int server_socket;
		bool server_mode;
		std::vector<R14PClient*> clients;
		// thread count (clients + server)
		unsigned int thread_count;
		// server pthread
		pthread_t server_thread;
		// server loop method, separate thread
		static void* server_loop(void* args);
		// mutexes
		pthread_mutex_t mtx_thread_count;
		pthread_mutex_t mtx_server_socket;
		pthread_mutex_t mtx_server_mode;
		pthread_mutex_t mtx_callback;
		pthread_mutex_t mtx_clients;
		// callback related
		R14PCallbackHandler callback_handler;
		void process_callback(R14PEventType type, R14PCallbackArgs* args);

		// client related
		void add_client(R14PClient* client);
	public:
		// constructor(s) and destructor
		R14PSession();
		~R14PSession();


		// thread related
		unsigned int get_thread_count();
		unsigned int inc_thread_count();
		unsigned int dec_thread_count();

		// client related
		R14PClient* get_client(unsigned int client_index);
		int get_client_count();
		// remove client and free memory
		int remove_client(unsigned int client_index);
		int remove_client(R14PClient* r14p_client);
		// connect client to end point
		R14PClient* connect(const char* end_point_address, unsigned int end_point_port, int stream_count, const char* local_address, unsigned int local_port);

		// server related
		int get_server_socket();
		void set_server_socket(int _socket);
		bool get_server_mode();
		void set_server_mode(bool _server_mode);
		int start_server(const char* bind_address, unsigned int bind_port);
		int stop_server();

		// callback related
		void set_callback(R14PEventType callback_type, R14PCallbackMethod* callback_method);
		void remove_callback(R14PEventType callback_type);


	};



	// init session with remote end point
	R14PSession* init_session();
	// destroy session
	int destroy_session(R14PSession* r14p_session);

}




#endif /* R14P_H_ */
