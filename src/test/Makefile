default:
	@echo "Choose..."

test_sctp:
	g++ -I../sctp -o ../../bin/test/test_sctp test_sctp.cpp ../sctp/sctp.cpp ../sctp/chunk.cpp -lsctp

test_cli:
	g++ -Wall -O3 -I../cli -o ../../bin/test/test_cli test_cli.cpp ../cli/cli.cpp \
	-lcurses \
	-lboost_regex


test_asn1:
	g++ -O3 -I../asn1 -I../asn1/itu_tcap -I../asn1/tcap_dialogue -o ../../bin/test/test_asn1 test_asn1.cpp \
	../asn1/itu_tcap/itu_tcap.cpp \
	../asn1/asn1.cpp \
	../asn1/tcap_dialogue/DialoguePDUs.cpp \
	-lrt

test_smpp:
	g++ -O2 -I../smpp -o ../../bin/test/test_smpp test_smpp.cpp \
	../smpp/smpp.cpp \
	-lrt


test_pcap:
	g++ -Wall -O2 -I../tcp_ip -I../sctp -I../m3ua -I../sccp -o ../../bin/test/test_pcap \
	test_pcap.cpp \
	../tcp_ip/tcp_ip.cpp \
	../sctp/sctp.cpp \
	../sctp/chunk.cpp \
	../m3ua/m3ua.cpp \
	../sccp/sccp.cpp \
	-lpcap -lrt




test_tcpip:
	g++ -I../tcp_ip -I../sctp -I../m3ua -I../sccp -o ../../bin/test/test_tcpip \
	test_tcpip.cpp \
	../tcp_ip/tcp_ip.cpp \
	../sctp/sctp.cpp \
	../sctp/chunk.cpp \
	../m3ua/m3ua.cpp \
	../sccp/sccp.cpp

test_m3ua:
	g++ -I../m3ua -o ../../bin/test/test_m3ua \
	test_m3ua.cpp \
	../m3ua/m3ua.cpp \
	-lrt


test_m2ua:
	g++ -I../tcp_ip -I../sctp -I../m2ua -I../sccp -I../mtp3 -o ../../bin/test/test_m2ua \
	test_m2ua.cpp \
	../tcp_ip/tcp_ip.cpp \
	../sctp/sctp.cpp \
	../sctp/chunk.cpp \
	../m2ua/m2ua.cpp \
	../mtp3/mtp3.cpp \
	../sccp/sccp.cpp

test_mtp2:
	g++ -I../tcp_ip -I../sctp -I../m2ua -I../sccp -I../mtp3 -I ../mtp2 -o ../../bin/test/test_mtp2 \
	test_mtp2.cpp \
	../tcp_ip/tcp_ip.cpp \
	../sctp/sctp.cpp \
	../sctp/chunk.cpp \
	../m2ua/m2ua.cpp \
	../mtp2/mtp2.cpp \
	../mtp3/mtp3.cpp \
	../sccp/sccp.cpp \
	-lrt


clean:
	rm test
