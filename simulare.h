#pragma once
#include <queue>
#include "harta.h"
#include "bot.h"
#include "tick.h"

class Simulare
{
private:
    Harta harta;
    Bot eu;
    Bot inamic;

    int runda_crt;
    int runde_tot;
    bool gata;

    int BFS(std::pair<int, int> start, std::pair<int, int> destinatie); //metoda pentru a cauta distanta minima folosind algoritmul BFS(Breadth-First Search), practic cauta in latime
    std::pair<int, int> gaseste_optim(); //metoda pentru gasirea celei mai profitabile celule
    std::pair<int, int> pas_viitor(std::pair<int, int> tinta); //metoda pentru gasirea celei mai bune directii spre cea mai profitabila celula(dintre sus/jos/stanga/dreapta)

public:
    Simulare();
    Simulare(Harta harta, Bot eu, Bot inamic);
    ~Simulare();

    void proceseaza_tick(const Tick& tick); //metoda pentru procesarea tick ului facut de inamic, iar mai apoi decid mutarea facuta de bot
    void ruleaza_simulare(); //metoda pentru rularea simularii(citirea si executarea)
};