#ifndef TCP_IP_H_
#define TCP_IP_H_

namespace tcpip {
	enum IPProtocolType {
		TCP = 0x06,
		UDP = 0x11,
		SCTP = 0x84
	};

	enum EtherType {
		IP = 0x0800,
		VLAN = 0x8100

	};
	enum VLANPriority {
		BACKGROUND = 0x20,
		BEST_EFFORT = 0x00,
		EXCELLENT_EFFORT = 0x40,
		CRITICAL_APPLICATIONS = 0x60,
		VIDEO_100MS_LATENCY = 0x80,
		VOICE_10MS_LATENCY = 0xa0,
		INTERNETWORK_CONTROL = 0xc0,
		NETWORK_CONTROL = 0xe0
	};

	class IPHeader{
	public:
		int vesion;
		int header_length;
		int total_length;
		IPProtocolType protocol;
		int identification;
		int fragment_offset;
		bool do_not_fragment;
		bool more_fragments;
		int time_to_live;
		int checksum_length;
		unsigned char* checksum;
		int source_length;
		unsigned char* source;
		int destination_length;
		unsigned char* destination;
		int payload_length;
		unsigned char* payload;

	};

	class ETHHeader{
	public:
		unsigned int destination_length;
		unsigned char* destination;
		unsigned int source_length;
		unsigned char* source;
		unsigned int payload_length;
		unsigned char* payload;
		EtherType ether_type;

	};

	class VLANHeader{
	public:
		EtherType ether_type;
		VLANPriority priority;
		bool cfi_indicator;
		int vlan_identifier;
		int payload_length;
		unsigned char* payload;
	};

	class SLLHeader{
	public:
		int packet_type;
		int address_type;
		int address_length;
		int source_length;
		unsigned char* source;
		int protocol;
		int payload_length;
		unsigned char* payload;
	};

	class TCPHeader{
	public:
		int source;
		int destination;
		int payload_length;
		unsigned char* payload;

	};

	// eth header
	ETHHeader* get_eth_header(unsigned char* data, int data_length);
	void get_eth_header(unsigned char* data, int data_length, ETHHeader* ethh);
	// sll header
	SLLHeader* get_sll_header(unsigned char* data, int data_length);
	// vlan header
	VLANHeader* get_vlan_header(unsigned char* data, int data_length);
	// tcp header
	TCPHeader* get_tcp_header(unsigned char* data, int data_length);
	// ip header
	IPHeader* get_ip_header(unsigned char* data, int data_length);
	void get_ip_header(unsigned char* data, int data_length, IPHeader* iph);

}


#endif /* TCP_IP_H_ */
