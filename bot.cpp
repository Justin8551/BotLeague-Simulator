#include "bot.h"

Bot::Bot()
{
    this->poz = {0, 0};
    this->scor_final = 0.0;
    this->multiplicator = 1;
    this->jump = false;
}

Bot::Bot(std::pair<int, int> poz, double scor_final, int multiplicator, bool jump)
{
    this->poz = poz;
    this->scor_final = scor_final;
    this->multiplicator = multiplicator;
    this->jump = jump;
}

Bot::~Bot()
{

}

std::pair<int, int> Bot::getPoz() const
{
    return this->poz;
}

double Bot::getScorFinal() const
{
    return this->scor_final;
}

int Bot::getMultiplicator() const
{
    return this->multiplicator;
}

bool Bot::getJump() const
{
    return this->jump;
}

void Bot::setPoz(std::pair<int, int> poz)
{
    this->poz = poz;
}

void Bot::setMultiplicator(int multiplicator)
{
    this->multiplicator = multiplicator;
}

void Bot::setJump(bool jump)
{
    this->jump = jump;
}

void Bot::colecteaza_cel(std::string continutCel)
{
    if (continutCel == "0") //daca celula este goala, ies din functie
    {
        return;
    }
    if(continutCel == "D") //modific multiplicatorul curent cu x2
    {
        this->multiplicator = this->multiplicator * 2;
    }
    else if(continutCel == "T") //modific multiplicatorul curent cu x3
    {
        this->multiplicator = this->multiplicator * 3;
    }
    else if (continutCel == "J") //activez jump ul
    {
        this->jump = true;
    }
    else if(std::isdigit(continutCel[0])) //daca e numar
    {
        int valoare_cel = std::stoi(continutCel); //transform textul in intreg
        scor_final = scor_final + (double)valoare_cel * multiplicator; //il adaug la scorul final, inmultind cu multiplicatorul curent
    }
}

std::ostream& operator<<(std::ostream& out, const Bot& bot)
{
    out << "MOVE " << bot.poz.first << " " << bot.poz.second << '\n'; //scrierea mutarii botului conform cerintei
    return out;
}