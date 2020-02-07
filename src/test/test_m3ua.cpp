#include<iostream>
#include<m3ua.h>
#include<fstream>
#include<iomanip>
#include<time.h>
#include<map>
using namespace std;

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
int calc (int a, int b)
{
    return a + b;
}

int main(){
	/*
	int test = 0;
	unsigned char ch1 = 0x64;
	unsigned char ch2 = 0x80;
	unsigned char ch3 = 0x02;
	unsigned char ch4 = 0xc0;
	test = (ch1 << 24) + (ch2 << 16) + (ch3 << 8) + ch4;
	cout << hex << test << endl;

	return 1;
	*/
	/*
	int** test_ip = new int *[10];

	test_ip[0] = new int;
	test_ip[1] = new int;

	*test_ip[0] = 1000;
	*test_ip[1] = 2000;

	cout << test_ip[0] << endl;
	cout << test_ip[1] << endl;
	cout << *test_ip[0] << endl;
	cout << *test_ip[1] << endl;
	return 1;
	*/
/*
	map<int, m3ua::M3UAParam**> test_map;

	test_map[m3ua::PROTOCOL_DATA] = new m3ua::M3UAParam* [10];

	test_map[m3ua::PROTOCOL_DATA][0] = new m3ua::ProtocolData();
	test_map[m3ua::PROTOCOL_DATA][1] = new m3ua::ProtocolData();

	m3ua::M3UAParam** tmp_param = test_map[m3ua::PROTOCOL_DATA];
	//tmp_param++;
	cout << tmp_param << endl;

	return 1;
*/
	ifstream ifs("/tmp/m3ua.raw", ios::binary | ios::in | ios::ate);
	ifstream::pos_type fsize;
	char* memblock;
	if(ifs.is_open()){
		fsize = ifs.tellg();
		memblock = new char[fsize];
		ifs.seekg(0, ios::beg);
		ifs.read(memblock, (long)fsize);
		ifs.close();



		// pool
		m3ua::M3UAPool* m3ua_pool = new m3ua::M3UAPool();
		// 10 messages of each, 10 parameters of each
		m3ua_pool->set_pool_size(10, 10);
		m3ua_pool->init_pool();
		// reusable m3ua packet
		m3ua::M3UAPacket* m3uap = new m3ua::M3UAPacket();

		timespec time1, time2;
		clock_gettime(0, &time1);

		for(int i = 0; i<1000000; i++){
			m3ua::decode((unsigned char*)memblock, (unsigned int)fsize, m3uap, m3ua_pool);
			//cout << ((m3ua::RoutingContext *)m3uap->message->get_parameter(m3ua::ROUTING_CONTEXT))->routing_context << endl;
			//m3ua_pool->return_param(m3uap->message->get_parameter(m3ua::PROTOCOL_DATA));
			//m3ua_pool->return_param(m3uap->message->get_parameter(m3ua::ROUTING_CONTEXT));
			//m3ua_pool->return_message(m3uap->message);


		}
		clock_gettime(0, &time2);

		cout<<diff(time1,time2).tv_sec<<":"<< (diff(time1,time2).tv_nsec / 1000000) << " msec" << endl;



		cout << endl;
		// free
		delete[] memblock;


	}
	//ETHHeader* ethh = tcpip.get_eth_header(NULL);
	//cout << ethh << endl;
}

