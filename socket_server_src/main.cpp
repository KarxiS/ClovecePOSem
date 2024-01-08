#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <condition_variable>
#include "../CloveceSEM/Hra.h"

std::mutex diceMutex;
int diceResult;
struct LocalInfo{
    char playerID='0';
};
struct StavHry {
    std::string hraciaDoska;
    int hodKockou=0;
    bool jeKoniec=false;
    bool naRade=false;
    int hracNaTahu=0;
    char playerID='0';
};

struct HraMutex {
    Hra hra;
    std::mutex mutex;
    std::condition_variable hrac;
    std::condition_variable zapisanie;
    bool obsadene=false;
    int aktualnyHrac = 0;
    bool jeKoniec=false;



};




void handleClient(int clientSocket, int playerId, HraMutex& hraMutex) {
    LocalInfo localInfo;


    localInfo.playerID=playerId+'0';
    send(clientSocket, reinterpret_cast<char*>(&localInfo.playerID), sizeof(localInfo.playerID), 0);
    Hrac hrac("Jozef", localInfo.playerID);
    hraMutex.hra.zapisHraca(hrac);







    while (true) {
        // Prijatie akcie od klienta (hod kockou)
        char bufferJoin[1];
        ssize_t bytesReadJoin = recv(clientSocket, bufferJoin, sizeof(bufferJoin), 0);
        if (bytesReadJoin <= 0) {
            std::cerr << "Hrac " << playerId <<" sa odpojil" << std::endl;
            hraMutex.hra.odpisHraca(playerId);
            break;
        }


        std::string boardMap = hraMutex.hra.ukazVysledok();
        // lengthData
        size_t lengthMap = boardMap.size();
        send(clientSocket, reinterpret_cast<char*>(&lengthMap), sizeof(lengthMap), 0);

        // data
        send(clientSocket, boardMap.c_str(), boardMap.size(), 0);


        char bufferHod[1];
        ssize_t bytesReadHod = recv(clientSocket, bufferHod, sizeof(bytesReadHod), 0);
        if (bytesReadHod <= 0) {
            std::cerr << "Hrac " << playerId <<" sa odpojil" << std::endl;
            hraMutex.hra.odpisHraca(playerId);
            break;
        }

        std::unique_lock<std::mutex> lockHra(hraMutex.mutex);
        hraMutex.obsadene=true;

        StavHry stavHry;

        if(playerId!=hraMutex.aktualnyHrac%4){
            stavHry.naRade=false;
            stavHry.hracNaTahu=hraMutex.aktualnyHrac%4;
            send(clientSocket, reinterpret_cast<char*>(&stavHry.naRade), sizeof(stavHry.naRade), 0);
            send(clientSocket, reinterpret_cast<char*>(&stavHry.hracNaTahu), sizeof(stavHry.hracNaTahu), 0);

            continue;
        }else{
            stavHry.naRade= true;
            send(clientSocket, reinterpret_cast<char*>(&stavHry.naRade), sizeof(stavHry.naRade), 0);

        }
        while(playerId!=hraMutex.aktualnyHrac%4){



            hraMutex.hrac.wait(lockHra);
        }
        stavHry.naRade=true;

        hraMutex.aktualnyHrac++;
        // Simulácia hodu kockou
        std::unique_lock<std::mutex> lock(diceMutex);
        diceResult = rand() % 6 + 1;

        //diceResult = kocka.hodkocou();


        // Aktualizácia stavu hrye

        //hraMutex.hra.spravTah(playerId, 1, diceResult);
        lock.unlock();

        stavHry.hodKockou = diceResult;
        std::string board = hraMutex.hra.ukazVysledok();
        std::cout<< hraMutex.hra.ukazVysledok();
        lockHra.unlock();

        // boardSize
        size_t length = board.size();
        send(clientSocket, reinterpret_cast<char*>(&length), sizeof(length), 0);

        // board
        send(clientSocket, board.c_str(), board.size(), 0);

        // hodKockou
        send(clientSocket, reinterpret_cast<char*>(&stavHry.hodKockou), sizeof(stavHry.hodKockou), 0);

        //jeKoniec
        send(clientSocket, reinterpret_cast<char*>(&stavHry.jeKoniec), sizeof(stavHry.jeKoniec), 0);

        std::cout << "Hrac " << playerId << " hodil kockou a ziskal: " << diceResult << std::endl;




        //vybranie figurky
        std::string panacikVyber = "napis jedno cislo od 1-4 na ovladanie zvoleneho panacika, napis 0 ak chces vynechat svoj tah";
        size_t lengthRozhodnutie = panacikVyber.size();
        send(clientSocket, reinterpret_cast<char*>(&lengthRozhodnutie), sizeof(lengthRozhodnutie), 0);
        send(clientSocket, panacikVyber.c_str(), panacikVyber.size(), 0);

        // prijem rozhodnutia
        char decisionBuffer[2];
        size_t bytesReadDecision = recv(clientSocket, decisionBuffer, sizeof(decisionBuffer), 0);
        if (bytesReadDecision <= 0) {
            std::cerr << "Hrac sa odpojil pocas vyberu panacika s id  " << playerId << std::endl;
            return;
        }
        int rozhodnutieFigurka = decisionBuffer[0] - '0';

        // rozhodnutie
        if (rozhodnutieFigurka == 0) {
            // vynechanie
            std::cout << "Hrac " << playerId << " vynechal svoj tah" << std::endl;
        } else if (rozhodnutieFigurka >= 1 && rozhodnutieFigurka <= 4) {
            // posun
            std::cout << "Hrac " << playerId << " posunul figurinu " << rozhodnutieFigurka << "o "<< diceResult  <<"." << std::endl;
            hraMutex.hra.spravTah(playerId, rozhodnutieFigurka, diceResult);
        } else {
            //TODO
            std::cerr << " zle cislo, pytam sa znova " << playerId << ": " << rozhodnutieFigurka << std::endl;
        }






        hraMutex.obsadene=false;
        hraMutex.hrac.notify_all();

}
}

void updateMap(std::vector<int>& clientSockets, HraMutex& hraMutex) {
    while (!hraMutex.hra.jeKoniec) {
        // Lock the mutex while updating and sending game state
        std::unique_lock<std::mutex> lock(hraMutex.mutex);


        for (int clientSocket : clientSockets) {
            std::string board = hraMutex.hra.ukazVysledok();
            send(clientSocket, reinterpret_cast<char*>(&hraMutex.jeKoniec), sizeof(hraMutex.jeKoniec), 0);
            // boardSize
            size_t length = board.size();
            send(clientSocket, reinterpret_cast<char*>(&length), sizeof(length), 0);

            // board
            send(clientSocket, board.c_str(), board.size(), 0);
        }
        lock.unlock();
        std::this_thread::sleep_for (std::chrono::seconds(2));
    }
}


void handleLocalPlayer(int playerId, HraMutex& hraMutex) {
    LocalInfo localPlayer;
    localPlayer.playerID = playerId + '0'; // or whatever ID you want to assign to the local player
    Hrac localHrac("Local Player", localPlayer.playerID);
    hraMutex.hra.zapisHraca(localHrac);

    while (true) {
        std::unique_lock<std::mutex> lockHra(hraMutex.mutex);
        // Check if it's the local player's turn
        while(playerId!=hraMutex.aktualnyHrac%4){

            hraMutex.hrac.wait(lockHra);
        }
            // Let the local player take their turn
            std::cout << "Lokalny hrac je na tahu\n stikni Enter na hod kockou \n";

            std::cin.get();

            // Simulate rolling the dice
            std::unique_lock<std::mutex> lock(diceMutex);
            diceResult = rand() % 6 + 1;
            lock.unlock();
            std::cout << "hodil si " << diceResult<< std::endl;
            // Update the game state
            // hraMutex.hra.spravTah(localPlayer.playerID - '0', 1, diceResult);
            std::cout <<"napis jedno cislo od 1-4 na ovladanie zvoleneho panacika, napis 0 ak chces vynechat svoj tah"<<std::endl;
            char rozhodnutieFigurka;
            std::cin.get(rozhodnutieFigurka);

            if (rozhodnutieFigurka == '0') {
                // vynechanie
                std::cout << "Hrac " << playerId << " vynechal svoj tah" << std::endl;
            } else if (rozhodnutieFigurka >= '1' && rozhodnutieFigurka <= '4') {
                // posun
                std::cout << "Hrac " << playerId << " posunul figurinu " << rozhodnutieFigurka << "o "<< diceResult  <<"." << std::endl;
                hraMutex.hra.spravTah(playerId, rozhodnutieFigurka - '0', diceResult);
            } else {
                //TODO
                std::cerr << " zle cislo, pytam sa znova " << playerId << ": " << rozhodnutieFigurka << std::endl;
            }



            // Print the game board
            std::string board = hraMutex.hra.ukazVysledok();
            std::cout << board << std::endl;
            hraMutex.aktualnyHrac++;
        }
        hraMutex.hrac.notify_all();

        // Wait for other players
        std::this_thread::sleep_for(std::chrono::seconds(1));

}




int main() {
    srand(static_cast<unsigned>(time(0)));



    HraMutex hraMutex;



    hraMutex.hra.zacniHru();

    short port = 12502;
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

    int playerId = 0;
    std::thread(handleLocalPlayer, playerId++, std::ref(hraMutex)).detach();
    std::vector<int> clientSockets;
    while (true) {


        int clientSocket = accept(serverSocket, nullptr, nullptr);


        // Vytvorenie noveho vlakna pre obsluhu noveho klienta
        std::thread(handleClient, clientSocket, playerId, std::ref(hraMutex)).detach();
        clientSockets.push_back(clientSocket);
        playerId++;
        //std::thread updateThread(updateMap, std::ref(clientSockets), std::ref(hraMutex));
        //updateThread.detach();
        if(playerId==4){
            hraMutex.aktualnyHrac=0;
            hraMutex.hrac.notify_all();

        }
        if (playerId >= 4) {
            playerId = 0;
        }
    }

    close(serverSocket);
    return 0;
}
