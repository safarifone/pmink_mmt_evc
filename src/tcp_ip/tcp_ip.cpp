#include<iostream>
#include<tcp_ip.h>
#include<string.h>

tcpip::ETHHeader* tcpip::get_eth_header(unsigned char* data, int data_length){
	if(data != NULL && data_length > 0){
		ETHHeader* ethh = new ETHHeader();
		// destination
		ethh->destination_length = 6;
		ethh->destination = data;
		// move fwd
		data += 6;
		// source
		ethh->source_length = 6;
		ethh->source = data;
		// move fwd
		data += 6;
		// ether type
		ethh->ether_type = (EtherType)(((data[0] & 0xff) << 8) + (data[1] & 0xff));
		// move fwd
		data += 2;
		// payload
		ethh->payload_length = data_length - 14;
		ethh->payload = data;
		// result
		return ethh;

	}
	return NULL;
}

void tcpip::get_eth_header(unsigned char* data, int data_length, ETHHeader* ethh){
	if(data != NULL && data_length > 0 && ethh != NULL){
		// destination
		ethh->destination_length = 6;
		ethh->destination = data;
		// move fwd
		data += 6;
		// source
		ethh->source_length = 6;
		ethh->source = data;
		// move fwd
		data += 6;
		// ether type
		ethh->ether_type = (EtherType)(((data[0] & 0xff) << 8) + (data[1] & 0xff));
		// move fwd
		data += 2;
		// payload
		ethh->payload_length = data_length - 14;
		ethh->payload = data;
		// result

	}
}


tcpip::IPHeader* tcpip::get_ip_header(unsigned char* data, int data_length){
	if(data != NULL && data_length > 0){
		IPHeader* iph = new IPHeader();
		// last 4 bits are header length in 32bit words
		iph->header_length = (int)(*data & 0x0f)*32 / 8;
		// first four bits are IP version, we are shifting them 4 bits to the right
		iph->vesion = *data >> 4;
		// fwd
		data += 2;
		//IP total length(2 bytes) = IP header length + all the other following headers
		iph->total_length = ((data[0] & 0xff) << 8) + (data[1] & 0xff);
		// fwd
		data += 2;
		// identification
		iph->identification = ((data[0] & 0xff) << 8) + (data[1] & 0xff);
		// fwd
		data += 2;
		// fragmentation
		iph->do_not_fragment = (*data & 0x40) == 0x40;
		iph->more_fragments = (*data & 0x20) == 0x20;
		iph->fragment_offset = (((data[0] & 0x1f) << 8) + (data[1] & 0xff)) * 8;
		// fwd
		data += 2;
		// ttl
		iph->time_to_live = (*data & 0xff);
		// fwd
		data++;
		// protocol
		iph->protocol = (IPProtocolType)(*data & 0xff);
		// fwd
		data++;
		// checksum
		iph->checksum_length = 2;
		iph->checksum = data;
		// fwd
		data += 2;
		// source
		iph->source_length = 4;
		iph->source = data;
		// fwd
		data += 4;
		// destination
		iph->destination_length = 4;
		iph->destination = data;
		// fwd
		data += 4;
		// payload
		iph->payload_length = iph->total_length - iph->header_length;
		iph->payload = data;
		// result
		return iph;

	}
	return NULL;
}

void tcpip::get_ip_header(unsigned char* data, int data_length, IPHeader* iph){
	if(data != NULL && data_length > 0 && iph != NULL){
		// last 4 bits are header length in 32bit words
		iph->header_length = (int)(*data & 0x0f)*32 / 8;
		// first four bits are IP version, we are shifting them 4 bits to the right
		iph->vesion = *data >> 4;
		// fwd
		data += 2;
		//IP total length(2 bytes) = IP header length + all the other following headers
		iph->total_length = ((data[0] & 0xff) << 8) + (data[1] & 0xff);
		// fwd
		data += 2;
		// identification
		iph->identification = ((data[0] & 0xff) << 8) + (data[1] & 0xff);
		// fwd
		data += 2;
		// fragmentation
		iph->do_not_fragment = (*data & 0x40) == 0x40;
		iph->more_fragments = (*data & 0x20) == 0x20;
		iph->fragment_offset = (((data[0] & 0x1f) << 8) + (data[1] & 0xff)) * 8;
		// fwd
		data += 2;
		// ttl
		iph->time_to_live = (*data & 0xff);
		// fwd
		data++;
		// protocol
		iph->protocol = (IPProtocolType)(*data & 0xff);
		// fwd
		data++;
		// checksum
		iph->checksum_length = 2;
		iph->checksum = data;
		// fwd
		data += 2;
		// source
		iph->source_length = 4;
		iph->source = data;
		// fwd
		data += 4;
		// destination
		iph->destination_length = 4;
		iph->destination = data;
		// fwd
		data += 4;
		// payload
		iph->payload_length = iph->total_length - iph->header_length;
		iph->payload = data;

	}
}



tcpip::SLLHeader* tcpip::get_sll_header(unsigned char* data, int data_length){
	if(data != NULL && data_length > 0){
		SLLHeader* slh = new SLLHeader();
		slh->packet_type = ((data[0]  & 0xff)<< 8) + (data[1] & 0xff);
		// fwd
		data += 2;
		slh->address_type = ((data[0]  & 0xff)<< 8) + (data[1] & 0xff);
		// fwd
		data += 2;
		slh->source_length = 8;
		slh->source = data;
		// fwd
		data += slh->source_length;
		slh->protocol =  ((data[0]  & 0xff)<< 8) + (data[1] & 0xff);
		// fwd
		data += 2;
		slh->payload_length = data_length - 16;
		slh->payload = data;
		// result
		return slh;
	}

	return NULL;

}

tcpip::VLANHeader* tcpip::get_vlan_header(unsigned char* data, int data_length){
	if(data != NULL && data_length > 0){
		VLANHeader* vlanh = new VLANHeader();
		vlanh->priority = (VLANPriority)(*data & 0xe0);
		vlanh->cfi_indicator = (*data & 0x10) == 0x10;
		vlanh->vlan_identifier = ((data[0] & 0x0f) << 8) + (data[1] & 0xff);
		// fwd
		data += 2;
		vlanh->ether_type = (EtherType)(((data[0] & 0xff) << 8) + (data[1] & 0xff));
		// fwd
		data += 2;
		vlanh->payload_length = data_length - 4;
		vlanh->payload = data;
		// result
		return vlanh;
	}
	return NULL;
}

tcpip::TCPHeader* tcpip::get_tcp_header(unsigned char* data, int data_length){
	if(data != NULL && data_length > 0){
		TCPHeader* tcph = new TCPHeader();
		tcph->source = ((data[0] & 0xff) << 8) + (data[1] & 0xff);
		tcph->destination = ((data[2] & 0xff) << 8) + (data[3] & 0xff);
		tcph->payload_length = data_length - ((data[12] & 0xff) >> 4)* 32 / 8;
		data += (((data[12] & 0xff) >> 4)* 32 / 8);
		tcph->payload = data;
		return tcph;
	}
	return NULL;
}




