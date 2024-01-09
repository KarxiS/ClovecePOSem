#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

struct LocalInfo{
    char playerID='0';
    std::string meno;
};

struct StavHry {
    std::string hraciaDoska;
    int hodKockou;
    bool jeKoniec=false;
    bool naRade = false;
    int hracNaTahu=-1;
    char playerID='0';
    std::string vitaz;
};

int main() {
    //Pripojenie na server
    WSADATA wsaData;
    LocalInfo localInfo;
    std::string hostName = "frios2.fri.uniza.sk";
    short port = 12502;

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
    recv(connectSocket, reinterpret_cast<char*>(&localInfo.playerID), sizeof(localInfo.playerID), 0);
    std::cout << "Pripojenie na server bolo uspesne.\n"
                 "Ste hrac cislo" <<localInfo.playerID<< std::endl;
    StavHry stavHry;

    // Hráč môže hodit kockou kliknutím na Enter
    // Jednoduchý while loop na opakované hody
    while (true) {
        char action = 'h';
        send(connectSocket, &action, sizeof(action), 0);
        // prijemDlzky
        size_t lengthMap;
        recv(connectSocket, reinterpret_cast<char*>(&lengthMap), sizeof(lengthMap), 0);

        // prijemMapy
        char* bufferMap = new char[lengthMap];
        recv(connectSocket, bufferMap, lengthMap, 0);
        stavHry.hraciaDoska = std::string(bufferMap, lengthMap);
        delete[] bufferMap;

        // Zobrazenie hracieho poľa
        std::cout << stavHry.hraciaDoska << std::endl; // Display the game board

        std::cout << "Stlacte Enter pre hod kockou..\n";
        std::cin.get();
        send(connectSocket, &action, sizeof(action), 0);     //posielanie na server - klient vykonal akciu
        recv(connectSocket, reinterpret_cast<char*>(&stavHry.naRade), sizeof(stavHry.naRade), 0);

        if (stavHry.naRade == false) {
            recv(connectSocket, reinterpret_cast<char*>(&stavHry.hracNaTahu), sizeof(stavHry.hracNaTahu), 0);
            std::cout << "pockajte, nie ste na rade! kocka sa hodi hned ako budete na rade!\n";
            std::cout <<"na rade je hrac "<< stavHry.hracNaTahu<<std::endl;
            std::cout <<"vy ste hrac "<< localInfo.playerID<<std::endl;
            continue;
        }
        size_t length;
        recv(connectSocket, reinterpret_cast<char*>(&length), sizeof(length), 0);

        // dlzkaString
        char* buffer = new char[length];
        recv(connectSocket, buffer, length, 0);
        stavHry.hraciaDoska = std::string(buffer, length);
        delete[] buffer;

        // hodKockou
        recv(connectSocket, reinterpret_cast<char*>(&stavHry.hodKockou), sizeof(stavHry.hodKockou), 0);
        // jeKoniec
        recv(connectSocket, reinterpret_cast<char*>(&stavHry.jeKoniec), sizeof(stavHry.jeKoniec), 0);
        // meno vitaza
        if(stavHry.jeKoniec){
            recv(connectSocket, reinterpret_cast<char*>(&stavHry.vitaz), sizeof(stavHry.vitaz), 0);
        }
        // Zobrazenie informácií hráčovi
        std::cout << "Hodil si: " << stavHry.hodKockou << std::endl;
        // Zobrazenie hracieho poľa
        std::cout << stavHry.hraciaDoska << std::endl; // Display the game board

        if(stavHry.jeKoniec){
            std::cout << "Hra skoncila." << std::endl;
            std::cout << "Vitazom hry sa stal " << stavHry.vitaz << std::endl;
            break;
        }

        // dlzkaStringu
        size_t lengthRozhodnutie;
        recv(connectSocket, reinterpret_cast<char*>(&lengthRozhodnutie), sizeof(lengthRozhodnutie), 0);
        // dataString
        char* bufferRozhodnutie = new char[lengthRozhodnutie];
        recv(connectSocket, bufferRozhodnutie, lengthRozhodnutie, 0);

        if (lengthRozhodnutie <= 0) {
            std::cerr << "Stratene spojenie so serverom." << std::endl;
            break;
        }
        std::cout<<std::string(bufferRozhodnutie, lengthRozhodnutie) <<std::endl;
        delete[] bufferRozhodnutie;

        // pytam sa ktoru chce posunut figurku
        std::string decision;
        std::cout << "Tvoj vstup: ";
        std::getline(std::cin, decision);
        std::cout << std::endl;
        send(connectSocket, decision.c_str(), decision.size(), 0);

        Sleep(1000);  // Simulácia ďalšieho kola
    }
    closesocket(connectSocket);
    WSACleanup();
    return 0;
}
