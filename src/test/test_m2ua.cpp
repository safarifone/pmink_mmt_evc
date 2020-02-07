#include<iostream>
#include<tcp_ip.h>
#include<sctp.h>
#include<m2ua.h>
#include<mtp3.h>
#include<sccp.h>
#include<fstream>
#include<iomanip>
#include<endian.h>

using namespace std;

int main(){
/*
	int test = 0x648002c0;
	char ct = 0x80;
	cout << hex << test << endl;
	cout << hex << htobe32(test) << endl;
	cout << hex << (0xff000000 | 0xff) << endl;
	unsigned int tmpi = 0x80000000;
	tmpi = (tmpi) >> 16;
	cout << hex << tmpi << endl;

	return 1;
*/
	//tcpip::TCPIP tcpip;
	ifstream ifs("/tmp/packet3.raw", ios::binary | ios::in | ios::ate);
	ifstream::pos_type fsize;
	char* memblock;
	if(ifs.is_open()){
		fsize = ifs.tellg();
		memblock = new char[fsize];
		ifs.seekg(0, ios::beg);
		ifs.read(memblock, (long)fsize);
		ifs.close();
		/*
		cout << "File contents, size: " << (int)fsize << endl;
		cout << "===== FILE ===============" << endl;
		for(int i = 0; i<fsize; i++){
			cout << setfill('0') << setw(2) << hex << ((int)memblock[i] & 0xff) << " ";

		}
		cout << endl;
		cout << "======= ETH PAYLOAD =============" << endl;
		tcpip::ETHHeader* ethh = tcpip.get_eth_header(memblock, (int)fsize);
		//cout << dec << ethh->ether_type << endl;
		cout << dec << "PAYLOAD LENGTH: " << ethh->payload_length << endl;
		for(int i = 0; i<ethh->payload_length; i++){
			cout << setfill('0') << setw(2) << hex << ((int)ethh->payload[i] & 0xff) << " ";

		}
		cout << endl << "====================" << endl;
		tcpip::IPHeader* iph = tcpip.get_ip_header(ethh->payload, ethh->payload_length);
		cout << dec << "IPH L: " << iph->header_length << endl;
		cout << dec << "IPH V: " << iph->vesion << endl;
		cout << dec << "IPH TTL: " << iph->time_to_live << endl;
		cout << dec << "IPH PROT: " << (int)iph->protocol << endl;
		cout << dec << "IPH PLD L: " << iph->payload_length << endl;
		for(int i = 0; i<ethh->source_length; i++){
			cout << setfill('0') << setw(2) << hex << ((int)ethh->source[i] & 0xff) << " ";

		}

		cout << endl << "====================" << endl;
		for(int i = 0; i<iph->payload_length; i++){
			cout << setfill('0') << setw(2) << hex << ((int)iph->payload[i] & 0xff) << " ";

		}
		cout << endl;
		cout << endl << "====================" << endl;
		sctp::SCTPPacket* sctpp = sctp::decode(iph->payload, iph->payload_length);
		for(int i = 0; i<sctpp->checksum_length; i++){
			cout << setfill('0') << setw(2) << hex << ((int)sctpp->checksum[i] & 0xff) << " ";

		}
		cout << endl << "====================" << endl;
		cout << "CHUNK COUNT: " << sctpp->chunks.size() << endl;
		sctp::Chunk* chunk =  sctpp->chunks[0];
		cout << "CHUNK 0 TYPE: " << chunk->type << endl;
		cout << dec << "CHUNK 0 LENGTH: " << chunk->length << endl;
		cout << dec << "CHUNK 0 SID: " << ((sctp::Data*)chunk)->stream_identifier << endl;
		cout << dec << "CHUNK 0 SEQ NUM: " << ((sctp::Data*)chunk)->sequence_number << endl;
		cout << dec << "CHUNK 0 PLD TYPE: " << ((sctp::Data*)chunk)->payload_protocol_type << endl;
		cout << dec << "CHUNK 0 USER DL: " << ((sctp::Data*)chunk)->user_data_length << endl;
		cout << endl << "====================" << endl;
		for(int i = 0; i<((sctp::Data*)chunk)->user_data_length; i++){
			cout << setfill('0') << setw(2) << hex << (int)(((sctp::Data*)chunk)->user_data[i] & 0xff)<< " ";

		}
		cout << endl << "======= M2UA =============" << endl;
		m2ua::M2UAPacket* m2uap = m2ua::decode(((sctp::Data*)chunk)->user_data, ((sctp::Data*)chunk)->user_data_length);
		cout << dec << "Version: " << m2uap->version << endl;
		cout << dec << "Message class: " << m2uap->message_class << endl;
		cout << dec << "Message type: " << (m2uap->message_type & 0x00ff) << endl;
		cout << dec << "Message length: " << m2uap->message_length << endl;
		cout << dec << "Message param count: " << m2uap->message->get_params_count()  << endl;
		m2ua::ProtocolData* pdata =  (m2ua::ProtocolData*)m2uap->message->get_parameter(m2ua::PROTOCOL_DATA_1);
		cout << endl;
		for(int i = 0; i<pdata->value_length; i++){
			cout << setfill('0') << setw(2) << hex << (int)(pdata->value[i] & 0xff)<< " ";
		}
		*/
		cout << endl;
		//mtp3::MTP3Packet* mtp3p =  mtp3::decode(pdata->value, pdata->value_length);
		mtp3::MTP3Packet* mtp3p =  mtp3::decode(memblock, (int)fsize);
		cout << dec << "Network indicator: " << mtp3p->network_indicator << endl;
		cout << dec << "Service indicator: " << mtp3p->service_indicator << endl;
		cout << dec << "Label DPC: " << mtp3p->label.dpc << endl;
		cout << dec << "Label OPC: " << mtp3p->label.opc << endl;
		cout << dec << "Label SLC: " << mtp3p->label.slc << endl;
		cout << dec << "SIF L: " << mtp3p->sif_length << endl;
		//for(int i = 0; i<mtp3p->sif_length; i++){
		//	cout << setfill('0') << setw(2) << hex << (int)(mtp3p->sif[i] & 0xff)<< " ";
		//}

		cout << dec << "MSG TYPE: " << mtp3p->signalling_message->message_type << " == " << mtp3::SLTM << endl;
		mtp3::Sltm* sltm = (mtp3::Sltm*)mtp3p->signalling_message;
		cout << "TEST PTRN L: " << sltm->test_pattern_length << endl;
		for(int i = 0; i<sltm->test_pattern_length; i++){
			cout << setfill('0') << setw(2) << hex << (int)(sltm->test_pattern[i] & 0xff)<< " ";
		}


		cout << endl;
		char mtp3_buffer[500];
		int mtp3_buffer_length = 500;
		int mtp3_result_length = 0;
		int mtp3_offset = 0;

		mtp3p->encode(mtp3_buffer, mtp3_buffer_length, mtp3_offset, &mtp3_result_length);
		for(int i = 0; i<mtp3_result_length; i++){
			cout << setfill('0') << setw(2) << hex << (int)(mtp3_buffer[i] & 0xff)<< " ";
		}
		cout << endl;


	}

}


