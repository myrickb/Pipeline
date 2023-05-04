#include "ProcessHandler.hpp"

volatile bool ProcessHandler::should_exit_ = false;  // initialize the static member variable

// Global function and variable to handle the signal
ProcessHandler* g_processHandlerInstance = nullptr;
void global_signal_handler(int sig) {
    // if (g_processHandlerInstance != nullptr) {
    //     g_processHandlerInstance->signal_handler(sig);
    // }
}

void ProcessHandler::StartThreads(const std::vector<std::string>& processList) {
    // Register signal handler for SIGINT (Ctrl+C)
    register_signal_handler();
    // Spawn a thread for each executable
    for (auto& exe : processList) {
        pthread_t t;
        std::string* exe_copy = new std::string(exe);  // make a copy of the string
        if (pthread_create(&t, NULL, thread_function, (void*)exe_copy) != 0) {
            std::cerr << "Error creating thread for " << exe << std::endl;
            delete exe_copy;
            return;
        }
        threads_.push_back(t);
    }
    // Wait for all threads to finish or program to exit
    for (auto& t : threads_) {
        if (!should_exit_) {
            pthread_join(t, NULL);
        } else {
            pthread_cancel(t);
        }
    }
}

void ProcessHandler::signal_handler(int sig) {
    std::cout << "Caught signal " << sig << ". Terminating threads..." << std::endl;
    should_exit_ = true;
    // Cancel all running threads
    for (auto& t : threads_) {
        pthread_cancel(t);
    }
}

void ProcessHandler::register_signal_handler() {
    g_processHandlerInstance = this;
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = global_signal_handler;
    //sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        std::cerr << "Error registering signal handler" << std::endl;
        _exit(1);
    }
}

void* ProcessHandler::thread_function(void* arg) {
    std::string* executable = static_cast<std::string*>(arg);

    if(executable == nullptr){
        std::cout << "Executable string is null" << std::endl;
        return NULL;
    }
    std::cout << "Starting thread for executable " << *executable << std::endl;
    // Spawn the process for the executable here
    //int status = system(executable->c_str());
    //std::cout << "past system call: " << status << std::endl;
    // if (status != 0) {
    //     std::cerr << "Error running " << *executable << std::endl;
    // }
    std::cout << "Thread for executable " << *executable << " finished" << std::endl;
    //delete executable;  // free the memory allocated for the string copy
    std::cout << "after delete" << std::endl;
    return NULL;
}