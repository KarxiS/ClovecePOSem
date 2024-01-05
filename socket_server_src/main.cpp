#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../CloveceSEM/Hra.h"

std::mutex diceMutex;
int diceResult;

struct StavHry {
    HraciaDoska hraciaDoska;
    Hra hra;
    //Kocka kocka;
    int hodKockou;
    bool jeKoniec;
};

void handleClient(int clientSocket, int playerId) {
    while (true) {
        // Prijatie akcie od klienta (hod kockou)
        char buffer[256];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << "Chyba pri čítaní zo soketu pre hráča " << playerId << std::endl;
            break;
        }

        // Simulácia hodu kockou
        std::lock_guard<std::mutex> lock(diceMutex);
        diceResult = rand() % 6 + 1;
        //diceResult = kocka.hodkocou();

        // Aktualizácia stavu hry
        StavHry stavHry;
        stavHry.hodKockou = diceResult;

        // Odošleme klientovi výsledek hodu
        //send(clientSocket, reinterpret_cast<char*>(&diceResult), sizeof(diceResult), 0);
        send(clientSocket, reinterpret_cast<char*>(&stavHry), sizeof(stavHry), 0);
        std::cout << "Hráč " << playerId << " hodil kockou a získal: " << diceResult << std::endl;
    }

    close(clientSocket);
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    short port = 12499;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;             // Internetove sokety
    serverAddress.sin_port = htons(port);           // Nastavenie portu
    serverAddress.sin_addr.s_addr = INADDR_ANY;     // Prijimam sokety z celeho internetu

    // aby sa predišlo tomu, že port bude stále obsadený, pri znovupoužiteľnosťi adresy
    int enable = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&enable), sizeof(int)) < 0)
        std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;

    // Pasivny soket je len na strane servera
    bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));
    listen(serverSocket, 5);    // Pasivny soket - nesluzi na komunikaciu, ale len aby sa k nemu niekto pripojil; 5 - najviac 5 ludi pripojit v jednom okamziku

    std::cout << "Server je spusteny a pocuva na porte " << port << std::endl;

    int playerId = 1;
    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        // Vytvorenie noveho vlakna pre obsluhu noveho klienta
        std::thread(handleClient, clientSocket, playerId).detach();

        playerId++;
        if (playerId > 3) {
            playerId = 1;
        }
    }

    close(serverSocket);
    return 0;
}
