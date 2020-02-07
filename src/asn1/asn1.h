#ifndef ASN1_H_
#define ASN1_H_

#include <vector>
#include <cmath>
#include <string.h>
#include <time.h>
#include <stdint.h>

namespace asn1 {
	enum UniversalClassTag {
		EOC = 0x00,
		BOOLEAN = 0x01,
		INTEGER = 0x02,
		BIT_STRING = 0x03,
		OCTET_STRING = 0x04,
		_NULL_ = 0x05,
		OBJECT_IDENTIFIER = 0x06,
		OBJECT_DESCRIPTOR = 0x07,
		EXTERNAL = 0x08,
		REAL = 0x09,
		ENUMERATED = 0x0a,
		EMBEDDED_PDV = 0x0b,
		UTF8STRING = 0x0c,
		RELATIVE_OID = 0x0d,
		SEQUENCE = 0x10,
		SEQUENCE_OF = 0x10,
		SET = 0x11,
		NUMERIC_STRING = 0x12,
		PRINTABLE_STRING = 0x13,
		T61STRING = 0x14,
		VIDEOTEX_STRING = 0x15,
		IA5_STRING = 0x16,
		UTC_TIME = 0x17,
		GENERALIZED_TIME = 0x18,
		GRAPHIC_STRING = 0x19,
		VISIBLE_STRING = 0x1a,
		GENERAL_STRING = 0x1b,
		UNIVERSAL_STRING = 0x1c,
		CHARACTER_STRING = 0x1d,
		BMP_STRING = 0x1e,
		USE_LONG_FORM = 0x1f,
		// extra
		CHOICE = 0xff,
		UNKNOWN_UNIVERSAL_TAG = -1,
		ANY = -2

	};

	enum TagClass {
		UNIVERSAL = 0x00,
		APPLICATION = 0x40,
		CONTEXT_SPECIFIC = 0x80,
		PRIVATE = 0xc0,
		CLASS_UNKNOWN = -1

	};

	enum Complexity {
		PRIMITIVE = 0x00,
		CONSTRUCTED = 0x20,
		COMPLEXITY_UNKNOWN = -1
	};

	enum LengthType {
		DEFINITE_SHORT = 100,
		DEFINITE_LONG = 200,
		INDEFINITE = 300,
		LENGTH_TYPE_UNKNOWN = -1,

	};

	class TLVNode {
	private:
	public:
		TLVNode();
		~TLVNode();
		bool is_explicit;
		TagClass tag_class;
		Complexity complexity;
		bool override_auto_complexity;
		bool unlimited_size;
		LengthType length_type;
		UniversalClassTag uni_tag_class;
		int tag_value;
		int tag_value_size;
		unsigned char* value;
		unsigned int value_length;
		unsigned int value_length_size;
		// used when calculating parent lengths in update_parents
		unsigned int old_value_length;

		void set_value(unsigned char* _data, unsigned int _length);



	};

	class ASN1Node {
	public:
		ASN1Node();
		virtual ~ASN1Node();
		TLVNode* tlv;
		//bool marked;
		uint64_t session_id;
		char* node_type_name;
		std::vector<ASN1Node*> children;
		ASN1Node* linked_node;
		ASN1Node* parent_node;
		bool has_linked_data(uint64_t _session_id);
		void set_linked_data(uint64_t _session_id, unsigned char* _data, unsigned int _data_length);
		void set_linked_data(uint64_t _session_id, ASN1Node* _linked_node);
		void set_linked_data(uint64_t _session_id);
		void update_parents(uint64_t _session_id);
		void prepare();
		void set_session_id(uint64_t _session_id);
		// optional and sequence of
		virtual ASN1Node* create_node(unsigned int _index);
		virtual ASN1Node* get_next_node(unsigned int _index);


	};

	// standard asn1 classes
	class Any : public ASN1Node {
	public:
		Any();
		~Any();
	};


	class Choice : public ASN1Node {
	public:
		Choice();
		~Choice();
	};

	class Boolean : public ASN1Node {
	public:
		Boolean();
		~Boolean();
	};

	class Integer : public ASN1Node {
	public:
		Integer();
		~Integer();
	};

	class Bit_string : public ASN1Node {
	public:
		Bit_string();
		~Bit_string();
	};

	class Octet_string : public ASN1Node {
	public:
		Octet_string();
		~Octet_string();
	};

	class Null : public ASN1Node {
	public:
		Null();
		~Null();
	};

	class Object_identifier : public ASN1Node {
	public:
		Object_identifier();
		~Object_identifier();
	};

	class Object_descriptor : public ASN1Node {
	public:
		Object_descriptor();
		~Object_descriptor();
	};



	class Real : public ASN1Node {
	public:
		Real();
		~Real();
	};

	class Enumerated : public ASN1Node {
	public:
		Enumerated();
		~Enumerated();
	};

	class Embedded_pdv : public ASN1Node {
	public:
		Embedded_pdv();
		~Embedded_pdv();
	};

	class Utf8_string : public ASN1Node {
	public:
		Utf8_string();
		~Utf8_string();
	};

	class Relative_oid : public ASN1Node {
	public:
		Relative_oid();
		~Relative_oid();
	};

	class Sequence : public ASN1Node {
	public:
		Sequence();
		~Sequence();
	};

	class Sequence_of : public ASN1Node {
	public:
		Sequence_of();
		~Sequence_of();
		int _sequence_of_size;

	};

	class Set : public ASN1Node {
	public:
		Set();
		~Set();
	};

	class Numeric_string : public ASN1Node {
	public:
		Numeric_string();
		~Numeric_string();
	};

	class Printable_string : public ASN1Node {
	public:
		Printable_string();
		~Printable_string();
	};

	class T61_string : public ASN1Node {
	public:
		T61_string();
		~T61_string();
	};

	class Videotex_string : public ASN1Node {
	public:
		Videotex_string();
		~Videotex_string();
	};

	class Ia5_string : public ASN1Node {
	public:
		Ia5_string();
		~Ia5_string();
	};

	class Utc_time : public ASN1Node {
	public:
		Utc_time();
		~Utc_time();
	};

	class Generalized_time : public ASN1Node {
	public:
		Generalized_time();
		~Generalized_time();
	};

	class Graphic_string : public ASN1Node {
	public:
		Graphic_string();
		~Graphic_string();
	};

	class Visible_string : public ASN1Node {
	public:
		Visible_string();
		~Visible_string();
	};

	class General_string : public ASN1Node {
	public:
		General_string();
		~General_string();
	};

	class Universal_string : public ASN1Node {
	public:
		Universal_string();
		~Universal_string();
	};

	class Character_string : public ASN1Node {
	public:
		Character_string();
		~Character_string();
	};

	class Bmp_string : public ASN1Node {
	public:
		Bmp_string();
		~Bmp_string();
	};


	// ========== Eternal and related =============
	// EXTERNAL_encoding
	class EXTERNAL_encoding : public Choice {
	public:
		EXTERNAL_encoding();
		~EXTERNAL_encoding();
		// nodes
		Any* _single_ASN1_type;
		Octet_string* _octet_aligned;
		Bit_string* _arbitrary;

	};


	class External : public Sequence {
	public:
		External();
		~External();
		// nodes
		Object_identifier* _direct_reference;
		Integer* _indirect_reference;
		Object_descriptor* _data_value_descriptor;
		EXTERNAL_encoding* _encoding;

	};
	// ========================================

	// ASN1 pool classes
	class ASN1Pool {
	private:
		std::vector<TLVNode*> TLV_POOL;
		std::vector<ASN1Node*> ASN1_POOL;
		int tlv_count;
		int asn1_node_count;
		int free_tlv_count;
		int free_asn1_node_count;
		TLVNode* next_free_tlv;
		ASN1Node* next_free_asn1_node;
	public:
		ASN1Pool();
		~ASN1Pool();
		void set_pool_size(int _tlv_count, int _asn1_node_count);
		void init_pool();
		TLVNode* request_tlv();
		ASN1Node* request_asn1_node();
		int get_free_tlv_count();
		int get_free_asn1_node_count();


	};



	// helper methods
	void decode_length(unsigned char* data, unsigned int data_length, TLVNode* tlv);
	void decode_tag(unsigned char* data, unsigned int data_length, TLVNode* tlv);
	void encode_length(unsigned char* data, unsigned int data_length, TLVNode* tlv);
	void encode_prepared_length(unsigned char* data, unsigned int data_length, TLVNode* tlv);
	void prepare_length(TLVNode* tlv);
	void encode_prepared_tag(unsigned char* data, unsigned int data_length, TLVNode* tlv);
	void encode_tag(unsigned char* data, unsigned int data_length, TLVNode* tlv);
	void prepare_tag(TLVNode* tlv);
	int find_eoc(unsigned char* data, unsigned int data_length);
	ASN1Node* resolve_CHOICE(ASN1Node* needle, ASN1Node* stack);
	void prepare(ASN1Node* root_node, ASN1Node* parent);
	void set_session_id(ASN1Node* root_node, uint64_t _session_id);
	uint64_t generate_session_id();
	void print_structure(ASN1Node* root_node, int depth);

	// main decode method WITHOUT asn1 definition
	int decode(unsigned char* data, unsigned int data_length, ASN1Node* root_node, ASN1Pool* _asn1_pool);

	// main decode method WITH asn1 definition
	int decode(unsigned char* data, unsigned int data_length, ASN1Node* root_node, ASN1Node* root_defintion_node, ASN1Pool* _asn1_pool, uint64_t* _session_id);

	// encode method
	int encode(unsigned char* buffer, int buffer_length, ASN1Node* root_node, uint64_t _session_id);


	// combine dest(without asn1 definition) and source(with asn1 definition)
	void combine(ASN1Node* dest, ASN1Node* source);

}

#endif /* ASN1_H_ */
