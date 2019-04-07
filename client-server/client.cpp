#include "client.h"

using namespace std;
using json = nlohmann::json;

/*
    Allows structs to map to/from json objects send/received.
*/
namespace ns {
    struct peer {
        std::string address;
        std::string port;
    };
    void to_json(json& j, const peer& p) {
        j = json{{"host", p.address}, {"port", p.port}};
    }
    void from_json(const json& j, peer& p) {
        j.at("host").get_to(p.address);
        j.at("port").get_to(p.port);
    }
} 
/*

*/
int main(int argc, char *argv[]){
    int server,peerServer,clientServer,newPeer;
    struct  sockaddr_in bootstrapAddr,clientServerAddr,peerHostAddr,newPeerAddr;
    socklen_t newPeerAddrSize;
    char *server_addr;
    unsigned short port,clientPort,peerPort;
    char buffer[1024];
    string input = "";
    pthread_t thread_id;
    bool gotServerConfig = false;
    //Get IPV4 hostname
    /*
    char hostbuffer[256]; 
    char *IPbuffer; 
    struct hostent *host_entry; 
    int hostname; 
    */
    if(argc < 4){
         cout << "Not enough arguments";
         return 1;
    }
    //Get IPV4 hostname
    /*
    hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
    host_entry = gethostbyname(hostbuffer); 
    IPbuffer = inet_ntoa(*((struct in_addr*) 
    host_entry->h_addr_list[0])); 
    cout << "hostname: " << IPbuffer     << endl;
    */
    port = (unsigned short) strtoul(argv[2], NULL, 0);
    clientPort = (unsigned short) strtoul(argv[5], NULL, 0);
    if(clientPort == 5556){
        peerPort = 5557;
    }
    else{
        peerPort = 5556;
    }
    server_addr = argv[4];
   
    server = socket(AF_INET, SOCK_STREAM, 0);
    peerServer = socket(AF_INET, SOCK_STREAM, 0);
    clientServer = socket(AF_INET, SOCK_STREAM, 0);

    //bootstrap server address
    bootstrapAddr.sin_addr.s_addr = inet_addr(server_addr);
    bootstrapAddr.sin_family = AF_INET;
    bootstrapAddr.sin_port = htons(port);

    //client address
    clientServerAddr.sin_addr.s_addr = INADDR_ANY;
    clientServerAddr.sin_family = AF_INET;
    clientServerAddr.sin_port = htons(clientPort);

    if(connect(server, (struct sockaddr *)&bootstrapAddr, sizeof(bootstrapAddr)) < 0){
            cout << "Cannot connect to server" << endl;
            close(server);
            cout << "Socket closed." << endl << endl;
            return 1;
    }
    sendBuffer(server,REQUEST,strlen(REQUEST));
    if(!gotServerConfig){
        while(1){
                if(recv(server, buffer, sizeof(buffer), 0) <0){
                    cout << "Cannot connect to server" << endl;
                    close(server);
                    cout << "Socket closed." << endl << endl;
                    break;
                }
            
                if(strcmp(buffer,HOST_IP) == 0){
                    cout << "Connection Accepted" << endl;
                    cout << "Please input host name: ";
                    getline(cin, input);
                    sendBuffer(server,input.c_str(),sizeof(input) + sizeof(input));
                    
                }
                else if(strcmp(buffer,HOST_PEERS) == 0){
                    cout << "Server requesting known peers:" << endl;
                    std::ifstream file("peers.json");
                    std::ostringstream tmp;
                    tmp<<file.rdbuf();
                    std::string s = tmp.str();
                    std::vector<char> bytes(s.begin(), s.end());
                    bytes.push_back('\0');
                    cout << bytes.data() << endl;
                    sendBuffer(server,bytes.data(),bytes.size());
                    
                }
                /*
                else if(strcmp(buffer,END) == 0){
                    close(server);
                    cout << "Bootstrap communication finished." << endl << endl;
                    gotServerConfig = true;
                    break;
                    
                }*/
                else{
                    close(server);
                    cout << "Received peers from server:" << endl;
                    synchronizePeers(buffer);
                    cout << "Bootstrap communication finished." << endl << endl;
                    gotServerConfig = true;
                    break;
                }

                memset(buffer, 0, sizeof(buffer));
            }
    }
    if(gotServerConfig){
        //peer host address
        peerHostAddr.sin_addr.s_addr = inet_addr(server_addr);
        peerHostAddr.sin_family = AF_INET;
        peerHostAddr.sin_port = htons(peerPort);

        bind(clientServer, (struct sockaddr *)&clientServerAddr, sizeof(clientServerAddr));
        listen(clientServer, 0);
        cout << "Listening for other peers" << endl;

        newPeerAddrSize = sizeof(newPeerAddr);

        while(1){
            if(connect(peerServer, (struct sockaddr *)&peerHostAddr, sizeof(peerHostAddr)) < 0){
                    cout << "Awating for peer to come online..." << endl;
                    //close(server);
            }
            else{
                cout << "Client Server: Sending hello" << endl;
                sendBuffer(peerServer,HELLO_PEER,strlen(HELLO_PEER));
            }

            if((newPeer = accept(clientServer, (struct sockaddr *)&newPeerAddr, (socklen_t*)&newPeerAddrSize)) > 0){
                if( pthread_create( &thread_id , NULL ,  peer_connection_handler , (void*) &newPeer) < 0){
                    perror("could not create thread");
                    return 1;
                }
            }
        }
    }
    
}
/*
    Clean up required. Initially used to parse JSON from .json files. No longer required.
*/
void testReadJson(){
    std::ifstream i("peers.json");
    json j;
    i >> j;
    for (json::iterator it = j.begin(); it != j.end(); ++it) {

        std::cout << *it << endl;
    }
    for (auto& element : j) {
        std::cout << element << '\n';
        for(auto& element2: element){
            std::cout << element2["host"] << ":" << element2["port"] << '\n';
        }
    }
    //std::cout << j;
}

/*
    Continues to send data until no data is left.
*/
int sendBuffer (int client_socket, const char *buf, int len){
    int num_left = len;
    int num_sent;
    int err = 0;
    const char *cp = buf;

    while (num_left > 0){

        num_sent = send(client_socket, cp, num_left,0);
        if (num_sent < 0){
             cout << err << endl;
            break;
        }

        num_left -= num_sent;
        cp += num_sent;
    }
    return num_sent;
}

/*
    Updates client's known peers based on servers response. Currenly overwrites client's known peers.
*/
void synchronizePeers(char *buffer){
    json j = json::parse((char*)buffer, ((char*)buffer) + strlen((char*)buffer));
    ns::peer p = {"127.0.0.1", "5557"};

    for (auto& element : j) {
        for(auto& element2: element){
            std::cout << element2["host"] << ":" << element2["port"] << '\n';
            auto p2 = element2.get<ns::peer>();
            cout << "p2: " << p2.address << ":" << p2.port << endl;
        }
    }
    
    ofstream file("peers.json");
    if (file.is_open()){
        file << j.dump(1);
        file.close();
    }
}

/*
    Handle each client on a new session.
    1. Receive Hello message from client
*/
void *peer_connection_handler(void *socket_desc){
    string host = "";
    string peers = "";
    int peerSocket =  *((int *)socket_desc);
    char buffer[1024];

    while(1){
        read(peerSocket, buffer, sizeof(buffer));
        cout << "Peer says: " << buffer << endl;

        if(strcmp(buffer,HELLO_PEER) == 0){
            cout  << "Client Server: Received hello" << endl;
            sendBuffer(peerSocket, HOST_IP, strlen(HOST_IP));
            
        }
        else{
            cout << "Closing Socket" << endl;
            pthread_exit(NULL); 
            close(peerSocket);
        }
        memset(buffer, 0, strlen(buffer));
    }
}
