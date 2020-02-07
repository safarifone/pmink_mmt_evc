#include<iostream>
#include<asn1.h>
#include<itu_tcap.h>
#include<DialoguePDUs.h>
#include<iomanip>
#include<fstream>
#include<time.h>
#include<curses.h>
#include <limits>
#include <sstream>


using namespace std;



void print_hex(unsigned char* data, int data_length){
	cout << "==============" << endl;
	for(int k = 0; k<data_length; k++){
		cout << setfill('0') << setw(2) << hex << (int)(data[k] & 0xff)<< " ";
	}
	cout << endl;
	cout << "==============" << endl;

}

void print_structure_names(asn1::ASN1Node* root_node, int depth){
	if(root_node != NULL){
		for(int i = 0; i<depth; i++) cout << "  ";
			if(root_node->node_type_name != NULL) cout << root_node->node_type_name << endl;
			else cout << "<UNDEFIED TYPE>" << endl;

		for(int i = 0; i<root_node->children.size(); i++){
			print_structure_names(root_node->children[i], depth + 1);
		}

	}else{
		for(int i = 0; i<depth; i++) cout << "  ";
		cout << "<OPTIONAL>" << endl;
	}

}



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
	cout << "Starting..." << endl;
	asn1::ASN1Node* tmp_asn = NULL;
	vector<asn1::ASN1Node*> tmp_vec;
	//int** asn_arr = new int *[10];
	//sleep(20);
	cout << "Allocating..." << endl;

	for(int i = 0; i<1000000; i++){
		tmp_vec.push_back(new asn1::ASN1Node());
		//asn_arr[i] = new int;
	}
	//sleep(20);
	cout << "Freeing..." << endl;
	for(int i = 0; i<1000000; i++){
		delete tmp_vec[i];
		//tmp_vec.push_back(new asn1::ASN1Node());
		//delete asn_arr[i];


	}
	tmp_vec.clear();
	//delete[] asn_arr;
	//asn_arr = NULL;

}



int main(int argc, char** argv){



	asn1::ASN1Node* root_node = new asn1::ASN1Node();

	root_node->tlv = new asn1::TLVNode();
	root_node->tlv->tag_value = 10;
	root_node->tlv->complexity = asn1::PRIMITIVE;
	root_node->tlv->tag_class = asn1::APPLICATION;



	unsigned char* buffer = new unsigned char[1024];

	asn1::TCMessage* tcm = new asn1::TCMessage();
	asn1::prepare(tcm, NULL);

	unsigned char tmp_data[] = {0, 0, 0};
	unsigned char* tmp_data2 = new unsigned char[128];
	root_node->set_linked_data(0, tmp_data, 3);





	//asn1::prepare_lengths(tcm, 0);
	//unsigned int tl = asn1::encode(buffer, 1024, tcm, 0);
	unsigned int tl = 0;
	//unsigned int tl = asn1::encode(buffer, 1024, tcm, 0);

	//print_hex(buffer, tl);
	//cout << dec << "TL: " << tl << endl;

	/*
	int req_bits = ceil(log2(128));
	int sept_bytes = ceil((double)req_bits / 8);
	cout << req_bits << endl;
	cout << sept_bytes << endl;
	*/

	//return 1;


	/*
	while(tmp_vec.size() > 0){
	//for(int i = 0; i<tmp_vec.size(); i++){
		tmp_asn = tmp_vec.back();
		tmp_vec.pop_back();
		delete tmp_asn;
		//delete tmp_vec.at(i);
	}
	tmp_vec.clear();
	vector<asn1::ASN1Node*>().swap( tmp_vec );
	tmp_vec.resize(0);
	*/

	//test_func();

	//sleep(20);

	//asn1::TCMessage* tcm_test_1 = new asn1::TCMessage();

	//tcm_test_1->tlv = new asn1::TLVNode();
	//delete tcm_test_1;



	//return 1;

	/*
	asn1::TCMessage* tcm = new asn1::TCMessage();
	print_structure_names(tcm, 0);
	delete tcm;
	return 1;
	*/
	//ifstream ifs("/home/dfranusic/tcap.raw", ios::binary | ios::in | ios::ate);
	//ifstream ifs("/home/dfranusic/ndef.raw", ios::binary | ios::in | ios::ate);
	//ifstream ifs;
	ifstream::pos_type fsize;
	char* memblock;

	timespec time1, time2;

	if(argc < 2 || argv[1] == NULL){
		cout << "Missing filename!" << endl;
		return 1;
	}


	ifstream ifs(argv[1], ios::binary | ios::in | ios::ate);


	if(ifs.is_open()){
		fsize = ifs.tellg();
		memblock = new char[fsize];
		ifs.seekg(0, ios::beg);
		ifs.read(memblock, (long)fsize);
		ifs.close();


		//print_hex((unsigned char*)memblock, (int)fsize);
		cout << flush;

		asn1::ASN1Pool* asn1_pool = new asn1::ASN1Pool();
		asn1_pool->init_pool();
		asn1::ASN1Node* root_node = new asn1::ASN1Node();
		asn1::TCMessage* tcm = new asn1::TCMessage();
		asn1::DialoguePDU* dpdu = new asn1::DialoguePDU();


		asn1::TCMessage* tcm_new = new asn1::TCMessage();
		tcm_new->prepare();

		unsigned long total_bytes = fsize * 1000000;
		int asn1_res = 0;
		//asn1::TLVNode* tlv = new asn1::TLVNode();
		uint64_t session_id;

		session_id = asn1::generate_session_id();


		clock_gettime(0, &time1);

		//tcm->_continue->_otid->linked_node->tlv->set_value(tmp_data2, 128);
		//tcm->_continue->_otid->linked_node->update_parents();

		//tcm->_continue->_otid->linked_node->tlv->set_value(tmp_data, );
		//tcm->_continue->_otid->linked_node->update_parents();
		//asn1::prepare(tcm_new, NULL);

		for(int i = 0; i<1000000; i++){
			//root_node = asn1_pool->request_asn1_node();
			//asn1::prepare_lengths(root_node->children[0], *session_id);
			//tcm->_continue->_otid->linked_node->tlv->set_value(tmp_data, 3);
			//tcm->_continue->_otid->linked_node->update_parents();
			//tl = asn1::encode(buffer, 1024, root_node->children[0], *session_id);

			session_id++;// = asn1::generate_session_id();
			root_node->children.clear();
			root_node->tlv = NULL;
			// decode with definition
			asn1_res = asn1::decode((unsigned char*)memblock, (int)fsize, root_node, tcm, asn1_pool, &session_id);

			// decode without definition
			//asn1_res = asn1::decode((unsigned char*)memblock, (int)fsize, root_node, asn1_pool);
			//asn1::combine(root_node, tcm);

		}
		clock_gettime(0, &time2);
		int msec = (diff(time1,time2).tv_sec * 1000) + (diff(time1,time2).tv_nsec / 1000000);

		double gbit = ((total_bytes * 8) / (double)1000000000) / (msec / (double)1000);

		//cout << "Packets/sec: " << (int)(c / (msec / (double)1000)) << endl;
		cout << "ENC L1: " << tl << endl;


		asn1::print_structure(root_node, 0);

		cout << dec;
		//cout << "Packet count: " << c << endl;
		cout << "Total bytes: " << total_bytes << endl;
		cout << "Total bandwith: " << gbit << " Gbit/s" << endl;
		cout << "Elapsed time: " << msec << " msec" << endl;



		//tcm_new->set_linked_data(1);
		//tcm_new->_continue->set_linked_data(1);

		//tcm_new->_continue->_otid->set_linked_data(1, tcm->_continue->_otid->linked_node->tlv->value, tcm->_continue->_otid->linked_node->tlv->value_length);


		//tcm_new->_continue->_dtid->set_linked_data(1, tcm->_continue->_dtid->linked_node->tlv->value, tcm->_continue->_dtid->linked_node->tlv->value_length);


		//tcm_new->_continue->_components->set_linked_data(1);
		//tcm_new->_continue->_components->get_child(0)->set_linked_data(1);
		//tcm_new->_continue->_components->get_child(0)->_invoke->set_linked_data(1);


		// invoke ID

		// set optional nodes
		tcm_new->_continue->set_components();
		tcm_new->_continue->_components->set_child(0);
		tcm_new->_continue->_components->get_child(0)->_invoke->set_parameter();
		tcm_new->prepare();


		tcm_new->_continue->_otid->set_linked_data(1, tcm->_continue->_otid->linked_node->tlv->value, tcm->_continue->_otid->linked_node->tlv->value_length);


		tcm_new->_continue->_dtid->set_linked_data(1, tcm->_continue->_dtid->linked_node->tlv->value, tcm->_continue->_dtid->linked_node->tlv->value_length);


		tcm_new->_continue->_components->get_child(0)->_invoke->_invokeID->set_linked_data(1, 	tcm->_continue->_components->get_child(0)->_invoke->_invokeID->linked_node->tlv->value,
																								tcm->_continue->_components->get_child(0)->_invoke->_invokeID->linked_node->tlv->value_length);


		// local value
		//tcm_new->_continue->_components->get_child(0)->_invoke->_opCode->set_linked_data(1);
		tcm_new->_continue->_components->get_child(0)->_invoke->_opCode->_localValue->set_linked_data(1,	tcm->_continue->_components->get_child(0)->_invoke->_opCode->_localValue->linked_node->tlv->value,
																											tcm->_continue->_components->get_child(0)->_invoke->_opCode->_localValue->linked_node->tlv->value_length);


		// parameter
		tcm_new->_continue->_components->get_child(0)->_invoke->_parameter->tlv->tag_value = 16;
		tcm_new->_continue->_components->get_child(0)->_invoke->_parameter->tlv->tag_class = asn1::UNIVERSAL;
		tcm_new->_continue->_components->get_child(0)->_invoke->_parameter->tlv->complexity = asn1::CONSTRUCTED;
		tcm_new->_continue->_components->get_child(0)->_invoke->_parameter->tlv->override_auto_complexity = true;
		//tcm_new->_continue->_components->get_child(0)->_invoke->_parameter->set_linked_data(1, tmp_data2, 128);

		tcm_new->_continue->_components->get_child(0)->_invoke->_parameter->set_linked_data(1, 	tcm->_continue->_components->get_child(0)->_invoke->_parameter->linked_node->tlv->value,
																								tcm->_continue->_components->get_child(0)->_invoke->_parameter->linked_node->tlv->value_length);






		tl = asn1::encode(buffer, 1024, tcm_new, 1);

		cout << "ENC L: " << tl << endl;


		ofstream out_file;
		out_file.open("/tmp/out", ios::out|ios::binary);
		out_file.write((char*)buffer, tl);
		out_file.close();









		print_hex(buffer, tl);
		print_hex((unsigned char*)memblock, (int)fsize);

		//print_hex(tlv->value, tlv->value_length);

		//cout << root_node->children[0]->children.size() << endl;

		if(asn1_res == 0){

			//asn1::combine(root_node, tcm);


			if(tcm->_continue->_components->get_child(0)->_invoke->_opCode->_localValue->has_linked_data(session_id - 1)){
				print_hex(	tcm->_continue->_components->get_child(0)->_invoke->_opCode->_localValue->linked_node->tlv->value,
							tcm->_continue->_components->get_child(0)->_invoke->_opCode->_localValue->linked_node->tlv->value_length);

			}

			//cout << tcm->_begin->_dialoguePortion->_explicit_element->_encoding->_single_ASN1_type->linked_node << endl;

			/*
			print_hex(	tcm->_begin->_dialoguePortion->_explicit_element->_encoding->_single_ASN1_type->linked_node->tlv->value,
						tcm->_begin->_dialoguePortion->_explicit_element->_encoding->_single_ASN1_type->linked_node->tlv->value_length);



			root_node->children.clear();
			root_node->tlv = NULL;

			asn1_res = asn1::decode(
					tcm->_begin->_dialoguePortion->_explicit_element->_encoding->children[0]->linked_node->tlv->value,
					tcm->_begin->_dialoguePortion->_explicit_element->_encoding->children[0]->linked_node->tlv->value_length,
					root_node, dpdu, asn1_pool, session_id);


			print_structure(root_node, 0);
			*/

			//print_hex(	((asn1::Component*)(tcm->_continue->_components->children[0]))->_invoke->_opCode->_localValue->tlv->value,
			//			((asn1::Component*)(tcm->_continue->_components->children[0]))->_invoke->_opCode->_localValue->tlv->value_length);

		}else{
			cout << "ASN.1 Decoder error: " << asn1_res << endl;
			switch(asn1_res){
				case 200: cout << "Invalid BER encoded file!" << endl; break;
			}
		}
		cout << flush;

		delete[] memblock;

	}


	return 0;
}



