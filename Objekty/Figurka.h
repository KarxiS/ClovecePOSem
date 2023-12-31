#pragma once
class Figurka {
private:
    char znak;
    int suradnicaX;
    int suradnicaY;

public:
    Figurka(char parZnak, int x, int y);
    char getZnak();
    int getSuradnicaX();
    int getSuradnicaY();
};

