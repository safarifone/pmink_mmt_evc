pmink_lexer:
	g++ -O2 -c -o ../../bin/test/pmink_lexer.o pminkLexer.c

pmink_parser:
	g++ -O2 -c -o ../../bin/test/pmink_parser.o pminkParser.c

cli_service:
	g++ -O2 -g -o ../../bin/test/cli_service -I. -I../utils \
	../../bin/test/pmink_parser.o \
	../../bin/test/pmink_lexer.o \
	cli_service.cpp \
	cli.cpp \
	../utils/antlr_utils.cpp \
	../utils/pmink_utils.cpp \
	-lantlr3c -lcurses -lrt -lboost_regex

clean:
	rm test
