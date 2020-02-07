#include <daemon.h>
// static
bool pmink::DaemonDescriptor::DAEMON_TERMINATED;

// DaemonDescriptor
pmink::DaemonDescriptor::DaemonDescriptor(){
	DAEMON_TERMINATED = false;
}

pmink::DaemonDescriptor::DaemonDescriptor(const char* _name, const char* _desc){
	DAEMON_TERMINATED = false;
	set_daemon_name(_name);
	set_daemon_description(_desc);
}


pmink::DaemonDescriptor::~DaemonDescriptor(){

}

void pmink::DaemonDescriptor::print_help(){
	std::cout << daemon_name << " - " << daemon_description << std::endl;
	std::cout << "Copyright (c) 2012 Release14.org" << std::endl;
	std::cout << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << " -c\tconfig daemon address (ip:port, example: 192.168.0.1:6666)" << std::endl;
	std::cout << " -?\thelp" << std::endl;

}

void pmink::DaemonDescriptor::process_arguements(int argc, char** argv){
	int opt;

	if(argc == 1){
		print_help();
		exit(EXIT_FAILURE);
		return;
	}else{
		while ((opt = getopt(argc, argv, "?c:")) != -1) {
			switch(opt){
				// help
				case '?':
					print_help();
					exit(EXIT_FAILURE);
					return;
				// config daemon address
				case 'c':
					std::cout << optarg << std::endl;
					break;
			}
		}
	}

}


void pmink::DaemonDescriptor::set_daemon_name(const char* _name){
	strcpy(daemon_name, "pmink.");
	if(_name != NULL) strcat(daemon_name, _name);

}
void pmink::DaemonDescriptor::set_daemon_description(const char* _desc){
	if(_desc != NULL) strcpy(daemon_description, _desc);

}

const char* pmink::DaemonDescriptor::get_daemon_name(){
	return daemon_name;
}

const char* pmink::DaemonDescriptor::get_daemon_description(){
	return daemon_description;
}

// daemon management
void pmink::child_handler(int signum){
    switch(signum) {
		case SIGTERM:
			// set termination flag
			DaemonDescriptor::DAEMON_TERMINATED = true;
			break;
    }
}

void pmink::daemon_start(DaemonDescriptor* daemon_descriptor){
	if(daemon_descriptor != NULL){
	    openlog(daemon_descriptor->get_daemon_name(), LOG_PID | LOG_CONS, LOG_USER);
	    syslog(LOG_INFO, "starting...");

	}

}

void pmink::daemon_terminate(DaemonDescriptor* daemon_descriptor){
	if(daemon_descriptor != NULL){
	    syslog(LOG_INFO, "terminating...");
		closelog();
	}
}

void pmink::daemon_loop(DaemonDescriptor* daemon_descriptor){
	while(!pmink::DaemonDescriptor::DAEMON_TERMINATED){
		sleep(30);
	    //syslog(LOG_DEBUG, "heart-beat...");

	}
	// release memory
	daemon_terminate(daemon_descriptor);


}

void pmink::daemon_init(DaemonDescriptor* daemon_descriptor){
    pid_t pid, sid;

    /* Fork off the parent process */
    pid = fork();
    if(pid < 0) exit(EXIT_FAILURE);

    /* If we got a good PID, then we can exit the parent process. */
    if(pid > 0) exit(EXIT_SUCCESS);

    /* child process executing from here, fork return 0 in child process */

    /* Change the file mode mask */
    umask(0);

    /* Create a new SID for the child process */
    sid = setsid();
    if(sid < 0) exit(EXIT_FAILURE);

    /* Change the current working directory.  This prevents the current
       directory from being locked; hence not being able to remove it. */
    if((chdir("/")) < 0) exit(EXIT_FAILURE);

    /* Close standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // custom signal handlers
    signal(SIGTERM, child_handler);

	// start daemon
	daemon_start(daemon_descriptor);


}




