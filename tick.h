#pragma once
#include <iostream>
#include <string>

class Tick
{
private:
    int nr_tick;
    int tip_tick;
    std::pair<int, int> poz_noua_inamic;
public:
    Tick();
    Tick(int nr_tick, int tip_tick, std::pair<int, int> poz_noua_inamic);
    ~Tick();

    int getNrTick() const;
    int getTipTick() const;
    std::pair<int, int> getPozNouaInamic() const;

    friend std::istream& operator>>(std::istream& in, Tick& tick); //metoda de citire
};