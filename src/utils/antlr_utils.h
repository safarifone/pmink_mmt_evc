#ifndef ANTLR_UTILS_H_
#define ANTLR_UTILS_H_

#include <iostream>
#include <algorithm>
#include <string>
#include <antlr3.h>
#include <pminkLexer.h>
#include <pminkParser.h>
#include <cli.h>
using namespace std;

namespace antlr {
	class PMinkParser {
	public:
		PMinkParser();
		~PMinkParser();
		pANTLR3_INPUT_STREAM input;
		pANTLR3_COMMON_TOKEN_STREAM tstream;
		ppminkParser parser;
		ppminkLexer lexer;

	};


	// methods
	PMinkParser* create_parser();
	void process_config_block(pANTLR3_BASE_TREE tmp_ast, cli::CLIItem* tmp_cli);
	void cli_process_pattern_block(pANTLR3_BASE_TREE tmp_ast, cli::CLIService* cli_service);
	void cli_process_config(pANTLR3_BASE_TREE p_ast_tree, cli::CLIItem* cli_tree_res);
	void cli_process_patterns(pANTLR3_BASE_TREE p_ast_tree, cli::CLIService* cli_service);
	void build_cli_tree(pANTLR3_BASE_TREE p_ast_tree, cli::CLIItem* cli_tree);
	void build_pattern_tree(pANTLR3_BASE_TREE p_ast_tree, cli::CLIService* cli_service);
	void print_tree(pANTLR3_BASE_TREE tree, int depth);
	void no_error_report (pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8 * tokenNames);
	void parse_line(string* data, string* result, int result_max_size, int* result_size);
	void parse_line(string* data, string* result, int result_max_size, int* result_size, PMinkParser* parser_info);
	void parse_line(string* data, string* result, int result_max_size, int* result_size, void* parser_info);
	void free_mem(void* parser_info);
}


#endif /* ANTLR_UTILS_H_ */
