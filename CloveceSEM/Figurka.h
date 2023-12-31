#pragma once
class Figurka {
private:
    char znak;
    int suradnicaX;
    int suradnicaY;
    int spawnX;
    int spawnY;
    void setSuradnicaX(int x);
    void setSuradnicaY(int y);
public:
    Figurka(char parZnak, int x, int y);
    char getZnak();
    int getSuradnicaX();
    int getSuradnicaY();
    Figurka setXY(int x, int y);
    Figurka vyhodFigurku();


};

