#include "harta.h"

Harta::Harta()
{
    this->N = 0;
    this->M = 0;
    this->ARENA = {};
    this->Runde = 0;
    this->poz_eu = {0, 0};
    this->poz_inamic = {0, 0};
    this->poz_final = {0, 0};
}

Harta::Harta(int N, int M, int Runde, std::pair<int, int> poz_eu,
             std::pair<int, int> poz_inamic, std::pair<int, int> poz_final,
             std::vector<std::vector<std::string>> ARENA)
{
    this->N = N;
    this->M = M;
    this->Runde = Runde;
    this->poz_eu = poz_eu;
    this->poz_inamic = poz_inamic;
    this->poz_final = poz_final;
    this->ARENA = ARENA;
}

Harta::~Harta()
{
    
}

Harta& Harta::operator=(const Harta& other)
{
    if(this != &other)
    {
        this->N = other.N;
        this->M = other.M;
        this->Runde = other.Runde;
        this->poz_eu = other.poz_eu;
        this->poz_inamic = other.poz_inamic;
        this->poz_final = other.poz_final;
        this->ARENA = other.ARENA;
    }
    return *this;
}

Harta::Harta(const Harta& other)
{
    this->N = other.N;
    this->M = other.M;
    this->Runde = other.Runde;
    this->poz_eu = other.poz_eu;
    this->poz_inamic = other.poz_inamic;
    this->poz_final = other.poz_final;
    this->ARENA = other.ARENA;
}

int Harta::getN() const
{
    return this->N;
}

int Harta::getM() const
{
    return this->M;
}

int Harta::getRunde() const
{
    return this->Runde;
}

std::pair<int, int> Harta::getPozEu() const
{
    return this->poz_eu;
}

std::pair<int, int> Harta::getPozInamic() const
{
    return this->poz_inamic;
}

std::pair<int, int> Harta::getPozFinal() const
{
    return this->poz_final;
}

bool Harta::confirm_miscare(std::pair<int, int> cel_start, std::pair<int, int> cel_destinatie, bool jump) const
{
    //verific daca destinatia este in afara hartii
    if(cel_destinatie.first < 0 || cel_destinatie.first >= N ||
       cel_destinatie.second < 0 || cel_destinatie.second >= M)
    {
        return false;
    }

    //verific daca celula la care vreau sa ajung este perete, empty sau foc
    std::string continut = ARENA[cel_destinatie.first][cel_destinatie.second];
    if(continut == "W" || continut == "E" || continut == "F")
    {
        return false;
    }

    //calculez distantele dintre cele 2 celule
    int dist_first = std::abs(cel_start.first - cel_destinatie.first);
    int dist_second = std::abs(cel_start.second - cel_destinatie.second);   

    //ma asigur ca miscarea este doar sus jos stanga dreapta
    if((dist_first > 0 && dist_second > 0 ) || (dist_first == 0 && dist_second == 0))
    {
        return false;
    }

    int dist = dist_first + dist_second;

    //implementez regulile pentru atunci cand am/n-am jump (pot doar sa sar peste perete si empty)
    if(jump == false)
    {
        return dist == 1;
    }
    else
    {
        if(dist < 1 || dist > 2)
        {   
            return false;   
        }

        if(dist == 2)
        {
            //verific sa nu sar peste foc
            int m_first = (cel_start.first + cel_destinatie.first) / 2;
            int m_second = (cel_start.second + cel_destinatie.second) / 2;
            if (ARENA[m_first][m_second] == "F")
                return false;
        }
        return true; //doar atunci cand miscarea este valida
    }
}

std::string Harta::getContinutCel(std::pair<int, int> cel) const
{
    return this->ARENA[cel.first][cel.second];
}

std::string Harta::setZeroContinutCel(std::pair<int, int> cel)
{
    std::string continut_vechi = ARENA[cel.first][cel.second]; //salvez continutul celulei
    ARENA[cel.first][cel.second] = "0"; //ii schimb continutul in "0"
    return continut_vechi; //returnez continutul
}

std::istream& operator>>(std::istream& in, Harta& harta)
{
    //un auxiliar pentru cuvintele nefolositoare
    std::string aux; // ARENA

    //citesc informatiile pentru ARENA
    in >> aux >> harta.N >> harta.M >> harta.Runde;
    in >> harta.poz_eu.first >> harta.poz_eu.second;
    in >> harta.poz_inamic.first >> harta.poz_inamic.second;
    in >> harta.poz_final.first >> harta.poz_final.second;

    in >> aux; //MAP

    harta.ARENA.resize(harta.N, std::vector<std::string>(harta.M)); //folosesc functia din STL resize pentru a definii harta

    //citesc celulele din harta
    for(int i=0; i<harta.N; i++)
    {
        for(int j=0; j<harta.M; j++)
        {
            in >> harta.ARENA[i][j];
        }
    }

    in >> aux; //END_MAP
    in >> aux; //STREAM
    return in;
}

