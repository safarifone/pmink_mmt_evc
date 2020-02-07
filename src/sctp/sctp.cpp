#include <iostream>
#include <sctp.h>
#include <string.h>
#include <chunk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>

// socket handling methods

/*
 * If everything successful return connSock koji koristis kao
 * connection ID za slanje i primanje poruka
 */
int sctp::get_client(int serverSock, sockaddr_in* sci){
	int socket = -1;
	if(sci != NULL){
		// zero mem
		bzero((void*)sci, sizeof(sockaddr_in));
		//bzero((void*)scs, sizeof(sctp_status) );
		// sizes
		int size_sci = sizeof(sockaddr_in);
		//int size_scs = sizeof(sctp_status);
		// accept socket
		socket = accept(serverSock, (sockaddr*)sci, (socklen_t*)&size_sci);
		// validate socket
		/*
		if(socket > 0){
			getsockopt(socket, SOL_SCTP, SCTP_STATUS, scs, (socklen_t *)&size_scs );

		}
		*/

	}else{
		socket = accept(serverSock, NULL, NULL);

	}

	return socket;

}
int sctp::shutdown_sctp_server(int socket){
	return close(socket);
}

int sctp::init_sctp_server(unsigned long addr, int local_port){
	  int ret, serverSock, clientSock;
	  struct sockaddr_in servaddr;
	  struct sctp_event_subscribe events;

	  /* Create an SCTP TCP-Style Socket */
	  serverSock = socket( AF_INET, SOCK_STREAM, IPPROTO_SCTP );

	  /* Specify the peer endpoint to which we'll connect */
	  bzero( (void *)&servaddr, sizeof(servaddr) );
	  servaddr.sin_family = AF_INET;
	  servaddr.sin_port = htons(local_port);
	  if(addr == 0) servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	  else servaddr.sin_addr.s_addr = addr;

	  /* Bind to the wildcard address (all) and MY_PORT_NUM */
	  ret = bind( serverSock, (struct sockaddr *)&servaddr, sizeof(servaddr) );
	  if(ret == 0){
		  /* Enable receipt of SCTP Snd/Rcv Data via sctp_recvmsg */
		  memset( (void *)&events, 0, sizeof(events) );
		  events.sctp_data_io_event = 1;
		  ret = setsockopt( serverSock, SOL_SCTP, SCTP_EVENTS, (const void *)&events, sizeof(events) );


		  listen(serverSock, 5);
		  return serverSock;
	  }
	  return -1;
}

int sctp::init_sctp_client_bind(unsigned long addr, unsigned long local_addr, int local_port, int remote_port, int stream_count){
	int in, i, ret, flags, connSock;
	struct sockaddr_in servaddr;
	struct sctp_status status;
	struct sctp_event_subscribe events;
	struct sctp_initmsg initmsg;
	sockaddr_in local_bind;

	/* Create an SCTP TCP-Style Socket */
	connSock = socket( AF_INET, SOCK_STREAM, IPPROTO_SCTP );
	if(connSock < 0){
		return -1;
	}
	// local bind
	bzero( (void *)&local_bind, sizeof(sockaddr_in) );
	local_bind.sin_family = AF_INET;
	local_bind.sin_addr.s_addr = local_addr;
	local_bind.sin_port = htons(local_port);
	ret = bind(connSock, (sockaddr *)&local_bind, sizeof(sockaddr_in));
	if(ret < 0){
		shutdown(connSock, SHUT_RDWR);
		close(connSock);
		return -1;
	}

	/* Specify that a maximum of 5 streams will be available per socket */
	memset( &initmsg, 0, sizeof(initmsg) );
	initmsg.sinit_num_ostreams = stream_count;
	initmsg.sinit_max_instreams = stream_count;
	initmsg.sinit_max_attempts = 4;
	ret = setsockopt( connSock, IPPROTO_SCTP, SCTP_INITMSG, &initmsg, sizeof(initmsg) );

	/* Specify the peer endpoint to which we'll connect */
	bzero( (void *)&servaddr, sizeof(servaddr) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(remote_port);
	servaddr.sin_addr.s_addr = addr;


	/* Connect to the server */
	ret = connect( connSock, (struct sockaddr *)&servaddr, sizeof(servaddr) );
	if(ret == 0){
	  /* Enable receipt of SCTP Snd/Rcv Data via sctp_recvmsg */
	  memset( (void *)&events, 0, sizeof(events) );
	  events.sctp_data_io_event = 1;
	  ret = setsockopt( connSock, SOL_SCTP, SCTP_EVENTS, (const void *)&events, sizeof(events) );

	  /* Read and emit the status of the Socket (optional step) */
	  in = sizeof(status);
	  ret = getsockopt( connSock, SOL_SCTP, SCTP_STATUS, (void *)&status, (socklen_t *)&in );
	  return connSock;

	}else{
		shutdown(connSock, SHUT_RDWR);
		close(connSock);
	}
	return -1;
}

int sctp::init_sctp_client(unsigned long addr, int remote_port, int stream_count){
	int in, i, ret, flags, connSock;
	struct sockaddr_in servaddr;
	struct sctp_status status;
	struct sctp_event_subscribe events;
	struct sctp_initmsg initmsg;

	/* Create an SCTP TCP-Style Socket */
	connSock = socket( AF_INET, SOCK_STREAM, IPPROTO_SCTP );
	if(connSock < 0){
		return -1;
	}
	/* Specify that a maximum of 5 streams will be available per socket */
	memset( &initmsg, 0, sizeof(initmsg) );

	initmsg.sinit_num_ostreams = stream_count;
	initmsg.sinit_max_instreams = stream_count;
	initmsg.sinit_max_attempts = 4;
	ret = setsockopt( connSock, IPPROTO_SCTP, SCTP_INITMSG,  &initmsg, sizeof(initmsg) );

	/* Specify the peer endpoint to which we'll connect */
	bzero( (void *)&servaddr, sizeof(servaddr) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(remote_port);
	servaddr.sin_addr.s_addr = addr;


	/* Connect to the server */
	ret = connect( connSock, (struct sockaddr *)&servaddr, sizeof(servaddr) );
	if(ret == 0){
		/* Enable receipt of SCTP Snd/Rcv Data via sctp_recvmsg */
		memset( (void *)&events, 0, sizeof(events) );
		events.sctp_data_io_event = 1;
		ret = setsockopt( connSock, SOL_SCTP, SCTP_EVENTS, (const void *)&events, sizeof(events) );

		/* Read and emit the status of the Socket (optional step) */
		in = sizeof(status);
		ret = getsockopt( connSock, SOL_SCTP, SCTP_STATUS, (void *)&status, (socklen_t *)&in );
		return connSock;

	}else{
		shutdown(connSock, SHUT_RDWR);
		close(connSock);
	}
	return -1;
}

/*
 * RETURN 0 if sucessfully sent a message
 * RETURN 1 if unsucesfull!
 */
int sctp::send_sctp(int connSock, const void *msg, size_t msg_len, uint32_t ppid, int stream_id){
	if(sctp_sendmsg(connSock, msg, msg_len, NULL, 0, ppid, 0, stream_id, 0, 0))
        return (EXIT_SUCCESS);
    else
        return (EXIT_FAILURE);
}


/*
 * RETURN Number of bytes received.
 */
int sctp::rcv_sctp(int connSock, const void *msg_buffer, unsigned int msg_buffer_size, int flags, sctp_sndrcvinfo *sndrcvinfo){
	return sctp_recvmsg(connSock, (void *)msg_buffer, msg_buffer_size, (struct sockaddr *)NULL, 0, sndrcvinfo, &flags);

}


/*
 * SCTP Client SHUTDOWN
 */
int sctp::shutdown_sctp_client(int connSock){
	//int res = shutdown(connSock, SHUT_RDWR);
	return close(connSock);
	//return res;
}


// dissection
sctp::SCTPPacket::SCTPPacket(){
	// reserve mem for 10 initial chunks
	chunks.reserve(10);

}

sctp::SCTPPacket::~SCTPPacket(){
	Chunk* chunk;
	while(chunks.size() > 0){
		chunk = chunks[0];
		chunks.erase(chunks.begin());
		delete chunk;
	}
}

sctp::Chunk* sctp::SCTPPacket::get_chunk(ChunkType chunk_type){
	for(unsigned int i = 0; i<chunks.size(); i++) if(chunks[i]->type == chunk_type) return chunks[i];
	return NULL;
}

sctp::Data* sctp::SCTPPacket::get_chunk(PayloadProtocolType payload_type){
	Data* data = NULL;
	for(unsigned int i = 0; i<chunks.size(); i++){
		if(chunks[i]->type == DATA){
			data = (Data*)chunks[i];
			if(data->payload_protocol_type == payload_type) return data;

		}
	}
	return NULL;
}



void sctp::decode(unsigned char* data, int data_length, SCTPPacket* sctpp, ChunkPool* chunk_pool){
	if(data != NULL && data_length > 0 && sctpp != NULL){
		sctpp->chunks.clear();
		int byte_pos = 0;
		ChunkType ct = _UNKNOWN_CHUNK_;
		Chunk* chunk;
		int m;
		sctpp->source_port = (((data[byte_pos] << 8) & 0xff) + (data[byte_pos + 1] & 0xFF)) & 0xFFFF;
		byte_pos += 2;
		sctpp->destination_port = (((data[byte_pos] << 8) & 0xff) + (data[byte_pos + 1] & 0xFF)) & 0xFFFF;
		byte_pos += 2;
		// verification tag
		sctpp->verification_tag_length = 4;
		sctpp->verification_tag = &data[byte_pos];
		byte_pos += 4;
		// checksum
		sctpp->checksum_length = 4;
		sctpp->checksum = &data[byte_pos];
		byte_pos += 4;

		// chunk loop
		while(byte_pos < data_length){
			ct = (ChunkType)(data[byte_pos] & 0xFF);
			chunk = chunk_pool->request_chunk(ct);
			// unknown chunk error
			if(chunk == NULL) return;
			chunk->byte_pos = 0;
			/*
			switch(ct){
				case DATA:
					chunk = new Data();
					break;
				default:
					chunk = new Chunk();
					break;
			}
			*/
			// decode chunk
			chunk->decode(&data[byte_pos], data_length - byte_pos);
			sctpp->chunks.push_back(chunk);
			byte_pos += chunk->length;
			// chunk has to be a multiple of 4, if not, zero padding is added
			m = chunk->length % 4;
			byte_pos += (m > 0 ? 4 - m : 0);


		}
	}
}

sctp::SCTPPacket* sctp::decode(unsigned char* data, int data_length){
	if(data != NULL && data_length > 0){
		SCTPPacket* sctpp = new SCTPPacket();
		int byte_pos = 0;
		ChunkType ct = _UNKNOWN_CHUNK_;
		Chunk* chunk;
		int m;
		sctpp->source_port = (((data[byte_pos] << 8) & 0xff) + (data[byte_pos+1] & 0xFF)) & 0xFFFF;
		byte_pos += 2;
		sctpp->destination_port = (((data[byte_pos] << 8) & 0xff) + (data[byte_pos+1] & 0xFF)) & 0xFFFF;
		byte_pos += 2;
		// verification tag
		sctpp->verification_tag_length = 4;
		sctpp->verification_tag = &data[byte_pos];
		byte_pos += 4;
		// checksum
		sctpp->checksum_length = 4;
		sctpp->checksum = &data[byte_pos];
		byte_pos += 4;

		// chunk loop
		while(byte_pos < data_length){
			ct = (ChunkType)(data[byte_pos] & 0xFF);
			switch(ct){
				case DATA:
					chunk = new Data();
					break;
				default:
					chunk = new Chunk();
					break;
			}
			// decode chunk
			//std::cout << std::dec << "SCTP!!!!!!!!!!!!!!L: " << (data_length - byte_pos) << std::endl;
			chunk->decode(&data[byte_pos], data_length - byte_pos);
			sctpp->chunks.push_back(chunk);
			byte_pos += chunk->length;
			//std::cout << std::dec << "SCTP!!!!!!!!!!!!!!L: " << chunk->length << std::endl;
			// chunk has to be a multiple of 4, if not, zero padding is added
			m = chunk->length % 4;
			byte_pos += (m > 0 ? 4 - m : 0);


		}

		return sctpp;

	}
	return NULL;
}



