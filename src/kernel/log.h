#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <string>
#include <fstream>
#include <mutex>

#define LOG_LEVEL_ERR 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_INFO 3

namespace IotChain {
class Log {
public:

    Log(const std::string filename = "CryptoKernel.log", const bool printToConsole = false);
    ~Log();
};

}

#endif // LOG_H_INCLUDED

