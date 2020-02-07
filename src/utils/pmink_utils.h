
#ifndef UTILS_H_
#define UTILS_H_

#include <time.h>

namespace pmink_utils {

	int run_external(const char* script, char* result, int result_size);
	void run_external_print(const char* script, bool ncurses);
	timespec time_diff_msec(timespec start, timespec end);

}

#endif /* UTILS_H_ */
