#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <antlr_utils.h>
#include <pmink_utils.h>
#include <stdio.h>

using namespace std;




void print_help(){
	cout << "cli_service - pMINK CLI service" << endl;
	cout << "Copyright (c) 2012 Release14.org" << endl;
	cout << "Usage: cli_service [options]" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << " -f\tspecify cli definition file" << endl;

}




int main(int argc, char** argv){

	int opt;
	pANTLR3_UINT8 fName = NULL;
	pANTLR3_INPUT_STREAM input;
	ppminkLexer lxr;
	pANTLR3_COMMON_TOKEN_STREAM tstream;
	ppminkParser psr;
	pminkParser_input_return ast;


	if(argc == 1){
		print_help();
		return 1;
	}else{
		while ((opt = getopt(argc, argv, "f:")) != -1) {
			switch(opt){
				case 'f':
					fName   = (pANTLR3_UINT8)optarg;
					break;
			}
		}
	}

	if(fName != NULL){
		// input
		input  = antlr3FileStreamNew(fName, 0);
		if(input == NULL){
			ANTLR3_FPRINTF(stderr, "ERROR: Cannot open file \"%s\"\n", (char *)fName);
			exit(ANTLR3_ERR_NOMEM);
		}
		// lexer
		lxr = pminkLexerNew(input);

	  	if(lxr == NULL){
			ANTLR3_FPRINTF(stderr, "ERROR: Cannot create lexer!\n");
			exit(ANTLR3_ERR_NOMEM);
		}

	  	// token stream
		tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));
		if(tstream == NULL){
			ANTLR3_FPRINTF(stderr, "ERROR: Cannot allocate token stream!\n");
			exit(ANTLR3_ERR_NOMEM);
		}
		// parser
		psr = pminkParserNew(tstream);

		if(psr == NULL){
			ANTLR3_FPRINTF(stderr, "ERROR: Cannot create parser!\n");
			exit(ANTLR3_ERR_NOMEM);
		}

		// ast
		ast = psr->input(psr);

		// err check
		int err_c = lxr->pLexer->rec->getNumberOfSyntaxErrors(lxr->pLexer->rec);
		err_c += psr->pParser->rec->getNumberOfSyntaxErrors(psr->pParser->rec);

		if(err_c > 0){
			ANTLR3_FPRINTF(stderr, "ERROR: Invalid cli definition!\n");
			exit(ANTLR3_ERR_NOMEM);

		}

		// process cli ast, generate cli definition
		cli::CLIItem cli_tree;
		antlr::cli_process_config(ast.tree, &cli_tree);
		cli::CLIService::print_cli_tree(&cli_tree, 0);

		// set cli definition
		cli::CLIService cli_service;
		cli_service.set_cli_tree(&cli_tree);
		// get cli patterns
		antlr::cli_process_patterns(ast.tree, &cli_service);
		// start cli service
		cli_service.start();


		// free antlr memory
	    tstream->free(tstream);
	    tstream = NULL;

	    input->close(input);
	    input = NULL;

	    lxr->free(lxr);
	    lxr = NULL;

	    psr->free(psr);
	    psr = NULL;

	}



	return 0;
}


