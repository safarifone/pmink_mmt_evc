
#ifndef POOL_H_
#define POOL_H_

#include <iostream>
#include <new>

using namespace std;
namespace memory {

	// raw buffer class
	// wrapper for generic char buffer
	template <int COUNT>
	class MemChunk {
	public:
		unsigned char buffer[COUNT];
		unsigned int buffer_length;

		MemChunk(){
			buffer_length = 0;
		}

	};

	// memory pool
	template <typename T>
	class Pool {
	private:
		char* buffer;
		int chunk_count;
		int chunk_size;
		int mem_size;
		int next_free_mem;
		char** raw_free_list;
		char** constructed_free_list;
		int raw_free_size;
		int constructed_free_size;
		bool construted_mode;

		void* find_available(char** _source, int* _source_size){
			char* tmp = _source[--(*_source_size)];
			// set availability bit (bit 7) to 1 = BUSY
			*tmp |= 0x80;
			// forward one byte to actual buffer memory
			tmp++;

			//cout << "find_available: Found free chunk: " << (int*)tmp << ", index: " << (*_source_size) <<  endl;

			return tmp;
		}
	public:

		int get_chunk_count(){
			return chunk_count;
		}
		// constructors and destructors
		Pool(){
			constructed_free_size = 0;
			raw_free_size = 0;
			chunk_count = 0;
			chunk_size = 0;
			construted_mode = false;
		}
		Pool(int _chunk_count){
			init(_chunk_count);
		}
		~Pool(){
			if(chunk_count <= 0) return;
			if(construted_mode){
				T* tmp = NULL;
				char* tmp_c = NULL;
				for(int i = 0; i<constructed_free_size; i++){
					tmp_c = constructed_free_list[i];
					// fwd one byte
					++tmp_c;
					// set pointer to T object
					tmp = (T*)tmp_c;
					// call destructor
					tmp->~T();
				}
			}
			delete[] constructed_free_list;
			delete[] raw_free_list;
			delete[] buffer;

		}

		// init
		void init(int _chunk_count){
			construted_mode = false;
			// chunks
			chunk_count = _chunk_count;
			chunk_size = sizeof(T) + 1; // extra byte for extra info (availability byte)
			mem_size = chunk_count * chunk_size;

			// main buffer
			buffer = new char[mem_size];
			next_free_mem = 0;


			// free lists
			raw_free_list = new char* [chunk_count];
			constructed_free_list = new char* [chunk_count];
			raw_free_size = chunk_count;
			constructed_free_size = 0;


			//cout << "Pool item chunk size: " << chunk_size << endl;
			//cout << "Pool item chunk count: " << chunk_count << endl;
			//cout << "Pool total mem size: " << mem_size << ", " << (int*)buffer << endl;
			//cout << "Pool mem: " << (int*)buffer << endl;

			// init extra bytes
			for(int i = 0; i<mem_size; i += chunk_size){
				// bit 7 = AVAILABILITY (0 = AVAILABLE, 1 = BUSY)
				// bit 6 = CONSTRUCTED (0 = NO, 1 = YES)
				buffer[i] = 0;

				// link with list
				raw_free_list[i / chunk_size] = &buffer[i];
			}
		}
		// construct objects if not using raw memory
		void construct_objects(){
			if(chunk_count <= 0) return;
			T* tmp = NULL;
			char* tmp_c = NULL;
			for(int i = 0; i<chunk_count; i++){
				// allocate T
				tmp = new(allocate_raw()) T();
				// cast as char
				tmp_c = (char*)tmp;
				// reverse one byte
				--tmp_c;
				// set as AVAILABLE
				// set as CONSTRUCTED
				// 0x40 = 	bit 7 = 0 AVAILABLE
				//			bit 6 = 1 CONSTRUCTED
				//
				*tmp_c = 0x40;

				// link with list
				constructed_free_list[i] = tmp_c;
			}
			// update linked list size
			construted_mode = true;
			constructed_free_size = chunk_count;
			// disable raw linked list
			raw_free_size = 0;
		}


		// allocate raw memory chunk
		void* allocate_raw(){
			// check free list
			if(raw_free_size > 0){
				return find_available(raw_free_list, &raw_free_size);

			}

			//cout << "NO FREE CHUNKS! " << endl;
			return NULL;

		}
		// allocate already constructed object
		T* allocate_constructed(){
			// check free list
			if(constructed_free_size > 0){
				return (T*)find_available(constructed_free_list, &constructed_free_size);

			}

			//cout << "NO FREE CHUNKS! " << endl;
			return NULL;

		}
		// deallocate constructed object
		int deallocate_constructed(T* obj){
			if(chunk_count <= 0) return 4;

			if((obj != NULL) && (raw_free_size < chunk_count)){
				// set pointer
				char* tmp = (char*)obj;
				// rewind one byte
				--tmp;
				// check for BUSY bit
				if((*tmp & 0x80) != 0x80) {
					//cout << "deallocate ERROR, already in pool" << endl;
					return 2;

				}

				// check for constructed allocated memory
				if((*tmp & 0x40) != 0x40) {
					//cout << "deallocate ERROR, expecting constructed object" << endl;
					return 3;

				}

				// set availability byte to 0 = AVAILABLE
				*tmp &= 0x7f;
				// return to linked list
				constructed_free_list[constructed_free_size++] = tmp;
				//cout << "deallocate_object: Next free item index: " << (constructed_free_size - 1) << " - " << (int*)tmp << endl;
				return 0;

			}
			return 1;
		}
		// deallocate raw memory
		int deallocate_raw(T* obj){
			if(chunk_count <= 0) return 4;

			if(obj != NULL){
				// set pointer
				char* tmp = (char*)obj;
				// rewind one byte
				--tmp;
				// check for BUSY bit
				if((*tmp & 0x80) != 0x80) {
					//cout << "deallocate ERROR, already in pool" << endl;
					return 2;

				}


				// check for constructed allocated memory
				if((*tmp & 0x40) != 0x00) {
					//cout << "deallocate ERROR, expecting raw memory" << endl;
					return 3;

				}

				// call destructor
				obj->~T();
				// set availability byte to 0 = AVAILABLE
				*tmp &= 0x7f;
				// return to linked list
				raw_free_list[raw_free_size++] = tmp;
				//cout << "deallocate: Next free item index: " << (raw_free_size - 1) << " - " << (int*)tmp << endl;
				return 0;

			}
			return 1;
		}


	};

};


#endif /* POOL_H_ */
