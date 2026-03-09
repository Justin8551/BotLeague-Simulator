#include "simulare.h"

Simulare::Simulare()
{
    this->harta = Harta();
    this->eu = Bot();
    this->inamic = Bot();
    this->runda_crt = 0;
    this->runde_tot = 0;
    this->gata = false;
}

Simulare::Simulare(Harta harta, Bot eu, Bot inamic)
{
    this->harta = harta;
    this->eu = eu;
    this->inamic = inamic;
    this->runda_crt = 0;
    this->runde_tot = harta.getRunde();
    this->gata = false;
}

Simulare::~Simulare()
{

}

int Simulare::BFS(std::pair<int, int> start, std::pair<int, int> destinatie)
{
    //daca pornesc de unde vreau sa ajung returnez 0
    if(start == destinatie)
    {
        return 0;
    }

    //cozi pt parcurgere, una pentru pozitiile curente cealalta pentru nr de miscari
    std::queue<std::pair<int, int>> q_crt;
    std::queue<int> q_nr;
    q_crt.push(start);
    q_nr.push(0);

    //matrice pt a tine evidenta celulelor vizitate din harta
    std::vector<std::vector<bool>> viz(harta.getN(), std::vector<bool>(harta.getM(), false));
    viz[start.first][start.second] = true;

    int miscare[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};//miscarile sus jos stanga dreapta

    //bucla principala de parcurgere
    while(!q_crt.empty())
    {
        //folosim elementele din cozi si numarul de miscari
        std::pair<int, int> crt = q_crt.front();
        int nr = q_nr.front();
        q_crt.pop();
        q_nr.pop();

        //cand ajung la destinatie returnez nr de mutari
        if(crt == destinatie)
        {
            return nr;
        }

        //for pentru cele 4 miscari
        for(int i=0;i<4;i++)
        {
            std::pair<int, int> urm = {crt.first + miscare[i][0], crt.second + miscare[i][1]}; //urmatoarea pozitie pentru verificare

            //verificarea mutarii fara jump
            if(harta.confirm_miscare(crt, urm, false))
            {
                std::string cont = harta.getContinutCel(urm); //retin continutul celulei
                if (!viz[urm.first][urm.second] && cont != "F") // daca nu am mai trecut si nu e foc este ok
                {
                    viz[urm.first][urm.second] = true; // o marchez ca vizitata
                    
                    //procesez urmatoarea poz
                    q_crt.push(urm);
                    q_nr.push(nr + 1);
                }
            }

            //daca jump este activ
            if(eu.getJump())
            {
                std::pair<int, int> urm_jump = {crt.first + 2 * miscare[i][0], crt.second + 2 * miscare[i][1]}; //urmatoarea pozitie pentru verificare

                //verificarea mutarii cu jump
                if(harta.confirm_miscare(crt, urm_jump, eu.getJump()))
                {
                    std::string cont_jump = harta.getContinutCel(urm_jump); // retin continutul celulei
                    if (!viz[urm_jump.first][urm_jump.second] && cont_jump != "F") // daca nu este vizitata deja si nu e foc este ok
                    {
                        viz[urm_jump.first][urm_jump.second] = true; // o marchez ca vizitata
                        
                        //procesez urm poz cu jump activ
                        q_crt.push(urm_jump);
                        q_nr.push(nr + 1);
                    }
                }
            }
        }
    }
    return -1; //daca cozile sunt goale returnez -1 pentru ca nu am gasit un drum valid
}

std::pair<int, int> Simulare::gaseste_optim()
{
    //pozitia curenta a botului si pozitia unde trebuie sa ajunga
    std::pair<int, int> poz_eu = eu.getPoz();
    std::pair<int, int> poz_final = harta.getPozFinal();

    int timp_ramas = runde_tot - runda_crt + 1;
    int dist_final = BFS(poz_eu, poz_final); //distanta pana la final

    //daca distanta finala este mai departe decat timpul ramas merg direct spre final
    if (dist_final != -1 && dist_final >= timp_ramas)
    {
        return poz_final;
    }

    std::pair<int, int> cel_optim = poz_final; //celula optima este initial cea finala

    //am initializat o variabila prioritate maxima pentru comparatie si pentru a putea seta prioritatile intre celulele cu valori si cele cu J/D/T
    double prioritate_max = -1.0;

    //parcurgerea celulelor din harta
    for(int i=0;i<harta.getN();i++)
    {
        for(int j=0;j<harta.getM();j++)
        {
            std::string cont = harta.getContinutCel({i, j});//retin continutul celulei

            int dist_resursa = BFS(poz_eu, {i, j}); //variabila care retine distanta pana la resursa

            //variabila prioritate pentru comparatie cu cea max si un char pentru a retine tipul resursei (J/D/T/numar)
            double prioritate = 0.0;
            char tip = cont[0];

            //jump ul are cea mai mare prioritate deoarece schimba modul de deplasare mult mai optim dpdv al distantelor
            if(tip == 'J' && !eu.getJump())
            {
                prioritate = 10000.0 / dist_resursa; //aceasta formula este pur sugestiva pentru prioritate per distanta parcursa, ea nu schimba deloc valorile din harta
            }
            //double are prioritate mai scazuta 
            else if(tip == 'D')
            {
                prioritate = 8000.0/ dist_resursa;
            }
            //triple are prioritate medie
            else if(tip == 'T')
            {
                prioritate = 9000.0 / dist_resursa;
            }
            //daca este o valoare numerica calculez prioritatea in functie de valoarea ei(cu multiplicator) per distanta parcursa
            else if(std::isdigit(tip))
            {
                int val = std::stoi(cont);
                prioritate = (double)(val * eu.getMultiplicator()) / dist_resursa;
            }

            int dist_resursa_final; //variabila pentru distanta de la resursa pana la final

            //daca resursa optima este jump dar nu il am activat, retin starea initiala, il activez temporar pentru a putea vedea distanta de la resursa la final..
            //..si dupa stabilesc daca este valid sa merg acolo sau nu, apoi revin la starea initiala
            if(tip == 'J' && !eu.getJump())
            {
                bool jump_temp = eu.getJump();
                eu.setJump(true);
                dist_resursa_final = BFS({i, j}, poz_final);
                eu.setJump(jump_temp);
            }
            //daca nu este jump doar calculez distanta respectiva
            else
            {
                dist_resursa_final = BFS({i, j}, poz_final);
            }

            //daca distanta de la resursa la final este valida si mai am timp pentru aceasta mutare, modific prioritatea si celula optima daca este necesar
            if(dist_resursa_final != -1 && (dist_resursa + dist_resursa_final <= timp_ramas))
            {
                if(prioritate > prioritate_max)
                {
                    prioritate_max = prioritate;
                    cel_optim = {i, j};
                }
            }
        }
    }
    return cel_optim; //dupa ce am parcurs toate celulele returnez cea cu prioritate maxima
}

std::pair<int, int> Simulare::pas_viitor(std::pair<int, int> tinta)
{
    std::pair<int, int> poz_eu = eu.getPoz(); //pozitia botului

    //daca pozitia botului este cea la care vreau sa ajung returnez pozitia curenta
    if(poz_eu == tinta)
    {
        return poz_eu;
    }

    //prima data pasul optim este pozitia botului si distanta minima este setata la o valoare mare pentru comparatie
    std::pair<int, int> pas_optim = poz_eu;
    int dist_min = 99999;

    int directii[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //miscarile sus jos stanga dreapta

    //for pentru cele 4 miscari
    for(int i=0;i<4;i++)
    {
        std::pair<int, int> vec = {poz_eu.first + directii[i][0], poz_eu.second + directii[i][1]}; //variabila pentru vecinul din directia specificata

        //confirm daca pot face miscarea fara jump
        if(harta.confirm_miscare(poz_eu, vec, false))
        {
            int dist = BFS(vec, tinta); //calculez distanta de la vecin la tinta(unde vreau sa ajung)

            //daca distanta este buna si e mai mica decat cea minima, setez distanta si pasul optim pentru bot
            if(dist != -1 && dist < dist_min)
            {
                dist_min = dist;
                pas_optim = vec;
            }
        }

        //daca avem jump activ
        if(eu.getJump())
        {
            std::pair<int, int> vec_jump = {poz_eu.first + 2 * directii[i][0], poz_eu.second + 2 * directii[i][1]}; //variabila pentru vecinul cu jump din directia specificata

            //confirm daca pot face miscarea cu jump
            if(harta.confirm_miscare(poz_eu, vec_jump, true))
            {
                int dist = BFS(vec_jump, tinta); //calculez distanta de la vecin(cu jump) la tinta

                //daca distanta este buna si este mai mica decat cea minima, setez distanta si pasul optim pentru bot
                if(dist != -1 && dist < dist_min)
                {
                    dist_min = dist;
                    pas_optim = vec_jump;
                }
            }
        }
    } 
    return pas_optim; //dupa ce verific toate mutarile posibile returnez pasul optim
}


void Simulare::proceseaza_tick(const Tick& tick)
{
    //retin numarul tick ului curente
    runda_crt = tick.getNrTick();

    //daca acesta este 1(adica inamicul se misca)
    if(tick.getTipTick() == 1)
    {
        std::pair<int, int> poz_noua_inamic = tick.getPozNouaInamic();//retin pozitia noua
        inamic.setPoz(poz_noua_inamic);//o setez
        harta.setZeroContinutCel(poz_noua_inamic);//si setez locul pe unde a trecut cu "0"
    }

    //daca nu am ajuns la final si inca am runde de jucat
    if(gata == false && runda_crt <= runde_tot)
    {
        //imi stabilesc un obiectiv si decid care este urmatorul pas spre acesta, folosindu ma de metodele implemtate mai sus
        std::pair<int, int> obiectiv = gaseste_optim();
        std::pair<int, int> urm_poz = pas_viitor(obiectiv);

        eu.setPoz(urm_poz); //modific pozitia botului

        //daca am ajuns la final, schimb variabila in true
        if(eu.getPoz() == harta.getPozFinal())
        {
            gata = true;
        }

        std::string continut_cel = harta.getContinutCel(urm_poz); //retin continutul celulei unde am ajuns

        //daca este foc, jocul s a terminat
        if(continut_cel =="F")
        {
            gata = true;
        }
        else if(continut_cel != "0" && continut_cel != "W" && continut_cel != "E")
        {
            std::string cont = harta.setZeroContinutCel(urm_poz);//daca este valid(numar/D/T)
            eu.colecteaza_cel(cont);//colectez ce este in celula
        }
    }

    std::cout << eu; //scriu exact dupa fiecare tick al adversarului, mutarea pe care eu o fac
}


void Simulare::ruleaza_simulare()
{
    //daca nu mai pot sa citesc harti, se termina simulare
    if (!(std::cin >> harta))
    {
        return;
    }
    
    eu.setPoz(harta.getPozEu()); //setez pozitia botului initiala
    inamic.setPoz(harta.getPozInamic()); //setez pozitia inamicului initiala
    runde_tot = harta.getRunde(); //retin numarul de runde totale pentru test

    Tick tick;
    //citesc pe rand tick urile si retin informatiile necesare
    while (std::cin >> tick)
    {
        proceseaza_tick(tick);
        if (tick.getNrTick() >= runde_tot) break;//daca numarul de tick uri facute este mai mare decat nr de runde totale ies din while
    }
}