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
    std::string hraciaDoska;
    int hodKockou;
    bool jeKoniec;
};

void handleClient(int clientSocket, int playerId, Hra& hra) {
    while (true) {
        // Prijatie akcie od klienta (hod kockou)
        char buffer[256];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << "Chyba pri citani zo soketu pre hraca " << playerId << std::endl;
            break;
        }

        // Simulácia hodu kockou
        std::lock_guard<std::mutex> lock(diceMutex);
        diceResult = rand() % 6 + 1;
        //diceResult = kocka.hodkocou();

        // Aktualizácia stavu hry
        hra.spravTah(playerId, 1, diceResult); // Assuming 1 is the position of the player's piece
        StavHry stavHry;
        stavHry.hodKockou = diceResult;
        std::string board = hra.ukazVysledok();
        std::cout<< hra.ukazVysledok();
        // Send the length of the string
        size_t length = board.size();
        send(clientSocket, reinterpret_cast<char*>(&length), sizeof(length), 0);

        // Send the string data
        send(clientSocket, board.c_str(), board.size(), 0);

        // Send the hodKockou field
        send(clientSocket, reinterpret_cast<char*>(&stavHry.hodKockou), sizeof(stavHry.hodKockou), 0);

        // Send the jeKoniec field
        send(clientSocket, reinterpret_cast<char*>(&stavHry.jeKoniec), sizeof(stavHry.jeKoniec), 0);

        std::cout << "Hrac " << playerId << " hodil kockou a ziskal: " << diceResult << std::endl;


}
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    Hrac hrac1("Jozef", '1');
    Hrac hrac2("Matus", '2');
    Hrac hrac3("Kiko", '3');
    Hrac hrac4("Rasto", '4');

    Hra hra;
    hra.zapisHraca(hrac1);
    hra.zapisHraca(hrac2);
    hra.zapisHraca(hrac3);
    hra.zapisHraca(hrac4);

    hra.zacniHru();

    short port = 12500;
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
        std::thread(handleClient, clientSocket, playerId, std::ref(hra)).detach();

        playerId++;
        if (playerId > 4) {
            playerId = 1;
        }
    }

    close(serverSocket);
    return 0;
}
