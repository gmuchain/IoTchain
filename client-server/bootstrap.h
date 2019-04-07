#include <iostream>
//#include <winsock2.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>

#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros  
#include <inttypes.h>
#include <cstdint>
//#include <process.h>
#include <fstream>
#include <string>

#include "json.hpp"
using json = nlohmann::json;
using namespace std;
const char* const REQUEST = "Initial Request";
const char* const HOST_IP = "Host IP";
const char* const HOST_PEERS = "Host Peers";
const char* const END = "End Connection";

void *connection_handler(void *socket_desc);
json parseClientPeers(char *buffer,std::string host);
json findHostsPeers(std::string host);
int sendBuffer (int client_socket, const char *buf, int len);