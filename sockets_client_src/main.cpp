#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

struct StavHry {
    //HraciaDoska hraciaDoska;
    int hodKockou;
    bool jeKoniec;
};

int main() {
    //Pripojenie na server
    WSADATA wsaData;
    std::string hostName = "frios2.fri.uniza.sk";
    short port = 12500;

    struct addrinfo *result = NULL;
    struct addrinfo hints;
    int iResult;

    //inicializacia WinSock kniznice
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        throw std::runtime_error("WSAStartup failed with error: " + std::to_string(iResult) + "\n");
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // získanie informácií o adrese pre daný sieťový host a port.
    iResult = getaddrinfo(hostName.c_str(), std::to_string(port).c_str(), &hints, &result);
    if (iResult != 0) {
        WSACleanup();
        throw std::runtime_error("getaddrinfo failed with error: " + std::to_string(iResult) + "\n");
    }

    // vytvorenie soketu pre pripojenie na server
    SOCKET connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connectSocket == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("socket failed with error: " + std::to_string(WSAGetLastError()) + "\n");
    }

    // pripojenie na server
    iResult = connect(connectSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(connectSocket);
        connectSocket = INVALID_SOCKET;
    }

    // uvolnenie pamäťi alokovanej pre zoznam adries
    freeaddrinfo(result);

    if (connectSocket == INVALID_SOCKET) {
        printf("Nepodarilo sa pripojit na server!\n");
        WSACleanup();
        throw std::runtime_error("Unable to connect to server.\n");
    }

    std::cout << "Pripojenie na server bolo uspesne." << std::endl;
    StavHry stavHry;

    // Hráč môže hodit kockou kliknutím na Enter
    // Jednoduchý while loop na opakované hody
    while (!stavHry.jeKoniec) {
        std::cout << "Stlacte Enter pre hod kockou..\n";
        std::cin.get();

        char action = 'h';
        send(connectSocket, &action, sizeof(action), 0);     //posielanie na server - klient vykonal akciu

        int diceResult;
        //recv(connectSocket, reinterpret_cast<char*>(&diceResult), sizeof(diceResult), 0);    //prijimanie zo serveru
        recv(connectSocket, reinterpret_cast<char*>(&stavHry), sizeof(stavHry), 0);

        // Zobrazenie informácií hráčovi
        std::cout << "Hodil si: " << stavHry.hodKockou << std::endl;

        // Zobrazenie hracieho poľa
        // stavHry.hraciaDoska.zobrazHraciePole();

        // Ďalšia logika hry by sa vykonávala tu

        Sleep(1000);  // Simulácia ďalšieho kola
    }

    closesocket(connectSocket);
    WSACleanup();
    return 0;
}
