#include <iostream>
//#include <winsock2.h>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>

#include <inttypes.h>
#include <cstdint>
#include <arpa/inet.h>
//#include <process.h>
#include "json.hpp"

#include <netdb.h> 
//#include <nlohmann/json.hpp>

const char* REQUEST = "Initial Request";
const char* HOST_IP = "Host IP";
const char* HOST_PEERS = "Host Peers";
const char* HELLO_PEER = "HELLO";
const char* END = "End Connection";
const char* CLIENT_REQUEST = "New Client";

const char* YES = "y";
const char* NO = "n";


int sendBuffer (int ClientSocket, const char *buf, int len);
void *peer_connection_handler(void *socket_desc);
void synchronizePeers(char *buffer);
void testReadJson();
