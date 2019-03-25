#include <iostream>
//#include <winsock2.h>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <process.h>
#include "json.hpp"

const char* REQUEST = "Initial Request";
const char* HOST_IP = "Host IP";
const char* HOST_PEERS = "Host Peers";
const char* END = "End Connection";

const char* CLIENT_REQUEST = "New Client";

const char* YES = "y";

const char* NO = "n";
const int SERVER_COMM = 0;
const int CLIENT_COMM = 1;


int sendBuffer (int ClientSocket, const char *buf, int len);

