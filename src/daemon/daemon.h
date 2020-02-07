#ifndef DAEMON_H_
#define DAEMON_H_

#include <iostream>
#include <syslog.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace pmink {

	class DaemonDescriptor {
	public:
		// termination flag
		static bool DAEMON_TERMINATED;
		// constructor, destructor
		DaemonDescriptor();
		DaemonDescriptor(const char* _name, const char* _desc);
		virtual ~DaemonDescriptor();
		// daemon_name
		const char* get_daemon_name();
		void set_daemon_name(const char* _name);
		// daemon description
		const char* get_daemon_description();
		void set_daemon_description(const char* _desc);
		// command line arguments
		virtual void process_arguements(int argc, char** argv);
		virtual void print_help();
	private:
		char daemon_name[100];
		char daemon_description[500];

	};


	// daemon management
	void child_handler(int signum);
	void daemon_init(DaemonDescriptor* daemon_descriptor);
	void daemon_start(DaemonDescriptor* daemon_descriptor);
	void daemon_terminate(DaemonDescriptor* daemon_descriptor);
	void daemon_loop(DaemonDescriptor* daemon_descriptor);



}


#endif /* DAEMON_H_ */
