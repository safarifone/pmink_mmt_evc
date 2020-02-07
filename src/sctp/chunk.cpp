#include<iostream>
#include<chunk.h>

// chunk pool
sctp::ChunkPool::ChunkPool() : chunk_count(10){

}

void sctp::ChunkPool::set_pool_size(int _chunk_count){
	chunk_count = _chunk_count;
}

void sctp::ChunkPool::init_chunk(ChunkType _chunk_type){
	CHUNK_POOL[_chunk_type] = new ChunkPoolItem[chunk_count];
	CHUNK_POOL[_chunk_type]->type = _chunk_type;
	CHUNK_POOL[_chunk_type]->set_pool_size(chunk_count);
	CHUNK_POOL[_chunk_type]->init_pool();

}

sctp::Chunk* sctp::ChunkPool::request_chunk(ChunkType chunk_type){
	//std::cout<<"request_chunk "<< chunk_type << "->" <<  CHUNK_POOL[chunk_type] << std::endl;

	return CHUNK_POOL[chunk_type]->request_item();

}

void sctp::ChunkPool::init_pool(){
	/*
		_UNKNOWN_CHUNK_ = -1,
		DATA = 0x00,
		INIT = 0x01,
		INIT_ACL = 0x02,
		SACK = 0x03,
		HEARTBEAT = 0x04,
		HEARTBEAT_ACK = 0x05,
		ABORT = 0x06,
		SHUTDOWN = 0x07,
		SHUTDOWN_ACK = 0x08,
		ERROR = 0x09,
		COOKIE_ECHO = 0x0a,
		COOKIE_ACK = 0x0b,
		ECNE = 0x0c,
		CWR = 0x0d,
		SHUTDOWN_COMPLETE = 0x0e	 */
	init_chunk(INIT);
	init_chunk(DATA);
	init_chunk(INIT_ACL);
	init_chunk(SACK);
	init_chunk(HEARTBEAT);
	init_chunk(HEARTBEAT_ACK);
	init_chunk(ABORT);
	init_chunk(SHUTDOWN);
	init_chunk(SHUTDOWN_ACK);
	init_chunk(ERROR);
	init_chunk(COOKIE_ECHO);
	init_chunk(COOKIE_ACK);
	init_chunk(ECNE);
	init_chunk(CWR);
	init_chunk(SHUTDOWN_COMPLETE);

}


// chunk pool item
sctp::ChunkPoolItem::ChunkPoolItem(){
	pool = NULL;
	next_free_item = NULL;
	total_count = 0;
	free_count = 0;
}


sctp::Chunk* sctp::ChunkPoolItem::create_chunk(ChunkType _chunk_type){
	switch(_chunk_type){
		case DATA: return new Data();
		default: return new Chunk();
	}
}

sctp::Chunk* sctp::ChunkPoolItem::request_item(){
	Chunk* tmp = next_free_item;
	--free_count;
	if(free_count <= 0) free_count = total_count;
	next_free_item = pool[free_count - 1];

	return tmp;

}

void sctp::ChunkPoolItem::init_pool(){
	pool = new Chunk *[total_count];
	for(int i = 0; i<total_count; i++) pool[i] = create_chunk(type);
	next_free_item = pool[total_count - 1];

}

int sctp::ChunkPoolItem::get_free_count(){
	return free_count;
}

void sctp::ChunkPoolItem::set_pool_size(int _total_count){
	total_count = _total_count;
	free_count = total_count;

}

// base Chunk
sctp::Chunk::Chunk(){
	type = _UNKNOWN_CHUNK_;
	byte_pos = 0;
}
sctp::Chunk::~Chunk(){}

void sctp::Chunk::decode(unsigned char* data, int data_length){
	byte_pos++;
	flags = data[byte_pos++];
	length = ((data[byte_pos] << 8) + (data[byte_pos + 1] & 0xFF)) & 0xFFFF;
	byte_pos += 2;
}


int sctp::Chunk::getLength(unsigned char* data, int data_length){
	return ((data[2] << 8) + (data[3] & 0xFF)) & 0xFFFF;
}


// DATA chunk
sctp::Data::Data(){
	type = DATA;

}

sctp::Data::~Data(){

}

void sctp::Data::decode(unsigned char* data, int data_length){
	Chunk::decode(data, data_length);
	if(length > 4){
		// tsn
		tsn_length = 4;
		tsn = &data[byte_pos];
		byte_pos += 4;
		// stream id
		stream_identifier = (((data[byte_pos] << 8) & 0xff) + (data[byte_pos + 1] & 0xFF)) & 0xFFFF;
		byte_pos += 2;
		// sequence num
		sequence_number = ((data[byte_pos] << 8) + (data[byte_pos + 1] & 0xFF)) & 0xffff;
		byte_pos += 2;
		// payload type
		payload_protocol_type = (PayloadProtocolType)((	(data[byte_pos] << 24) +
														(data[byte_pos+1] << 16) +
														(data[byte_pos+2] << 8) +
														(data[byte_pos+3] & 0xFF)) & 0xFFFF);
		byte_pos += 4;
		// payload
		user_data_length = length - 16;
		user_data = &data[byte_pos++];
	}
}
