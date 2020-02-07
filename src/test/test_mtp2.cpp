#include<iostream>
#include<mtp2.h>
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
	ifstream ifs("/tmp/mtp2.raw", ios::binary | ios::in | ios::ate);
	ifstream::pos_type fsize;
	char* memblock;
	if(ifs.is_open()){
		fsize = ifs.tellg();
		memblock = new char[fsize];
		ifs.seekg(0, ios::beg);
		ifs.read(memblock, (long)fsize);
		ifs.close();

		mtp2::MTP2Packet* mtp2p = mtp2::decode(memblock, (int)fsize);
		cout << "BSN: " << mtp2p->backward_seq_num << endl;
		cout << "BSNI: " << mtp2p->backward_seq_num_indicator << endl;
		cout << "FSN: " << mtp2p->fwd_seq_num << endl;
		cout << "FSNI: " << mtp2p->fwd_seq_num_indicator << endl;
		cout << "LI: " << mtp2p->length_indicator << endl;

		for(int i = 0; i<mtp2p->sif_length; i++){
			cout << setfill('0') << setw(2) << hex << (int)(mtp2p->sif[i] & 0xff)<< " ";
		}
		cout << endl;
		cout << "============ MTP2 ENCODER ==========" << endl;
		char mtp2_buffer[500];
		int mtp2_buffer_length = 500;
		int mtp2_result_length = 0;
		int mtp2_offset = 0;

		mtp2::MTP2Packet* new_mtp2 = new mtp2::MTP2Packet();
		new_mtp2->backward_seq_num_indicator = true;
		new_mtp2->backward_seq_num = 66;
		new_mtp2->fwd_seq_num = 110;
		new_mtp2->fwd_seq_num_indicator = true;
		new_mtp2->type = mtp2::MSU;
		new_mtp2->sif = mtp2p->sif;
		new_mtp2->sif_length = mtp2p->sif_length;
		new_mtp2->encode(mtp2_buffer, mtp2_buffer_length, mtp2_offset, &mtp2_result_length);


		for(int i = 0; i<mtp2_result_length; i++){
			cout << setfill('0') << setw(2) << hex << (int)(mtp2_buffer[i] & 0xff)<< " ";
		}


		cout << endl;
		cout << endl;


	}

}


