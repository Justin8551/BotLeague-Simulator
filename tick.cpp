#include "tick.h"

Tick::Tick()
{
    this->nr_tick = 0;
    this->tip_tick = 0;
    this->poz_noua_inamic = {0, 0};
}

Tick::Tick(int nr_tick, int tip_tick, std::pair<int, int> poz_noua_inamic)
{
    this->nr_tick = nr_tick;
    this->tip_tick = tip_tick;
    this->poz_noua_inamic = poz_noua_inamic;
}

Tick::~Tick()
{

}

int Tick::getNrTick() const
{
    return this->nr_tick;
}

int Tick::getTipTick() const
{
    return this->tip_tick;
}

std::pair<int, int> Tick::getPozNouaInamic() const
{
    return this->poz_noua_inamic;
}

std::istream& operator>>(std::istream& in, Tick& tick)
{
    //aux pentru cuvinte intermediare
    std::string aux;

    in >>aux;//TICK
    
    in >> tick.nr_tick;

    in >> aux; //tip Tick

    if(aux == "WAIT")
    {
        tick.tip_tick = 0;
    }
    else if(aux == "MOVE")
    {
        tick.tip_tick = 1;
        in >> tick.poz_noua_inamic.first >> tick.poz_noua_inamic.second;
    }
    return in;
}