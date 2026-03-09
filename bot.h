#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <cmath>
#include <vector>


class Bot
{
private:
    std::pair<int, int> poz;
    double scor_final;
    int multiplicator;
    bool jump;
public:
    Bot();
    Bot(std::pair<int, int> poz, double scor_final, int multiplicator, bool jump);
    ~Bot();

    std::pair<int, int> getPoz() const;
    double getScorFinal() const;
    int getMultiplicator() const;
    bool getJump() const;
    void setPoz(std::pair<int, int> pozitie);
    void setMultiplicator(int multiplicator);
    void setJump(bool jump);
    
    void colecteaza_cel(std::string continutCel); //metoda de colectare

    friend std::ostream& operator<<(std::ostream&out, const Bot& bot); //metoda de scriere
};