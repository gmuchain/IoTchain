#include "log.h"

IotChain::Log::Log(std::string filename, bool printToConsole) {
    if(printToConsole){
        printf("Test log");
    }
}

IotChain::Log::~Log() {
}