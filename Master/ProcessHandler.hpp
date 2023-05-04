#ifndef PROCESSHANDLER_HPP
#define PROCESSHANDLER_HPP

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <pthread.h>
#include <vector>

class ProcessHandler {
public:
    ProcessHandler();
    void StartThreads(const std::vector<std::string>& processList);
    void signal_handler(int sig);  // now public

private:
    // Private member variables
    std::vector<pthread_t> threads_;  // stores the thread IDs
    static volatile bool should_exit_;  // flag indicating if the program should exit

    // Member functions
    static void* thread_function(void* arg);

    // Helper function to register the signal handler
    void register_signal_handler();
};

#endif

