#include "bootstrap.h"
 
int main(){
 
    int server, client;
    struct  sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrSize;
    pthread_t thread_id;

    server = socket(AF_INET, SOCK_STREAM, 0);
    
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
 
    bind(server, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);
 
    cout << "Listening for incoming connections..." << endl;
 
    clientAddrSize = sizeof(clientAddr);

    while(1){
        
        if((client = accept(server, (struct sockaddr *)&clientAddr, (socklen_t*)&clientAddrSize)) > 0){
            if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client) < 0){
                perror("could not create thread");
                return 1;
            }
        }
    }
}

 /*
    Handle each client on a new session.
    1. Receive initial request from client.
    2. Request "hostname" from client.
    3. Read peers from client and store in known_peers.json
 */
void *connection_handler(void *socket_desc){
    std::string host = "";
    std::string peers = "";
    int client_socket =  *((int *)socket_desc);
    char buffer[1024];
    json peerJson;

    cout  << "Client connected!" << endl;
    while(1){
        read(client_socket, buffer, sizeof(buffer));
        cout << "Client says: " << buffer << endl;

        if(strcmp(buffer,REQUEST) == 0){
            cout  << "Server: Received Initial Request" << endl;
            cout  << "Server: Request Host IP" << endl;
            send(client_socket, HOST_IP, strlen(HOST_IP), 0);
            
        }
        else{
            if(host.length() == 0){
                cout << "Server: Received Host IP " << buffer << endl;
                host = buffer;                
                cout << "Server: Request Peers " << endl;
                send(client_socket, HOST_PEERS, strlen(HOST_PEERS), 0);

            }
            else{
                
                peerJson = parseClientPeers(buffer,host);
                peers = peerJson.dump();
                cout << "Server: Peers sent to client " << endl;
                cout << peerJson.dump(1) << endl;
                std::vector<char> bytes(peers.begin(), peers.end());
                bytes.push_back('\0');
                /*
                ofstream file("known_peers.json");
                if (file.is_open()){
                    file << buffer;
                    parseClientPeers(buffer,host);
                    file.close();
                }
                */
               

                sendBuffer(client_socket,bytes.data(),bytes.size());               
                //send(client_socket, END, strlen(END), 0);
                
                pthread_exit(NULL); 
                close(client_socket);
                cout << "Client disconnected." << endl;
                break;
            }
        }
        memset(buffer, 0, strlen(buffer));
    }
}   


/*
    Parse received peers from buffer. Needs to update known peers
    for given host.
*/
json parseClientPeers(char *buffer,std::string host){
    json peers = findHostsPeers(host);

    /*
    json j = json::parse((char*)buffer, ((char*)buffer) + strlen((char*)buffer));
    for (auto& element : peers) {
        for(auto& element2: element){
            std::cout << element2["host"] << ":" << element2["port"] << '\n';
        }
    }*/
    return peers;
}

/*
    If the connecting host is found, update its known peers.
*/
json findHostsPeers(std::string host){
    std::ifstream i("known_peers.json");
    json j, peers,peer,client;
    i >> j;
    peers = json::array();
    // even easier with structured bindings (C++17)
    for (auto& el : j.items() ){
        if(strcmp(el.key().c_str(),host.c_str()) == 0){
            std::cout  << "Found host!" << endl;
            std::cout << "Peers on server: " << endl;
            for(auto& el2: el.value()){
                std::cout << el2["host"] << ":" << el2["port"] << '\n';
                peer["host"] = el2["host"];
                peer["port"] = el2["port"];
                peers.push_back(peer);
            }
        }
    }
    client["peers"] = peers;
    return client;   
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