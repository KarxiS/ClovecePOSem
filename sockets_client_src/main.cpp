#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main() {
    //Pripojenie na server
    WSADATA wsaData;
    std::string hostName = "frios2.fri.uniza.sk";
    short port = 12499;

    struct addrinfo *result = NULL;
    struct addrinfo hints;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        throw std::runtime_error("WSAStartup failed with error: " + std::to_string(iResult) + "\n");
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(hostName.c_str(), std::to_string(port).c_str(), &hints, &result);
    if (iResult != 0) {
        WSACleanup();
        throw std::runtime_error("getaddrinfo failed with error: " + std::to_string(iResult) + "\n");
    }

    // Create a SOCKET for connecting to server
    SOCKET connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connectSocket == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("socket failed with error: " + std::to_string(WSAGetLastError()) + "\n");
    }

    // Connect to server
    iResult = connect(connectSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(connectSocket);
        connectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (connectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        throw std::runtime_error("Unable to connect to server.\n");
    }
    std::cout << "Pripojenie na server bolo uspesne." << std::endl;



    // Hráč môže hodit kockou kliknutím na Enter
    // Jednoduchý while loop na opakované hody
    while (true) {
        std::cout << "Stlacte Enter pre hod kockou..\n";
        std::cin.get();

        char action = 'h';
        send(connectSocket, &action, sizeof(action), 0);     //posielanie na server - klient vykonal akciu

        int diceResult;
        recv(connectSocket, reinterpret_cast<char*>(&diceResult), sizeof(diceResult), 0);    //prijimanie zo serveru

        std::cout << "Hodil si: " << diceResult << std::endl;

        // Ďalšia logika hry by sa vykonávala tu

        Sleep(1000);  // Čakáme na simuláciu ďalšieho kola
    }

    closesocket(connectSocket);
    WSACleanup();
    return 0;
}
