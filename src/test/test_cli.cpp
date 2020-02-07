#include<iostream>
#include<string>
#include<boost/regex.hpp>
#include<cli.h>



int main(){

	char tmp_input[50];
	boost::regex rgx;
    // Set up the regular expression for case-insensitivity
	std::string str("ad");
	rgx.assign(".\\d", boost::regex_constants::icase);
	// match
	bool match = boost::regex_match(str, rgx);
	std::cout << "Match: " << match << std::endl;

	// cli
	cli::CLIService* cli_service = new cli::CLIService();
	cli_service->start();


}


