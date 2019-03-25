#include <iostream>
//#include <winsock2.h>  //windows socket header
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros  
#include <inttypes.h>
#include <cstdint>
#include <process.h>
#include <fstream>
#include "json.hpp"

const char* const REQUEST = "Initial Request";
const char* const HOST_IP = "Host IP";
const char* const HOST_PEERS = "Host Peers";
const char* const END = "End Connection";

void *connection_handler(void *socket_desc);