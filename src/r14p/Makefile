default:
	@echo "Choose..."

test_r14p:
	g++ -O2 -g -I. -I../pool -I../asn1 -I../asn1/r14p -I../sctp -o ../../bin/test/test_r14p \
	test_r14p.cpp r14p.cpp ../sctp/sctp.cpp ../sctp/chunk.cpp ../asn1/asn1.cpp ../asn1/r14p/r14p_asn1.cpp \
	-lsctp -lpthread -lrt



clean:
	rm test
