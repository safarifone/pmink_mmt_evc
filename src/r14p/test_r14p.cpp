#include <iostream>
#include <sctp.h>
#include <r14p.h>
#include <r14p_asn1.h>
#include <fstream>
#include <deque>
#include <pool.h>

class TestCallback : public r14p::R14PCallbackMethod {
public:
	void run(r14p::R14PCallbackArgs* args) {
		if(args != NULL){
			r14p::R14PClient* client = (r14p::R14PClient*)args->args;
			std::cout	<< "new_client_callback: remote "
						<< client->get_end_point_address()
						<< ":"
						<< client->get_end_point_port()
						<< ", local "
						<< client->get_local_point_address()
						<< ":"
						<< client->get_local_point_port()
						<< std::endl;

		}

	}
};

class TestCallback2 : public r14p::R14PCallbackMethod {
public:
	void run(r14p::R14PCallbackArgs* args) {
		if(args != NULL){
			r14p::R14PClient* client = (r14p::R14PClient*)args->args;
			std::cout	<< "new_statless outbound: "
						<< client->get_end_point_address()
						<< ":"
						<< client->get_end_point_port()
						<< std::endl;

		}

	}
};

class TestCallback3 : public r14p::R14PCallbackMethod {
public:
	void run(r14p::R14PCallbackArgs* args) {
		std::cout << "Payload sent" << std::endl;
	}
};

class TestClass {
public:
	int* test;
	TestClass(){
		test = new int;
		*test = 100;

		//cout << "Constructor" << endl;
	}
	~TestClass(){
		delete test;
		//cout << "Destructor" << endl;

	}
};




timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
void test_func(){
	int i = 0;
	i++;
}

int main(){
	/*
	char *a = new char;
	*a = 0xff;
	if(*a & 0x40 == 0x40) cout << "AAAA" << endl;

	return 1;
	*/
	/*
	timespec time1, time2;

	int test_arr[1000000000];
	clock_gettime(0, &time1);

	int test_c = 0;
	for(int i = 0; i<1000000000; i++){
		if(test_arr[i] == 0)
		test_c++;
	}
	clock_gettime(0, &time2);
	int nsec = (diff(time1,time2).tv_sec * 1000000000) + (diff(time1,time2).tv_nsec);

	cout << nsec << endl;

	return 1;
	*/

/*
	TestClass* tmp_p = NULL;
	Pool<TestClass> pool(1000);
	pool.construct_objects();
	for(int i = 0; i<1000000; i++){
		//new TestClass();
		//tmp_p = new(pool.allocate()) TestClass();
		//pool.deallocate_destroy(tmp_p);

		tmp_p = pool.allocate_object();
		pool.deallocate_object(tmp_p);

	}

	return 1;
*/
	//memory::Pool<TestClass> pool(10);
	//pool.construct_objects();
//	cout << endl;

	/*
	cout << "Raw free" << endl;
	for(int i = 0; i<pool.raw_free_size; i++){
		cout << i << " -> " << (int*)pool.raw_free_list[i] << endl;
	}
	cout << endl;

	cout << "Constructed free" << endl;
	for(int i = 0; i<pool.constructed_free_size; i++){
		cout << i << " -> " << (int*)pool.constructed_free_list[i] << endl;
	}
*/
	//return 1;
	//pool.allocate_object();

	//return 1;
	/*
	TestClass* tmp_str = NULL;

	TestClass* arr[15];

	arr[0] = new(pool.allocate_raw()) TestClass();
	arr[1] = new(pool.allocate_raw()) TestClass();
	arr[2] = new(pool.allocate_raw()) TestClass();
	arr[3] = new(pool.allocate_raw()) TestClass();
	arr[4] = new(pool.allocate_raw()) TestClass();
	arr[5] = new(pool.allocate_raw()) TestClass();
	arr[6] = new(pool.allocate_raw()) TestClass();
	arr[7] = new(pool.allocate_raw()) TestClass();
	arr[8] = new(pool.allocate_raw()) TestClass();
	arr[9] = new(pool.allocate_raw()) TestClass();


	for(int i = 0; i<10; i++) {
		cout << pool.deallocate_raw(arr[i]) << endl;
	}

	//pool.deallocate(arr[5]);
	//pool.deallocate(arr[5]);

	//arr[10] = new(pool.allocate()) TestClass();

	return 1;

	arr[0] = pool.allocate_constructed();
	arr[1] = pool.allocate_constructed();
	arr[2] = pool.allocate_constructed();
	arr[3] = pool.allocate_constructed();
	arr[4] = pool.allocate_constructed();
	arr[5] = pool.allocate_constructed();
	arr[6] = pool.allocate_constructed();
	arr[7] = pool.allocate_constructed();
	arr[8] = pool.allocate_constructed();
	arr[9] = pool.allocate_constructed();

	//pool.deallocate(arr[5]);
	//pool.deallocate_destroy(arr[5]);
	//pool.deallocate_destroy(arr[1]);
	//new(pool.allocate()) TestClass()
	//pool.deallocate_object(arr[5]);
	//pool.deallocate_object(arr[5]);
	//pool.allocate_object();

	for(int i = 0; i<10; i++) pool.deallocate_constructed(arr[i]);


	//pool.allocate_object();
	//pool.deallocate(arr[5]);
	//pool.allocate();
	//arr[10] = pool.allocate_object();

	//pool.deallocate(arr[1]);
	//pool.deallocate(arr[5]);


	//arr[10] = new(pool.allocate()) TestClass();
	//arr[11] = new(pool.allocate()) TestClass();
//		pool.deallocate(arr[14]);
	//cout << tmp_str << endl;


	return 1;

	*/
	// start R14P session
	r14p::R14PSession* r14ps = r14p::init_session();
	TestCallback tcb;
	TestCallback2 tcb2;
	// set callback for NEW_CLIENT event
	r14ps->set_callback(r14p::R14P_ET_CLIENT_INBOUND_NEW, &tcb);
	// accept connections (server mode)
	r14ps->start_server(NULL, 10000);
	// connect to end point
	r14p::R14PClient* r14p_client = r14ps->connect("127.0.0.1", 10000, 16, NULL, 0);


	r14p_client->set_callback(r14p::R14P_ET_STATELESS_OUTBOUND_NEW, &tcb2);


	unsigned char test_data[] = "ABCD";
	TestCallback3 tcb3;
	r14p_client->send_datagram(0, test_data, 4, &tcb3);

	sleep(1);

	r14p::R14PStream* stream = r14p_client->get_stream(0);
	if(stream != NULL){
		cout << "STREAM ADDR: " << stream << endl;
		//stream->get_uuid();

		r14p_client->get_stream(stream->get_uuid());

	}

	sleep(1);
	// disconnect client
	r14p_client->disconnect();
	// remove client, free memory
	r14ps->remove_client(r14p_client);
	// stop server
	r14ps->stop_server();
	// destroy session, free memory
	r14p::destroy_session(r14ps);

	return 1;

}
