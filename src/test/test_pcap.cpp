#include<pcap.h>
#include<iostream>
#include<m3ua.h>
#include<sccp.h>
#include<sctp.h>
#include<tcp_ip.h>
#include<fstream>
#include<iomanip>
#include<time.h>
#include<string.h>
#include<map>
//#include "TCMessage.h"
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

class A {
public:
	void test(){
		cout << "A::test" << endl;
	}
	void test2(){
		cout << "A::test2" << endl;
	}
};

class B: public A {
public:
	void test(){
		//A::test();
		cout << "B::test" << endl;
	}
};

void print_hex(unsigned char* data, int data_length){
	cout << "==============" << endl;
	for(int k = 0; k<data_length; k++){
		cout << setfill('0') << setw(2) << hex << (int)(data[k] & 0xff)<< " ";
	}
	cout << endl;
	cout << "==============" << endl;

}
int main(){
	/*
		A a1;
		B b1;
		A* a = &b1;
		a->test2();
		return 1;
	*/
	   //temporary packet buffers
	   struct pcap_pkthdr header; // The header that pcap gives us
	   const u_char *packet; // The actual packet

	    pcap_t *handle;
	    char errbuf[PCAP_ERRBUF_SIZE]; //not sure what to do with this, oh well
	    handle = pcap_open_offline("/home/dfranusic/develp/dumps/gsms_sms.cap", errbuf);

	    tcpip::ETHHeader* ethh = new tcpip::ETHHeader();
	    tcpip::IPHeader* iph = new tcpip::IPHeader();
	    sctp::SCTPPacket* sctpp = new sctp::SCTPPacket();
	    m3ua::M3UAPacket* m3uap = new m3ua::M3UAPacket();
	    m3ua::ProtocolData* m3ua_pdata = NULL;
	    m3ua::M3UAParam* m3ua_param = NULL;
	    sccp::SCCPMessage* sccpm = NULL;
	    sccp::UDT_UnitData* sccp_udt = NULL;
	    //TCMessage_t* tcm = NULL;
	    //asn_dec_rval_t rval;

	    // sctp pool
	    sctp::ChunkPool* sctp_chunk_pool = new sctp::ChunkPool();
	    sctp_chunk_pool->set_pool_size(100);
	    sctp_chunk_pool->init_pool();
	    // m3ua pool
	    m3ua::M3UAPool* m3ua_pool = new m3ua::M3UAPool();
	    m3ua_pool->set_pool_size(10, 10);
	    m3ua_pool->init_pool();
	    // sccp pool
	    sccp::SCCPPool* sccp_pool = new sccp::SCCPPool();
	    sccp_pool->set_pool_size(10, 10);
	    sccp_pool->init_pool();

		timespec time1, time2;

		/*
		clock_gettime(0, &time1);
		handle = pcap_open_offline("/home/dfranusic/develp/dumps/gsms_sms.cap", errbuf);
		clock_gettime(0, &time2);
		cout<<diff(time1,time2).tv_sec<<":"<< (diff(time1,time2).tv_nsec) << " msec" << endl;
	*/


		//clock_gettime(0, &time1);
		sctp::Data* data_chunk = NULL;
		sctp::Chunk* sctp_chunk = NULL;
		unsigned int c = 0;
		cout << "Allocating memory..." << endl;
		unsigned char* tmp_buffer = new unsigned char[1000*1004800];
		unsigned char* tmp_address = tmp_buffer;
		unsigned long total_bytes = 0;

		cout << "Loading packets from file to memory..." << endl;

		for(int i = 0; i<1600; i++){
		    handle = pcap_open_offline("/home/dfranusic/develp/dumps/gsms_sms.cap", errbuf);
		    while ((packet = pcap_next(handle,&header))) {
		    	memcpy(tmp_buffer, packet, header.caplen);
		    	total_bytes += header.caplen;
		    	tmp_buffer += 1000;
		    	/*
		    	c++;
		    	// eth
		    	tcpip::get_eth_header((unsigned char*)packet, header.caplen, ethh);
		    	// ip
		    	if(ethh->ether_type == tcpip::IP){
		    		// sctp
		    		tcpip::get_ip_header(ethh->payload, ethh->payload_length, iph);
		    		if(iph->protocol == tcpip::SCTP){
		    			sctp::decode(iph->payload, iph->payload_length, sctpp, sctp_chunk_pool);
		    			data_chunk = sctpp->get_chunk(sctp::M3UA);
		    			if(data_chunk != NULL){
		    				//for(int k = 0; k<data_chunk->user_data_length; k++){
		    				//	cout << setfill('0') << setw(2) << hex << (int)(data_chunk->user_data[k] & 0xff)<< " ";
		    				//}
		    				//cout<<endl;
		    				//cout<<endl;

		    				// m3ua
		    				m3ua::decode(data_chunk->user_data, data_chunk->user_data_length, m3uap, m3ua_pool);
		    			}
		    		}
		    	}
		    	*/
		    }
		    pcap_close(handle);


		}
		cout << "Decoding packets from memory..." << endl;

		tmp_buffer = tmp_address;
		clock_gettime(0, &time1);

		for(int i = 0; i<1004800; i++){
			//cout << i << endl;
	    	c++;
	    	// eth
	    	tcpip::get_eth_header(tmp_buffer, 1000, ethh);
	    	// ip
	    	if(ethh->ether_type == tcpip::IP){
	    		tcpip::get_ip_header(ethh->payload, ethh->payload_length, iph);
	    		// sctp
	    		if(iph->protocol == tcpip::SCTP){
	    			sctp::decode(iph->payload, iph->payload_length, sctpp, sctp_chunk_pool);
	    			//data_chunk = sctpp->get_chunk(sctp::M3UA);
	    			for(int j = 0; j<sctpp->chunks.size(); j++){
	    				sctp_chunk = sctpp->chunks[j];
	    				if(sctp_chunk->type == sctp::DATA){
	    					data_chunk = (sctp::Data*)sctp_chunk;
	    					if(data_chunk->payload_protocol_type == sctp::M3UA){
	    						// m3ua
			    				m3ua::decode(data_chunk->user_data, data_chunk->user_data_length, m3uap, m3ua_pool);
			    				if(m3uap->message_type == m3ua::DATA){
			    					//sccp::decode(m3uap->message->)
			    					m3ua_param = m3uap->message->get_parameter(m3ua::PROTOCOL_DATA);
			    					if(m3ua_param != NULL){
			    						m3ua_pdata = (m3ua::ProtocolData*)m3ua_param;
			    						if(m3ua_pdata->service_indicator == m3ua::SCCP){
			    							sccpm = sccp::decode(m3ua_pdata->user_protocol_data, m3ua_pdata->user_protocol_data_length, sccp_pool);
			    							if(sccpm->type == sccp::UDT_UNITDATA){
			    								sccp_udt = (sccp::UDT_UnitData*)sccpm;
			    								//print_hex(sccp_udt->data->value, sccp_udt->data->value_length);
											//rval = ber_decode(0, &asn_DEF_TCMessage, (void**)&tcm, sccp_udt->data->value, sccp_udt->data->value_length);
											//if(rval.code != RC_OK) cout << "ERR" << endl;
											//xer_fprint(stdout, &asn_DEF_TCMessage, tcm);
											//cout << endl;
                									//asn_DEF_TCMessage.free_struct(&asn_DEF_TCMessage, tcm, 0);
		                							//tcm = NULL;
											//tcm->present = TCMessage_PR_NOTHING;


			    							}

			    						}
			    					}
			    				}
			    				//for(int k = 0; k<data_chunk->user_data_length; k++){
			    				//	cout << setfill('0') << setw(2) << hex << (int)(data_chunk->user_data[k] & 0xff)<< " ";
			    				//}
			    				//cout<<endl;
			    				//cout<<endl;

	    					}
	    				}
	    			}
	    			//if(data_chunk != NULL){
	    				//for(int k = 0; k<data_chunk->user_data_length; k++){
	    				//	cout << setfill('0') << setw(2) << hex << (int)(data_chunk->user_data[k] & 0xff)<< " ";
	    				//}
	    				//cout<<endl;
	    				//cout<<endl;

	    				// m3ua
	    				//m3ua::decode(data_chunk->user_data, data_chunk->user_data_length, m3uap, m3ua_pool);
	    			//}
	    		}
	    	}
	    	tmp_buffer += 1000;

		}


		clock_gettime(0, &time2);
		int msec = (diff(time1,time2).tv_sec * 1000) + (diff(time1,time2).tv_nsec / 1000000);
		double gbit = ((total_bytes * 8) / (double)1000000000) / (msec / (double)1000);
		cout << "Packet count: " << c << endl;
		cout << "Total bytes: " << total_bytes << endl;
		cout << "Total bandwith: " << gbit << " Gbit/s" << endl;
		cout << "Elapsed time: " << msec << " msec" << endl;
		cout << "Packets/sec: " << (int)(c / (msec / (double)1000)) << endl;
		tmp_buffer = tmp_address;
		delete[] tmp_buffer;


}



