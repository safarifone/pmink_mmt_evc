
#ifndef CLI_H_
#define CLI_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

// CTRL macro
#define CTRL(c) ((c) & 037)

namespace cli {
	enum CLINodeType {
		CLI_CONST = 0x01,
		CLI_METHOD = 0x02,
		CLI_SCRIPT = 0x03,
		CLI_PARAM = 0x04,
		CLI_UNKNOWN = -1
	};


	class CLIPattern {
	public:
		string name;
		string pattern;
	};

	class CLIItem {
	public:
		CLIItem();
		~CLIItem();
		CLIItem* parent;
		CLINodeType node_type;
		string name;
		string script_path;
		string type;
		string desc;
		vector<CLIItem*> children;
		// param only
		bool is_set;
		string param_value;

	};


	class CLIService {
	public:
		CLIService();
		~CLIService();
		int max_history;
		int history_index;
		void set_prompt(char* _prompt);
		void set_prompt(string* _prompt);
		void set_cli_tree(CLIItem* cli_tree);
		void start();
		void add_pattern(CLIPattern* ptrn);
		bool param_valid(string* param_value, string* param_type);
		CLIPattern* get_pattern(string* type);
		static void print_cli_tree(cli::CLIItem* tree, int depth);
	private:
		// void* here, trying to localize antlr specific refs and includes to antlr_utils only
		void* pmink_parser;
		// methods
		void init_colors();
		void print_cli_def(CLIItem* def, int level, int max_levels);
		void cli_auto_complete(CLIItem* def, string* line, int line_size, CLIItem* result, int* result_size);
		void search_cli_def(CLIItem* def, int current_level, int target_level, string* target, CLIItem* result);
		void add_to_history(string* _line);
		// vars
		CLIItem* cli_def;
		string prompt;
		string current_line;
		vector<string*> history;
		vector<CLIPattern*> patterns;
	};



}


#endif /* CLI_H_ */
