# BotLeague-Simulator

Acest proiect reprezinta un motor de simulare pentru un joc de strategie bazat pe grid, unde un bot autonom concurează pentru colectarea eficientă a resurselor. Programul gestioneaza logica de miscare, interactiunea cu mediul (obstacole și power-ups) si procesarea evenimentelor de tip "Tick".

Tehnologii folosite:
 - C++
 - Standard Template Library (STL): utilizat pentru simplificarea programului
 - Pathfinding: Implementare BFS (Breadth-First Search) optimizata pentru determinarea celui mai scurt drum catre obiective.
 - Strategie de decizie: Utilizarea metodei Greeady pentru prioritizarea resurselor

Organizare:
 - main.cpp gestioneaza bucla principala de citire si executie
 - bot.cpp/bot.h gestioneaza starea agentului
 - harta.cpp/harta.h reprezinta mediul de joc
 - tick.cpp/tick.h proceseaza actiunile inamicului si actualizeaza starea simularii
 - simulare.cpp/simulare.h gestioneaza interactiunea dintre bot, harta si eventimentele de tip tick

Optimizari:
 - Utilizarea unei matrici de tip bool pentru a optimiza cautarea BFS(evita ciclurile)
 - Simulatorul este conceput modular, in 9 fisiere pentru a asigura o mentenanta lizibila

Autor: Dumitru Gabriel Justin(322AB)
