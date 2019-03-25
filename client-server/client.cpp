#include "client.h"
using namespace std;
 
int main(int argc, char *argv[]){
    int server;
    struct  sockaddr_in addr;
    char *server_addr;
    unsigned short port;
    char buffer[1024];
    string input = "";
    string comms = "";
    if(argc < 4){
         cout << "Not enough arguments";
         return 1;
    }
    port = (unsigned short) strtoul(argv[2], NULL, 0);
    server_addr = argv[4];
   
    server = socket(AF_INET, SOCK_STREAM, 0);
 
    addr.sin_addr.s_addr = inet_addr(server_addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    if(connect(server, (struct sockaddr *)&addr, sizeof(addr)) < 0){
            cout << "Cannot connect to server" << endl;
            close(server);
            cout << "Socket closed." << endl << endl;
            return 1;
    }

    sendBuffer(server,REQUEST,strlen(REQUEST));

    while(1){
        if(recv(server, buffer, sizeof(buffer), 0) <0){
            cout << "Cannot connect to server" << endl;
            close(server);
            cout << "Socket closed." << endl << endl;
            break;
        }
    
        cout << "Server says: " << buffer << endl;
        
        if(strcmp(buffer,HOST_IP) == 0){
            cout  << "Request Accepted" << endl;
            cout << "Please input host name: ";
            getline(cin, input);
            cout << input << endl;
            sendBuffer(server,input.c_str(),sizeof(input));
            
        }
        else if(strcmp(buffer,HOST_PEERS) == 0){
            std::ifstream file("peers.json");
            std::ostringstream tmp;
            tmp<<file.rdbuf();
            std::string s = tmp.str();
            std::vector<char> bytes(s.begin(), s.end());
            bytes.push_back('\0');
            cout << bytes.data() << endl;
            sendBuffer(server,bytes.data(),bytes.size());
            
        }
        else if(strcmp(buffer,END) == 0){
            close(server);
            cout << "Socket closed." << endl << endl;
            break;
            
        }
        memset(buffer, 0, sizeof(buffer));
    }
}

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
