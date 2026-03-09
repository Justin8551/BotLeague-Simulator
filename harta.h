#pragma once
#include "bot.h"

class Harta
{
private:
    std::vector<std::vector<std::string>> ARENA;
    int N,M,Runde;
    std::pair<int, int> poz_eu;
    std::pair<int, int> poz_inamic;
    std::pair<int, int> poz_final;
public:
    Harta();
    Harta(int N, int M, int Runde, std::pair<int, int> poz_eu,
         std::pair<int, int> poz_inamic, std::pair<int, int> poz_final,
         std::vector<std::vector<std::string>> ARENA);
    ~Harta();
    Harta& operator=(const Harta& other);
    Harta(const Harta& other);

    int getN() const;
    int getM() const;
    int getRunde() const;
    std::pair<int, int> getPozEu() const;
    std::pair<int, int> getPozInamic() const;
    std::pair<int, int> getPozFinal() const;
    std::string getContinutCel(std::pair<int, int> cel) const;
    std::string setZeroContinutCel(std::pair<int, int> cel);

    bool confirm_miscare(std::pair<int, int> cel_start ,std::pair<int, int> cel_destinatie ,bool jump) const; //metoda de verificare
    
    friend std::istream& operator>>(std::istream& in, Harta& harta); //metoda de citire
};