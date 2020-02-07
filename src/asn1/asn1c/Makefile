asn1c_lexer:
	g++ -O2 -c -o ../../../bin/test/asn1_lexer.o asn1Lexer.c

asn1c_parser:
	g++ -O2 -c -o ../../../bin/test/asn1_parser.o asn1Parser.c

asn1c:
	g++ -O2 -I. -o ../../../bin/test/asn1c ../../../bin/test/asn1_parser.o ../../../bin/test/asn1_lexer.o asn1c.cpp -lantlr3c

clean:
	rm test
