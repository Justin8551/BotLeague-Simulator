Dumitru Gabriel Justin - 322AB

Programul meu este implementat sa functioneze intr un mod optim din punct de vedere al timpului si al memoriei deoarece folosesc STL uri(exemplu std::pair, std::queue, std::vector) pentru simplitate si intelegere mai bine a programului.

Algoritmul principal pentru rezolvare este BFS cu 2 cozi si o matrice de tip bool, pentru evidenta celulelor vizitate, si metodele "gaseste_optim", respectiv "pas_viitor" ajuta la respectarea si rezolvarea cerintelor intr un mod cat mai lizibil si usor de inteles, folosindu se si de metodele ajutatoare din celelalte clase.

Bot ul ia deciziile intr un mod "greeady", evaluand mereu cea mai buna optiune dupa harta printr un sistem de prioritati bine stabilit, unde "jump" ul este cel mai important, urmat de "triple", "double" si valorile numerice, dar aceasta prioritate este conditionata de distanta dintre bot si resursa, de aceea modalitatea de prioritati este foarte stabila si se muleaza perfect pe acest tip de cerinta.

In main am apelat functia de rulare a testelor, principiul functiei este urmatorul: citesc datele despre Arena, bot, inamic si le salvez in clasele aferente, iar mai apoi citesc "TICK" urile si incep procesarea de date. Cu ajutorul metodei "procesare_tick" citesc actiunile inamicului si apelez metodele specifice pentru miscarile bot ului, incluzand restrictiile cerintei.

Am organizat programul in 9 fisiere (4 .h uri si 5 .cpp uri): main.cpp , bot.h/bot.cpp , harta.h/harta.cpp , tick.h/tick.cpp , 
simulare.h/simulare.cpp. fisierele header au implementate clase specifice numelui, iar in fisierele .cpp sunt impementate metodele.

Clasa Bot: acesta retine pozitia, scorul final acumulat, multiplicatorul si functia jump(da/nu) al bot ului, are implementate metodele specifice (Constructorii/Destructor gol dar necesar pentru compilare), gettere, settere si doua metode ajutatoare care se ocupa cu colectarea de continut din celule si scrierea miscarii botului.

Clasa Harta: aceasta contine matricea de string uri, dimensiunile, rundele, pozitia botului pe harta, pozitia inamicului pe harta si pozitia celulei de final, are implementate metodele specifice(Constructorii/Destructorul gol dar necesar pentru compilare/operatorul= si operatorul de copiere), gettere, settere si doua metode ajutatoare care se ocupa cu verificarea mutarii de pe o celula pe alta si cu citirea de informatii din fisierul input.

Clasa Tick: aceasta retine numarul curent de tick, tipul de tick (0 - WAIT/ 1 - MOVE) si pozitia noua a inamicului(de fiecare data cand se muta), are implementate metodele specifice(Constructorii/Destructorul gol dar necesar pentru compliare), gettere si o metoda ajutatoare pentru citire a informatiilor din fisierul input.

Clasa Simulare: aceasta contine obiecte de tip Harta si Bot, runda curenta, rundele totale si o variabila de tip bool care specifica daca testul a ajuns la final sau nu, are implementate metodele principale ale programului, metodele specifice(Constructorii/Destructorul gol dar necesar pentru compilare) si doua metode ajutatoare pentru procesarea datelor si rularea programului.

Am folosit AI(Google Gemini) pentru implementarea in mare a buclei din "BFS" ul cu 2 cozi, pentru implementarea acelui test care activeaza jump ul temporar pentru a testa varianta drumului cu jump din metoda "gaseste_optim" si in modul de implementare al vectorului vecin din metoda "pas_viitor", ideea de implementare si logica este gandita de mine dar m am ajutat de AI pentru dezvoltarea in cod a anumitor parti.
# BotLeague-Simulator
