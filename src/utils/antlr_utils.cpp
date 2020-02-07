#include<antlr_utils.h>
using namespace std;


antlr::PMinkParser::PMinkParser(){
	input = NULL;
	tstream = NULL;
	parser = NULL;
	lexer = NULL;

}
antlr::PMinkParser::~PMinkParser(){
	// free input stream
	if(tstream != NULL){
		tstream->free(tstream);
		tstream = NULL;

	}

	if(input != NULL){
		input->close(input);
		input = NULL;

	}

	if(lexer != NULL){
		lexer->free(lexer);
		lexer = NULL;

	}

	if(parser != NULL){
		parser->free(parser);
		parser = NULL;

	}
}




// process pattern block
void antlr::cli_process_pattern_block(pANTLR3_BASE_TREE tmp_ast, cli::CLIService* cli_service){
	int n2 = tmp_ast->children->count;
	pANTLR3_BASE_TREE tmp_ci;
	string tmp_str;
	cli::CLIPattern* cli_ptrn = new cli::CLIPattern();

	// pattern name
	tmp_ci = (pANTLR3_BASE_TREE)tmp_ast->children->get(tmp_ast->children, 0);
	tmp_str = (char*)tmp_ci->toString(tmp_ci)->chars;
	// remove double quotes
	tmp_str.erase(remove(tmp_str.begin(), tmp_str.end(), '"' ), tmp_str.end());
	cli_ptrn->name = tmp_str;

	// patern regex
	tmp_ci = (pANTLR3_BASE_TREE)tmp_ast->children->get(tmp_ast->children, 1);
	tmp_str = (char*)tmp_ci->toString(tmp_ci)->chars;
	// remove PTRN quotes
	tmp_str.erase(tmp_str.begin(), tmp_str.begin() + 4);
	tmp_str.erase(tmp_str.end() - 4, tmp_str.end());
	cli_ptrn->pattern = tmp_str;

	// add to list
	cli_service->add_pattern(cli_ptrn);


}

// process config block
void antlr::process_config_block(pANTLR3_BASE_TREE tmp_ast, cli::CLIItem* tmp_cli){
	int n2 = tmp_ast->children->count;
	pANTLR3_BASE_TREE tmp_ci;
	string tmp_str;

	for(int j = 0; j<n2; j++){
		tmp_ci = (pANTLR3_BASE_TREE)tmp_ast->children->get(tmp_ast->children, j);
		tmp_str = (char*)tmp_ci->toString(tmp_ci)->chars;
		// id/name
		if(tmp_str == "ITEM_ID"){
			if(tmp_ci->children != NULL){
				if(tmp_ci->children->count > 0){
					tmp_ci = (pANTLR3_BASE_TREE)tmp_ci->children->get(tmp_ci->children, 0);
					tmp_str = (char*)tmp_ci->toString(tmp_ci)->chars;
					tmp_cli->name = tmp_str;
					//cout << "ID: " << tmp_str << endl;

				}

			}
		// type
		}else if(tmp_str == "ITEM_TYPE"){
			if(tmp_ci->children != NULL){
				if(tmp_ci->children->count > 0){
					tmp_ci = (pANTLR3_BASE_TREE)tmp_ci->children->get(tmp_ci->children, 0);
					tmp_str = (char*)tmp_ci->toString(tmp_ci)->chars;
					// remove double quotes
					tmp_str.erase(remove(tmp_str.begin(), tmp_str.end(), '"' ), tmp_str.end());
					tmp_cli->type = tmp_str;

					if(tmp_str == "METHOD") tmp_cli->node_type = cli::CLI_METHOD;
					else if(tmp_str == "SCRIPT") tmp_cli->node_type = cli::CLI_SCRIPT;
					else if(tmp_str == "CONST") tmp_cli->node_type = cli::CLI_CONST;
					else tmp_cli->node_type = cli::CLI_PARAM;

					// script param
					if(tmp_cli->node_type == cli::CLI_SCRIPT){
						if(tmp_ci->children != NULL){
							if(tmp_ci->children->count > 0){
								tmp_ci = (pANTLR3_BASE_TREE)tmp_ci->children->get(tmp_ci->children, 0);
								tmp_str = (char*)tmp_ci->toString(tmp_ci)->chars;
								// remove double quotes
								tmp_str.erase(remove(tmp_str.begin(), tmp_str.end(), '"' ), tmp_str.end());

								tmp_cli->script_path = tmp_str;
								/*
								// script path as first param
								cli::CLIItem* new_cli = new cli::CLIItem();
								new_cli->node_type = cli::CLI_PARAM;
								new_cli->name = tmp_str;

								tmp_cli->children.push_back(new_cli);
								*/
							}

						}

					}

				}
			}
		// description
		}else if(tmp_str == "ITEM_DESC"){
			if(tmp_ci->children != NULL){
				if(tmp_ci->children->count > 0){
					tmp_ci = (pANTLR3_BASE_TREE)tmp_ci->children->get(tmp_ci->children, 0);
					tmp_str = (char*)tmp_ci->toString(tmp_ci)->chars;
					// remove double quotes
					tmp_str.erase(remove(tmp_str.begin(), tmp_str.end(), '"' ), tmp_str.end());
					tmp_cli->desc = tmp_str;
					//cout << "Desc: " << tmp_str << endl;

				}
			}
		// item
		}else if(tmp_str == "CONFIG_ITEM" || tmp_str == "CONFIG_BLOCK"){
			cli::CLIItem* new_cli = new cli::CLIItem();
			process_config_block(tmp_ci, new_cli);
			new_cli->parent = tmp_cli;
			tmp_cli->children.push_back(new_cli);


		}

	}
}

// process cli patterns
void antlr::cli_process_patterns(pANTLR3_BASE_TREE p_ast_tree, cli::CLIService* cli_service){
	// build cli
	pANTLR3_BASE_TREE tmp_tree = NULL;
	string tmp_str;
	// node name/value
	// children
	if(p_ast_tree->children != NULL){
		// child count
		int n = p_ast_tree->children->size(p_ast_tree->children);
		for(int i = 0; i<n; i++){
			tmp_tree = (pANTLR3_BASE_TREE)p_ast_tree->children->get(p_ast_tree->children, i);
			tmp_str = (char*)tmp_tree->toString(tmp_tree)->chars;
			if(tmp_str == "TYPE_ROOT"){
				antlr::build_pattern_tree(tmp_tree, cli_service);
				break;
			}


		}
	}

}

// process cli config
void antlr::cli_process_config(pANTLR3_BASE_TREE p_ast_tree, cli::CLIItem* cli_tree_res){
	// build cli
	pANTLR3_BASE_TREE tmp_tree = NULL;
	string tmp_str;
	// node name/value
	// children
	if(p_ast_tree->children != NULL){
		// child count
		int n = p_ast_tree->children->size(p_ast_tree->children);
		for(int i = 0; i<n; i++){
			tmp_tree = (pANTLR3_BASE_TREE)p_ast_tree->children->get(p_ast_tree->children, i);
			tmp_str = (char*)tmp_tree->toString(tmp_tree)->chars;
			if(tmp_str == "CONFIG_ROOT"){
				cli_tree_res->name = "ROOT";
				antlr::build_cli_tree(tmp_tree, cli_tree_res);
				break;
			}


		}
	}
}

// build pattern tres
void antlr::build_pattern_tree(pANTLR3_BASE_TREE p_ast_tree, cli::CLIService* cli_service){
	cli::CLIItem* tmp_cli;
	pANTLR3_BASE_TREE tmp_ast;
	pANTLR3_BASE_TREE tmp_ci;
	string tmp_str;

	if(p_ast_tree->children != NULL){
		// child count
		int n = p_ast_tree->children->size(p_ast_tree->children);
		for(int i = 0; i<n; i++){
			tmp_ast = (pANTLR3_BASE_TREE)p_ast_tree->children->get(p_ast_tree->children, i);
			tmp_str = (char*)tmp_ast->toString(tmp_ast)->chars;
			if(tmp_str == "TYPE_ITEM"){
				cli_process_pattern_block(tmp_ast, cli_service);
				//cout << "TYPE ITEM!!!!!!!!!!" << endl;
			}

		}
	}

}

// build cli tree
void antlr::build_cli_tree(pANTLR3_BASE_TREE p_ast_tree, cli::CLIItem* cli_tree){
	cli::CLIItem* tmp_cli;
	pANTLR3_BASE_TREE tmp_ast;
	pANTLR3_BASE_TREE tmp_ci;
	string tmp_str;

	if(p_ast_tree->children != NULL){
		// child count
		int n = p_ast_tree->children->size(p_ast_tree->children);
		for(int i = 0; i<n; i++){
			tmp_ast = (pANTLR3_BASE_TREE)p_ast_tree->children->get(p_ast_tree->children, i);
			tmp_str = (char*)tmp_ast->toString(tmp_ast)->chars;
			if(tmp_str == "CONFIG_ITEM" || tmp_str == "CONFIG_BLOCK"){
				tmp_cli = new cli::CLIItem();
				process_config_block(tmp_ast, tmp_cli);
				tmp_cli->parent = cli_tree;
				cli_tree->children.push_back(tmp_cli);

			}

		}
	}

}
// print ast tree
void antlr::print_tree(pANTLR3_BASE_TREE tree, int depth){
	pANTLR3_BASE_TREE tmp_tree;
	int n;
	// padding
	for(int i = 0; i<depth; i++) cout << "  ";
	// node name/value
	cout << tree->toString(tree)->chars << endl;
	// children
	if(tree->children != NULL){
		// child count
		n = tree->children->size(tree->children);
		for(int i = 0; i<n; i++){
			tmp_tree = (pANTLR3_BASE_TREE)tree->children->get(tree->children, i);
			// print
			print_tree(tmp_tree, depth + 1);
		}
	}

}
void antlr::no_error_report (pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8 * tokenNames) {
	// no errors reported to stdout
}

// tokenize line, reuse
void antlr::parse_line(string* data, string* result, int result_max_size, int* result_size, void* parser_info){
	parse_line(data, result, result_max_size, result_size, (PMinkParser*)parser_info);
}


// tokenize line, reuse
void antlr::parse_line(string* data, string* result, int result_max_size, int* result_size, PMinkParser* parser_info){
	if(parser_info == NULL) return;

	pANTLR3_BASE_TREE tmp_tree = NULL;
	string tmp_str;

	// input stream
	parser_info->input->reuse(parser_info->input, (unsigned char*)data->c_str(), data->size(), (unsigned char*)"line_stream");

	// token stream
	parser_info->tstream->reset(parser_info->tstream);

	// parse and build ast
	pminkParser_lineParser_return ast = parser_info->parser->lineParser(parser_info->parser);
	// err check
	int err_c = parser_info->lexer->pLexer->rec->getNumberOfSyntaxErrors(parser_info->lexer->pLexer->rec);
	err_c += parser_info->parser->pParser->rec->getNumberOfSyntaxErrors(parser_info->parser->pParser->rec);


	*result_size = 0;
	//print_tree(ast.tree, 0);
	if(err_c == 0 && ast.tree != NULL){
		if(ast.tree->children != NULL){
			// child count
			int n = ast.tree->children->size(ast.tree->children);
			for(int i = 0; i<n; i++){
				// check buffer
				if(*result_size >= result_max_size) return;
				// inc result size
				(*result_size)++;
				// get node value
				tmp_tree = (pANTLR3_BASE_TREE)ast.tree->children->get(ast.tree->children, i);
				tmp_str = (char*)tmp_tree->toString(tmp_tree)->chars;
				// remove double quotes
				//tmp_str.erase(remove(tmp_str.begin(), tmp_str.end(), '"' ), tmp_str.end());
				// result
				result[i] = tmp_str;
			}
		}

	}


}


antlr::PMinkParser* antlr::create_parser(){
	PMinkParser* pp = new PMinkParser();
	// input stream
	pp->input = antlr3StringStreamNew((unsigned char*)"", ANTLR3_ENC_8BIT, 0, (unsigned char*)"line_stream");
	// lexer
	pp->lexer = pminkLexerNew(pp->input);
	// no error reporting
	pp->lexer->pLexer->rec->displayRecognitionError = &no_error_report;
	// token stream
	pp->tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(pp->lexer));
	// create parser
	pp->parser = pminkParserNew(pp->tstream);

	return pp;
}

// tokenize line
void antlr::parse_line(string* data, string* result, int result_max_size, int* result_size){
	pANTLR3_BASE_TREE tmp_tree = NULL;
	string tmp_str;


	// input stream
	pANTLR3_INPUT_STREAM input  = antlr3StringStreamNew((unsigned char*)data->c_str(), ANTLR3_ENC_8BIT, data->size(), (unsigned char*)"line_stream");
	// lexer
	ppminkLexer lexer = pminkLexerNew(input);
	// no error reporting
	lexer->pLexer->rec->displayRecognitionError = &no_error_report;
	// token stream
	pANTLR3_COMMON_TOKEN_STREAM tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
	// create parser
	ppminkParser parser = pminkParserNew(tstream);
	// no error reporting
	parser->pParser->rec->displayRecognitionError = &no_error_report;
	// parse and build ast
	pminkParser_lineParser_return ast = parser->lineParser(parser);
	// err check
	int err_c = lexer->pLexer->rec->getNumberOfSyntaxErrors(lexer->pLexer->rec);
	err_c += parser->pParser->rec->getNumberOfSyntaxErrors(parser->pParser->rec);


	*result_size = 0;
	//print_tree(ast.tree, 0);
	if(err_c == 0 && ast.tree != NULL){
		if(ast.tree->children != NULL){
			// child count
			int n = ast.tree->children->size(ast.tree->children);
			for(int i = 0; i<n; i++){
				// check buffer
				if(*result_size >= result_max_size) return;
				// inc result size
				(*result_size)++;
				// get node value
				tmp_tree = (pANTLR3_BASE_TREE)ast.tree->children->get(ast.tree->children, i);
				tmp_str = (char*)tmp_tree->toString(tmp_tree)->chars;
				// remove double quotes
				//tmp_str.erase(remove(tmp_str.begin(), tmp_str.end(), '"' ), tmp_str.end());
				// result
				result[i] = tmp_str;
			}
		}

	}


	// free input stream
	tstream->free(tstream);
	tstream = NULL;

	input->close(input);
	input = NULL;

	lexer->free(lexer);
	lexer = NULL;

	parser->free(parser);
	parser = NULL;


}


void antlr::free_mem(void* parser_info){
	if(parser_info != NULL){
		PMinkParser* pmink_parser = (PMinkParser*)parser_info;
		delete pmink_parser;

	}
}


