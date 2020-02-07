#ifndef SCTP_H_
#define SCTP_H_

#include <chunk.h>
#include <vector>
#include <netinet/in.h>
#include <netinet/sctp.h>

using namespace std;

namespace sctp{
	// dissection
	class SCTPPacket {
	public:
		SCTPPacket();
		~SCTPPacket();
		int source_port;
		int destination_port;
		int verification_tag_length;
		unsigned char* verification_tag;
		int checksum_length;
		unsigned char* checksum;
		vector<Chunk*> chunks;
		Chunk* get_chunk(ChunkType chunk_type);
		Data* get_chunk(PayloadProtocolType payload_type);
	};
	// main decode method
	SCTPPacket* decode(unsigned char* data, int data_length);
	void decode(unsigned char* data, int data_length, SCTPPacket* sctpp, ChunkPool* chunk_pool);

	// socket handling
	int init_sctp_server(unsigned long addr, int local_port);
	int shutdown_sctp_server(int socket);
	int get_client(int serverSock, sockaddr_in* sci);
	int init_sctp_client(unsigned long addr, int remote_port, int stream_count);
	int init_sctp_client_bind(unsigned long addr, unsigned long local_addr, int local_port, int remote_port, int stream_count);
	int send_sctp(int connSock, const void *msg, size_t msg_len, uint32_t ppid, int stream_id);
	int rcv_sctp(int connSock, const void *msg_buffer, unsigned int msg_buffer_size, int flags, sctp_sndrcvinfo *sndrcvinfo);
	int shutdown_sctp_client(int connSock);


}


#endif /* SCTP_H_ */
