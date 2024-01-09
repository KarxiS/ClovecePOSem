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
    int hracNaTahu=-1;
    char playerID='0';
};

struct HraMutex {
    Hra hra;
    std::mutex mutex;
    std::condition_variable hrac;
    std::condition_variable zapisanie;
    bool obsadene=false;
    int aktualnyHrac = -1;
    bool koniecHry= false;
    std::string vitaz;
};

struct KockaMutex{
    std::vector<int> data;
    std::mutex mutex;
    std::condition_variable generuj;
    std::condition_variable konzumuj;
};

void handleClient(int clientSocket, int playerId, HraMutex& hraMutex, KockaMutex& kockaMutex) {
    LocalInfo localInfo;
    localInfo.playerID=playerId+'0';
    send(clientSocket, reinterpret_cast<char*>(&localInfo.playerID), sizeof(localInfo.playerID), 0);

    Hrac hrac("Jozef", localInfo.playerID);
    hraMutex.hra.zapisHraca(hrac);

    std::string boardClient = hraMutex.hra.ukazVysledok();
    std::cout << boardClient << std::endl;
    std::cout << "pripojil sa hrac "<<playerId<<std::endl;

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

        std::unique_lock<std::mutex> lockHra(hraMutex.mutex);
        hraMutex.obsadene=true;

        while(playerId!=hraMutex.aktualnyHrac%4){
            hraMutex.hrac.wait(lockHra);
        }
        std::cout<< "na rade je hrac "<<playerId<<std::endl;
        stavHry.naRade=true;
        hraMutex.aktualnyHrac++;

        // Simulácia hodu kockou
        std::unique_lock<std::mutex> lock(kockaMutex.mutex);
        while (kockaMutex.data.empty()) {
            kockaMutex.generuj.notify_one();
            kockaMutex.konzumuj.wait(lock);
        }
        diceResult = kockaMutex.data.back();
        kockaMutex.data.pop_back();
        lock.unlock();

        //Aktualizacia dat
        stavHry.hodKockou = diceResult;
        stavHry.jeKoniec = hraMutex.hra.jeHracVitaz(hrac);
        if(stavHry.jeKoniec){
            hraMutex.koniecHry= true;
            hraMutex.vitaz=hrac.getMeno();
        }
        std::string board = hraMutex.hra.ukazVysledok();
        std::cout<< board;

        // boardSize
        size_t length = board.size();
        send(clientSocket, reinterpret_cast<char*>(&length), sizeof(length), 0);

        // board
        send(clientSocket, board.c_str(), board.size(), 0);

        // hodKockou
        send(clientSocket, reinterpret_cast<char*>(&stavHry.hodKockou), sizeof(stavHry.hodKockou), 0);

        //jeKoniec
        send(clientSocket, reinterpret_cast<char*>(&stavHry.jeKoniec), sizeof(stavHry.jeKoniec), 0);

        if (hraMutex.koniecHry) {
            send(clientSocket, hraMutex.vitaz.c_str(), hraMutex.vitaz.size(), 0);
            break;
        }

        std::cout << "Hrac " << playerId << " hodil kockou a ziskal: " << diceResult << std::endl;

        //vybranie figurky
        std::string panacikVyber = "napis jedno cislo od 1-4 na ovladanie zvoleneho panacika, napis 0 ak chces vynechat svoj tah";
        size_t lengthRozhodnutie = panacikVyber.size();
        send(clientSocket, reinterpret_cast<char*>(&lengthRozhodnutie), sizeof(lengthRozhodnutie), 0);
        send(clientSocket, panacikVyber.c_str(), panacikVyber.size(), 0);

        //prijem rozhodnutia
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

        lockHra.unlock();

        hraMutex.obsadene=false;
        hraMutex.hrac.notify_all();
    }
}

void handleLocalPlayer(int playerId, HraMutex &hraMutex, KockaMutex &kockaMutex) {
    LocalInfo localPlayer;
    localPlayer.playerID = playerId + '0';
    Hrac localHrac("Local Player", localPlayer.playerID);
    hraMutex.hra.zapisHraca(localHrac);

    std::string board = hraMutex.hra.ukazVysledok();
    std::cout << board << std::endl;
    while (true) {
        std::unique_lock<std::mutex> lockHra(hraMutex.mutex);
        // Check if it's the local player's turn
        while (playerId != hraMutex.aktualnyHrac % 4) {
            hraMutex.hrac.wait(lockHra);
        }
        // Let the local player take their turn
        std::cout << "Lokalny hrac je na tahu" << std::endl;
        std::cout << "stikni Enter na hod kockou" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        std::unique_lock<std::mutex> lock(kockaMutex.mutex);
        while (kockaMutex.data.empty()) {
            kockaMutex.generuj.notify_one();
            kockaMutex.konzumuj.wait(lock);
        }
        diceResult = kockaMutex.data.back();
        kockaMutex.data.pop_back();
        lock.unlock();

        std::cout << "hodil si: " << diceResult << std::endl;

        // Update the game state
        char rozhodnutieFigurka;
        std::cout << "zvol jedno cislo od 1-4 na ovladanie zvoleneho panacika, napis 0 ak chces vynechat svoj tah" << std::endl;
        std::cin.get(rozhodnutieFigurka);

        if (rozhodnutieFigurka == '0') {
            // vynechanie
            std::cout << "Hrac " << playerId << " vynechal svoj tah" << std::endl;
        } else if (rozhodnutieFigurka >= '1' && rozhodnutieFigurka <= '4') {
            // posun
            std::cout << "Hrac " << playerId << " posunul figurinu " << rozhodnutieFigurka << "o " << diceResult << "." << std::endl;
            hraMutex.hra.spravTah(playerId, rozhodnutieFigurka - '0', diceResult);
            if (hraMutex.hra.jeHracVitaz(localHrac)) {
                hraMutex.koniecHry = true;
                hraMutex.vitaz = localHrac.getMeno();
            }
        } else {
            //TODO
            std::cerr << " zle cislo, pytam sa znova " << playerId << ": " << rozhodnutieFigurka << std::endl;
        }

        hraMutex.aktualnyHrac++;
        lockHra.unlock();
        // Print the game board
        std::string board = hraMutex.hra.ukazVysledok();
        std::cout << board << std::endl;

        hraMutex.hrac.notify_all();
    }
    // Wait for other players
}


void diceRollProducer(KockaMutex& kocka) {
    std::srand(std::time(0));

    while (true) {  // Always generate 10 dice rolls

        int diceRoll = 1 + std::rand() % 6;
        std::unique_lock<std::mutex> lock(kocka.mutex);
        while (kocka.data.size() >= 3) {
            kocka.generuj.wait(lock);
        }
        std::cout << "generujem cisla z kocky" << std::endl;
        kocka.data.push_back(diceRoll);
        lock.unlock();
        kocka.konzumuj.notify_one();
    }
}


int main() {
    srand(static_cast<unsigned>(time(0)));

    HraMutex hraMutex;
    KockaMutex kockaMutex;
    hraMutex.hra.zacniHru();

    short port = 12505;
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

    bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));
    listen(serverSocket, 5);
    // Pasivny soket - nesluzi na komunikaciu, ale len aby sa k nemu niekto pripojil; 5 - najviac 5 ludi pripojit v jednom okamziku

    std::cout << "Server je spusteny a pocuva na porte " << port << std::endl;
    std::thread(diceRollProducer,std::ref(kockaMutex)).detach();
    int playerId = 0;
    std::thread(handleLocalPlayer, playerId++, std::ref(hraMutex),std::ref(kockaMutex)).detach();
    while (true) {
        // Prijímanie pripojenia
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        // Skontrolovanie stavu hry pred vytvorením nového vlákna pre obsluhu nového klienta
        if (hraMutex.koniecHry) {
            std::cout << "Hra skoncila." << std::endl;
            std::cout << "Vitazom hry sa stal " << hraMutex.vitaz << std::endl;
            break;
        }
        // Vytvorenie noveho vlakna pre obsluhu noveho klienta
        std::thread(handleClient, clientSocket, playerId, std::ref(hraMutex),std::ref(kockaMutex)).detach();

        playerId++;
        if (playerId >= 4) {
            playerId = 0;
            hraMutex.aktualnyHrac=0;
            std::cout<< "su pripojeny vsetci stlacte enter na zacatie hry"<< std::endl;
            hraMutex.hrac.notify_all();
        }
    }
    close(serverSocket);
    return 0;
}
