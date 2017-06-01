-------------------------------README-----------------------------------

	Pentru implementarea proiectului Laser-Tag am folosit structurile:
--> Structura player : defineste un jucator , contine caracteristicile necesare pentru a putea cele 3 top -uri si scorul final. In structura player shoots reprezinta totalul de puncte obtinut prin impuscaturi de un jucator, vectorul pozitie salveaza senzorii prin care trece jucatorul, alive este 0 daca e mort si 1 daca este inca in viata.

--> Structura matrix care are doua elemente nume si puncte, a fost folosita pentru salvarea unor tipuri de date si ordonare

--> Structura matrix_trageri care contine nume1 nume2 si puncte, ea retine numarul schimburilor de focuri dintr jucatorul nume1 si jucatorul nume2

--> struct vect are un singur element un vector alocat static , a fost folosit pentru a returna niste date

	Si clasele Hashtable si Graph:

==> Clasa Hashtable - o folosesc pentru a retine toti jucatorii si informatii despre acestia. Ea contine elementele:
- struct player *H un vector la o structura player
- HMAX dimensiunea maxima a hashtable ului
- (*hash) pointer la functia de hash
- st1 si st2 sunt numarul de puncte acumulate de cele doua echipe
- nr_players este numarul toatal de jucatori
                    - Ea contine metodele : put_player, get_number, get_name, kill, print, pozitie, vector_pozitii, top_shooters, winning_chance, winner, restart, print_distanta.

-> metoda put_player are ca argumente numele si echipa jucatorului, cand adaug un jucator trebuie sa initializez datele intiale si ca cresc un contor pentru numarul de jucatori

-> metoda get_number in functie de numele jucatorului returneaza un numar intre 0 si nr_players pe care il vom folosi pentru a obtine date din grafuri.

-> metoda get_name in functie de un umar intreg intre 0 si nr_players returneaza un nume

--> metoda kill are doua stringuri ca parametru primul reprezentand cel care impusca si al 2 lea e este cel care este impuscat. Functia are ca rol sa verifice daca jucatorii killer si victim sunt in viata sau nu , sa adauge sau sa scada punte pentru killer in functie de cine impusca si scade din vietile jucatorului victim.

-> metoda print am folosit-o mai mult pentru teste si verificare

--> metoda pozitie care are ca parametri numele unui jucator si senzorul pe langa a trecut, aceasta metoda adauga in vectorul pozitii al jucatorul carespunzator numelui o noua valoare cea corespunzatoare senzorului, si calculeaza o distanta partiala ce reprezinta numarul senzorilor unici prin care trece inmultiat cu 3

-> metoda vector_pozitii returneaza o structura struct vect in care este salvat vectorul pozitilor unui jucator

-> metoda add_distanta calculeaza distanta parcursa de un jucator pe parcursul unui campionat , este formata din distanta partiala plus distanta dintre senzorii printre care trece(aceasta valoare oobtine din graful de distante).

--> metoda top_shooters imi afiseaza topul celor mai bui tragatori in primul rand metoda procedeaza astfel:
	- salveaza toti jucatorii cu punctajele crespunzatoare corespunzatoare
	- ii ordonez in functie de puncte 
	- daca doi jucatori au acelasi scor ii ordonez alfabetic

-> winning_chance imi calculeaza sansa de castig a unei echipe in functie de formula data

-> winner verifica daca toti jucatorii unei echipe sunt morti deci rezulta ca cealalta echipa a castigat

-> restart imi reseteaza anumite valori pentru fiecare player

==> Clasa Graph am implementat-o cu o matrice de adiacenta si metodele:

-> add_edge imi adauga la imi adauga in matrice o valoare

-> add_shot imi creste cu 1 o pozitie din matrice

-> get_distanta imireturneaza distanta dintre 2 senzori

	In main citesc prima data marimea grafului distante si cu ajutorul unui for citesc valorile din graf. Dupa care citesc numarul de jucatori din ambele echipe si ii citesc si pe ei , dupa care cu ajutorul unui while citesc restul inputului si cu ajutorul unui if imi dau seama cand un joc s-a terminat. Pentru fiecare joc ma folosesc de metodele din hashtable si graf pentru a efectua operatia de pe linia curenta.
	La final afisez cele 3 topuri si scorul final.
