#include <pmink_utils.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <curses.h>


int pmink_utils::run_external(const char* script, char* result, int result_size){
	//std::cout << "run_external: " << script << std::endl;
    FILE* pipe = popen(script, "r");
    if (!pipe) return -1;
    char tmp_buff[128];
    std::string tmp_res;
    // read from pipe
    while(!feof(pipe)){
    	if(fgets(tmp_buff, 128, pipe) != NULL) tmp_res += tmp_buff;
    }
    pclose(pipe);

    // check buffer size
    if(result_size >= (tmp_res.size() + 1)){
        memcpy(result, tmp_res.c_str(), tmp_res.size());
        result[tmp_res.size()] = 0;

    }

    return 0;
}


void pmink_utils::run_external_print(const char* script, bool ncurses){
    FILE* pipe = popen(script, "r");
    if (!pipe) return;
    char tmp_buff[128];
    // read from pipe
    while(!feof(pipe)){
    	if(fgets(tmp_buff, 128, pipe) != NULL) if(ncurses) printw("%s", tmp_buff); else std::cout << tmp_buff;
    }
    if(ncurses) printw("\n"); else std::cout << std::endl;
    pclose(pipe);

}


timespec pmink_utils::time_diff_msec(timespec start, timespec end) {
	timespec temp;
	if((end.tv_nsec - start.tv_nsec) < 0){
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	}else{
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return temp;
}
