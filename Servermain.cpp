#include <iostream>

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

SOCKET Connections[5];
int Connection_id = 0;

void ClientHandler(int index) {
    char msg[256];
    while (true) {
        recv(Connections[index], msg, sizeof(msg), NULL);
        for (int i = 0; i < Connection_id; i++) {
            if (i == index) {
                continue;
            }

            send(Connections[i], msg, sizeof(msg), NULL);
        }
    }
}


int main(int argc, char* argv[])
{
    cout << "Hello Server World!\n" << endl;
   
    

    // Initialize Winsock
    cout << "Initialize Winsock...\n" << endl;
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(11111);
    addr.sin_family = AF_INET;


    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, 5);


    SOCKET newConnection;

    for (int i = 0; i < 5; i++) {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

        if (newConnection == 0) {
            cout << "newConnection failed!";
        }
        else {
            cout << "newConnection bindet!" << endl;
            char msg[256] = "Hello. I am Server";
            send(newConnection, msg, sizeof(msg), NULL);

            Connections[i] = newConnection;
            Connection_id++;

            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
        }

    }

    cout << "Server closed successfully! Press to close a window...\n";
    cin.ignore();
    return 0;
}