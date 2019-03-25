#include "bootstrap.h"

using namespace std;
//using json = nlohmann::json;
int main(){
 
    int server, client;
    pthread_t new_thread;
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
            

            if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client) < 0)
        {
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
    string host = "";
    string peers = "";
    int client_socket =  *((int *)socket_desc);
    char buffer[1024];

    cout  << "Client connected!" << endl;
    while(1){
        read(client_socket, buffer, sizeof(buffer));
        cout << "Client says: " << buffer << endl;

        if(strcmp(buffer,REQUEST) == 0){
            cout  << "Server: Received Initial Request" << endl;
            cout  << "Server: Ready for Host IP" << endl;
            send(client_socket, HOST_IP, strlen(HOST_IP), 0);
            
        }
        else{
            if(host.length() == 0){
                cout << "set host" << endl;
                host = buffer;
                send(client_socket, HOST_PEERS, strlen(HOST_PEERS), 0);

            }
            else{
                cout << "create known_peers" << endl;
                ofstream file("known_peers.json");
                if (file.is_open()){
                    file << buffer;
                    file.close();
                }
                send(client_socket, END, strlen(END), 0);
                
                pthread_exit(NULL); 
                close(client_socket);
                cout << "Client disconnected." << endl;
                break;
            }
        }
        memset(buffer, 0, strlen(buffer));
    }
}
