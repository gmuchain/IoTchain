#include <ctime>
#include <chrono>
#include <sstream>
#include <iostream>

#include "log.h"

IotChain::Log::Log(std::string filename, bool printToConsole) {
    if(printToConsole){
        printf(LOG_LEVEL_INFO,"test");
    }
}

IotChain::Log::~Log() {
}

bool IotChain::Log::printf(int logLevel, std::string logMessage){
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(today);
    std::string t(ctime(&tt));
    std::ostringstream stagingstream;
    stagingstream << t.substr(0, t.length() - 1) << " ";

    switch(logLevel) {
        case LOG_LEVEL_ERR:
            stagingstream << "ERROR ";
            break;

        case LOG_LEVEL_WARN:
            stagingstream << "ERROR ";
            break;

        case LOG_LEVEL_INFO:
            stagingstream << "ERROR ";
            break;
    }
    
    stagingstream << logMessage << "\n";

    std::cout << stagingstream.str() << std::flush;
    return true;
}