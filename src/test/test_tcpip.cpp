#include<iostream>
#include<tcp_ip.h>
#include<sctp.h>
#include<m3ua.h>
#include<sccp.h>
#include<fstream>
#include<iomanip>
using namespace std;


#define ___BIG_ENDIAN      0
#define ___LITTLE_ENDIAN   1

int TestByteOrder()
{
   short int word = 0x0001;
   char *byte = (char *) &word;
   return(byte[0] ? ___LITTLE_ENDIAN : ___BIG_ENDIAN);
}
int main(){
	tcpip::TCPIP tcpip;
	ifstream ifs("/tmp/packet.raw", ios::binary | ios::in | ios::ate);
	ifstream::pos_type fsize;
	char* memblock;
	if(ifs.is_open()){
		fsize = ifs.tellg();
		memblock = new char[fsize];
		ifs.seekg(0, ios::beg);
		ifs.read(memblock, (long)fsize);
		ifs.close();
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
		cout << endl << "======= M3UA =============" << endl;
		m3ua::M3UAPacket* m3uap = m3ua::decode(((sctp::Data*)chunk)->user_data, ((sctp::Data*)chunk)->user_data_length);
		cout << dec << "Version: " << m3uap->version << endl;
		cout << dec << "Message class: " << m3uap->message_class << endl;
		cout << dec << "Message type: " << m3uap->message_type << endl;
		cout << dec << "Message length: " << m3uap->message_length << endl;
		if(m3uap->message != NULL){
			cout << endl << "======= M3UA MESSAGE =============" << endl;
			m3ua::Data* data = (m3ua::Data*)m3uap->message;
			cout << dec << "NetworkAppearance: " << (data->get_parameter(m3ua::NETWORK_APPEARANCE) == NULL ? "n/a" : "available") << endl;
			cout << dec << "RoutingContext: " << (data->get_parameter(m3ua::ROUTING_CONTEXT) == NULL ? "n/a" : "available") << endl;
			cout << dec << "ProtocolData: " << (data->get_parameter(m3ua::PROTOCOL_DATA) == NULL ? "n/a" : "available") << endl;
			cout << dec << "CorrelationId: " << (data->get_parameter(m3ua::CORRELATION_ID) == NULL ? "n/a" : "available") << endl;
			if(data->get_parameter(m3ua::ROUTING_CONTEXT) != NULL){
				cout << "======= RoutingContext =============" << endl;
				m3ua::RoutingContext* rct = (m3ua::RoutingContext*)data->get_parameter(m3ua::ROUTING_CONTEXT);
				cout << "Value length: " << rct->value_length << endl;
				cout << "Value:  ";
				for(int i = 0; i<rct->value_length; i++){
					cout << setfill('0') << setw(2) << hex << (int)(rct->value[i] & 0xff) << " ";

				}
				cout << endl;

			}
			if(data->get_parameter(m3ua::NETWORK_APPEARANCE) != NULL){
				m3ua::NetworkAppearance* napp = (m3ua::NetworkAppearance*)data->get_parameter(m3ua::NETWORK_APPEARANCE);
				cout << "======= NetworkAppearance =============" << endl;
				cout << "Value length: " << napp->value_length << endl;
				cout << "Value:  ";
				for(int i = 0; i<napp->value_length; i++){
					cout << setfill('0') << setw(2) << hex << (int)(napp->value[i] & 0xff) << " ";

				}
				cout << endl;


			}
			if(data->get_parameter(m3ua::PROTOCOL_DATA) != NULL){
				m3ua::ProtocolData* pdata = (m3ua::ProtocolData*)data->get_parameter(m3ua::PROTOCOL_DATA);
				cout << "======= ProtocolData =============" << endl;
				cout << dec << "OPC: " <<pdata->originating_point_code << endl;
				cout << dec << "DPC: " <<pdata->destination_point_code << endl;
				cout << dec << "SI: " <<pdata->service_indicator << endl;
				cout << dec << "NI: " <<pdata->network_indicator << endl;
				cout << dec << "MP: " <<pdata->message_priority << endl;
				cout << dec << "SLS: " <<pdata->signalling_link_selection_code << endl;
				cout << dec << "user_protocol_data length: " << pdata->user_protocol_data_length << endl;
				cout << "Value:  ";
				for(int i = 0; i<pdata->user_protocol_data_length; i++){
					cout << setfill('0') << setw(2) << hex << (int)(pdata->user_protocol_data[i] & 0xff) << " ";

				}
				if(pdata->service_indicator == m3ua::SCCP){
					cout << endl << "======= SCCP =============" << endl;
					sccp::SCCPMessage* sccpm = sccp::decode(pdata->user_protocol_data, pdata->user_protocol_data_length);
					/*
					//sccp::GlobalTitle::prepareNew(sccp::GT_NATURE_OF_ADDRESS_INDICATOR_ONLY);
					cout << endl << "SCCP Message type: " << sccpm->type <<  endl;
					cout << endl << "SCCP Optional count: " << sccpm->optional_params.size() <<  endl;
					for(int i = 0; i<sccpm->optional_params.size(); i++){
						cout << dec << "SCCP Optional: " << sccpm->optional_params[i]->type <<  endl;

					}
					cout << endl;
					sccp::CR_ConnectionRequest* cr = (sccp::CR_ConnectionRequest*)sccpm;
					cout << hex << "Called PA GTI: " << cr->called_party_address->global_title_indicator << endl;

*/



					sccp::UDT_UnitData* udt = (sccp::UDT_UnitData*)sccpm;
					cout << hex << "Called PA GTI: " << udt->called_party_address->global_title_indicator << endl;
					cout << hex << "Subsys num: " << udt->called_party_address->subsystem_number << endl;
					sccp::GT_TTNPENOA* gt = (sccp::GT_TTNPENOA*)udt->called_party_address->global_title;
					cout << hex << "GT numbering plan: " << gt->numbering_plan << endl;
					cout << hex << "GT encoding scheme: " << gt->encoding_scheme << endl;
					cout << hex << "GT nai: " << gt->nature_of_address << endl;
					cout << hex << "GT address: ";
					for(int i = 0; i<gt->address_information_length; i++){
						cout << setfill('0') << setw(2) << hex << (int)(gt->address_information[i] & 0xff) << " ";

					}
					cout << endl;
					cout << hex << "OPTIONAL: " << udt->get_optional_params_count() << endl;

					cout << endl << "======= SCCP PAYLOAD =============" << endl;
					for(int i = 0; i<udt->data->value_length; i++){
						cout << setfill('0') << setw(2) << hex << (int)(udt->data->value[i] & 0xff) << " ";

					}
					cout << endl << "======= SCCP ENCODER TEST =============" << endl;

					sccp::RLSD_Released* rlsd = new sccp::RLSD_Released();
					rlsd->init_new();
					rlsd->destination_local_reference->dlr_value = 10940674;
					rlsd->source_local_reference->slr_value = 6013913;
					rlsd->release_cause->release_cause = sccp::RLC_SCCP_USER_ORIGINATED;

					char _sccp_buffer[500];
					int _sccp_buffer_length = 500;
					int _sccp_result_length = 0;
					int _sccp_offset = 0;
					for(int i = 0; i<_sccp_buffer_length; i++) _sccp_buffer[i] = 0xff;
					rlsd->encode(_sccp_buffer, _sccp_buffer_length, _sccp_offset, &_sccp_result_length);
					cout << dec << "ENC L: " << _sccp_result_length << endl;
					for(int i = 0; i<_sccp_result_length; i++){
						cout << setfill('0') << setw(2) << hex << (int)(_sccp_buffer[i] & 0xff) << " ";

					}
					cout << endl;



					//return 1;
					sccp::UDT_UnitData* new_udt = new sccp::UDT_UnitData();
					new_udt->init_new();
					new_udt->protocol_class->protocol_class = sccp::CLASS0;
					new_udt->protocol_class->message_handling = sccp::RETURN_MESSAGE_ON_ERROR;
					// called party
					new_udt->called_party_address->routing_indicator = sccp::ROUTE_ON_GT;
					new_udt->called_party_address->global_title_indicator = sccp::GT_TRANSLATION_TYPE_NUMNBERING_PLAN_ENCODING_NATURE_OF_ADDRESS;
					new_udt->called_party_address->ssn_indicator = true;
					new_udt->called_party_address->point_code_indicator = false;
					new_udt->called_party_address->subsystem_number = sccp::MSC;
					new_udt->called_party_address->global_title = new sccp::GT_TTNPENOA();
					sccp::GT_TTNPENOA* new_gt = (sccp::GT_TTNPENOA*)new_udt->called_party_address->global_title;
					new_gt->numbering_plan = sccp::ISDN_TELEPHONE;
					new_gt->encoding_scheme = sccp::BCD_ODD;
					new_gt->nature_of_address = sccp::NOA_INTERNATIONAL;
					char* test_gt = new char[6];
					test_gt[0] = 0x83;
					test_gt[1] = 0x46;
					test_gt[2] = 0x01;
					test_gt[3] = 0x20;
					test_gt[4] = 0x11;
					test_gt[5] = 0x01;
					new_gt->address_information = test_gt;
					new_gt->address_information_length = 6;
					// calling party
					new_udt->calling_party_address->routing_indicator = sccp::ROUTE_ON_GT;
					new_udt->calling_party_address->global_title_indicator = sccp::GT_TRANSLATION_TYPE_NUMNBERING_PLAN_ENCODING_NATURE_OF_ADDRESS;
					new_udt->calling_party_address->ssn_indicator = true;
					new_udt->calling_party_address->point_code_indicator = false;
					new_udt->calling_party_address->subsystem_number = sccp::MSC;
					new_udt->calling_party_address->global_title = new sccp::GT_TTNPENOA();
					new_gt = (sccp::GT_TTNPENOA*)new_udt->calling_party_address->global_title;
					new_gt->numbering_plan = sccp::ISDN_TELEPHONE;
					new_gt->encoding_scheme = sccp::BCD_ODD;
					new_gt->nature_of_address = sccp::NOA_INTERNATIONAL;

					test_gt = new char[6];
					test_gt[0] = 0x83;
					test_gt[1] = 0x76;
					test_gt[2] = 0x00;
					test_gt[3] = 0x70;
					test_gt[4] = 0x00;
					test_gt[5] = 0x07;
					new_gt->address_information = test_gt;
					new_gt->address_information_length = 6;

					new_udt->data->value_length = udt->data->value_length;
					new_udt->data->value = udt->data->value;


					char sccp_buffer[500];
					int sccp_buffer_length = 500;
					int sccp_result_length = 0;
					int sccp_offset = 0;
					for(int i = 0; i<sccp_buffer_length; i++) sccp_buffer[i] = 0xff;
					new_udt->encode(sccp_buffer, sccp_buffer_length, sccp_offset, &sccp_result_length);
					cout << dec << "ENC L: " << sccp_result_length << endl;
					for(int i = 0; i<sccp_result_length; i++){
						cout << setfill('0') << setw(2) << hex << (int)(sccp_buffer[i] & 0xff) << " ";

					}
					cout << endl;



				}
			}

			cout << endl << "======= M3UA ECODER TEST =============" << endl;
			char buffer[500];
			int buffer_length = 500;
			int result_length = 0;
			int offset = 0;
			for(int i = 0; i<buffer_length; i++) buffer[i] = 0xff;
			//m3uap->encode(&buffer[0], buffer_length, offset, &result_length);

			m3ua::M3UAPacket* m3uap2 = new m3ua::M3UAPacket();
			m3uap2->message_class = m3ua::TRANSFER;
			m3uap2->message_type = m3ua::DATA;
			m3uap2->message = new m3ua::Data();
			m3ua::Data* data2 = (m3ua::Data*)m3uap2->message;
			data2->add_parameter(m3ua::ROUTING_CONTEXT);
			data2->add_parameter(m3ua::PROTOCOL_DATA);

			m3ua::RoutingContext* rctx = (m3ua::RoutingContext*)data2->get_parameter(m3ua::ROUTING_CONTEXT);
			rctx->set_routing_context(8979);

			m3ua::ProtocolData* protdata = (m3ua::ProtocolData*)data2->get_parameter(m3ua::PROTOCOL_DATA);
			protdata->set_opc(8979);
			protdata->set_dpc(8961);
			protdata->set_si(m3ua::SCCP);
			protdata->set_ni(3);
			protdata->set_mp(0);
			protdata->set_sls(241);
			protdata->set_user_protocol_data(	((m3ua::ProtocolData*)data->get_parameter(m3ua::PROTOCOL_DATA))->user_protocol_data,
					((m3ua::ProtocolData*)data->get_parameter(m3ua::PROTOCOL_DATA))->user_protocol_data_length);

			m3uap2->encode(&buffer[0], buffer_length, offset, &result_length);

			for(int i = 0; i<result_length; i++){
				cout << setfill('0') << setw(2) << hex << (int)(buffer[i] & 0xff) << " ";

			}


			cout << endl;
			cout << dec << "ENC L: " << result_length << endl;

			//delete m3uap2;


		}
		delete sctpp;
		cout << endl;
		// free
		delete[] memblock;
		delete m3uap;


	}
	//ETHHeader* ethh = tcpip.get_eth_header(NULL);
	//cout << ethh << endl;
}

