#include <iostream>

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

SOCKET Connection;

void ClientHandler() {
    char msg[256];
    while (true) {
        recv(Connection, msg, sizeof(msg), NULL);
        cout << msg << endl;
    }
}

int main(int argc, char* argv[])
{
    cout << "Hello Client World!\n" << endl;



    // Initialize Winsock
    cout << "Initialize Winsock...\n" << endl;
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    // Socket info
    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(11111);
    addr.sin_family = AF_INET;



    Connection = socket(AF_INET, SOCK_STREAM, NULL);
    
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        cout << "Error to connect\n" << endl;
        return 1;
    }
    cout << "Connected!\n" << endl;
    
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

    char msg1[256];
    while (true) {
        cin.getline(msg1, sizeof(msg1));
        send(Connection, msg1, sizeof(msg1), NULL);
        Sleep(10);
    }

    //cout << "Client was successfully connected! Press to close a window...\n" << endl;
    cin.ignore();
    return 0;
}