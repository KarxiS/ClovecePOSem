#include <iostream>
#include <vector>
#include <thread>

void producer() {

}


void consumer() {

}



















int main() {
    std::vector<std::thread> threads;
    int pocetBanikov = 2;
    int velkostNastenky = 10;

    srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;
    //std::thread producerThread();

//    for (int i = 0; i < pocetBanikov; ++i) {
//        threads.push_back(std::thread(consumer, std::ref(nastenka)));
//    }
//    for (auto& thread : threads) {
//        thread.join();
//    }
//    producerThread.join();

    return 0;
}
