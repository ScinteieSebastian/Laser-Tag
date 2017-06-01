#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <list>
#include <string>
#include<math.h>
#define VMAX 100
using namespace std;
struct player {              // in structura player retin informatii despre fiecare jucator
    string  nume = "null";
    int vieti ;
    int shoots ;
    int shoot_joc;
    int distanta_joc;
    int distanta_totala;
    int alive ;
    int pozitie[100];
    int player_number;
    int echipa ;
};
struct matrix{
        string nume;
        int puncte;           // matrix si matrix_trageri le folosesc pentru sortari si afisari
};
struct matrix_trageri{
    string nume1;
    string nume2;
    int puncte;
};
struct vect{
    int poz[100];
};
class Graph {                   // structura graph in care retin distantele dintre senzori si numarul de trageri
    public:
         int **m;
         int size;
    //public:
        Graph(int size)
        {
            this->size = size;
            m = new int *[size];
            for( int i = 0 ; i< size; i++)
            {
                    m[i] = new int[size];
            }
            for(int i = 0; i<size; i++)
            {
                for(int j = 0; j < size ; j++)
                {
                    m[i][j] = 0;
                }
            }
        }
        ~Graph()
        {
            for( int i = 0 ; i< size; i++)
            {
                delete[] m[i];
            }
            delete[] m;
        }
        void add_edge(int src, int dst, int value)  // imi adauga un nod in graf si pune pe acea pozitie o valoare
        {
            m[src][dst] = value;
        }
        void add_shot(int src, int dst)            // imi creste valoarea de pe acea pozitie(o folosesc cand src il impusca pe dst)
        {
            m[src][dst] = m[src][dst] + 1;
        }
        int get_value(int src, int dst)            // returneaza valoarea de pe o pozitie
        {
            return (m[src][dst]+m[dst][src]);
        }
        int get_distanta(int src, int dst)        // returneaza distanta dintre 2 senzori
        {
            return m[src][dst];
        }
        void print()                              // printeaza graful
        {
            for(int i = 0; i<size; i++)
            {
                for(int j = 0; j < size ; j++)
                {
                    cout<<m[i][j]<<" ";
                }
                cout<<endl;
            }
        }
};
class Hashtable {                                  // structura Hashtable unde retin toti jucatorii
    public:
        struct player *H;
        int HMAX;
        unsigned int (*hash) (string);
        Hashtable(Hashtable& h){};
        Hashtable operator=(Hashtable& h){};
   // public:
        int st1,st2;
        int nr_players = 0;
        Hashtable(int hmax, unsigned int (*h)(string))
        {
            HMAX = hmax;
            hash = h;
            H = new struct player [HMAX];
            st1 = 0;
            st2 = 0;
        }
        ~Hashtable()
            {
                    delete[] H;
            }
        void put_player(string nume, int echipa)  // imi adauga un jucator , si precizez in ce echipa este
        {
            int index = hash(nume) % HMAX;
            H[index].nume = nume;
            H[index].vieti = 2;
            H[index].shoots = 0;                   // setez valori intiale petru fiecare jucator
            H[index].shoot_joc = 0;
            H[index].distanta_totala = 0;
            H[index].distanta_joc = 0;
            for(int i = 0; i < 100 ; i++)
            {
                    H[index].pozitie[i] = -1;
            }
            H[index].alive = 1;
            H[index].player_number = nr_players;
            nr_players++;
            H[index].echipa = echipa;
        }
         int get_number(string nume)                 // imi returneaza numele jucatorul in functie de index ul setat in functia put_player
        {
            int index = hash(nume) % HMAX;
            return H[index].player_number;
        }
        string get_name(int player_number)           // imi returneaza indexul setat in metoda put_player in functie de nume
        {
            string nume;
            for(int i = 0; i < HMAX; i++)
            {
                if(H[i].nume != "null")
                {
                if(H[i].player_number == player_number)
                    {
                        nume = H[i].nume;
                        break;
                    }
                }
            }
            return nume;
        }
          void kill(string killer,string victim)     // imi adauga adauga punctele corespunzatoare cand "killer" impusca "victim"
        {
            int index1 = hash(killer) % HMAX;
            int index2 = hash(victim) % HMAX;
            if(H[index1].vieti != 0)
            {
                if( H[index2].vieti != 0)       // verific daca player ul care impusca nu e mort
                {
                    if(H[index1].echipa != H[index2].echipa)        // verific daca nu fac parte din aceeasi ecipa pentru a sti cate puncte primeste
                    {
                        H[index1].shoots = H[index1].shoots + 2;
                        H[index1].shoot_joc = H[index1].shoot_joc +2; // adaug punctele corespunzatoare pentru "killer"
                        H[index2].vieti = H[index2].vieti - 1;    // scad numarul de vieti pentru "victim"
                    }
                    else                                            // daca fac parte din aceeasi echipa player ul e depunctat
                    {
                        H[index1].shoots = H[index1].shoots -5;
                        H[index1].shoot_joc = H[index1].shoot_joc - 5;
                        H[index2].vieti = H[index2].vieti - 1;    // scad numarul de vieti pentru "victim"
                    }
                }
                if(H[index2].vieti == 0)            // daca player ul care este impuscat nu i se mai pot scadea din numarul de vieti
                {
                    H[index2].alive = 0;
                }
            }
        }
          void print()                                  // printez intreg hashtable ul
        {
            for(int index  = 0; index < HMAX; index++)
                if(H[index].nume != "null")
                {
                    int i = 0;
                    cout<<"Nume: "<<H[index].nume<<endl;
                    cout<<"Nr_vieti: "<<H[index].vieti<<endl;
                    cout<<"Kills: "<<H[index].shoots<<endl;
                    cout<<"kill/joc: "<<H[index].shoot_joc<<endl;
                    cout<<"Distanta: "<<H[index].distanta_totala<<endl;
                    cout<<"Distanta/joc:"<<H[index].distanta_joc<<endl;
                    while(H[index].pozitie[i] != -1)
                    {
                        cout<<H[index].pozitie[i]<<" ";
                        i++;
                    }
                    cout<<endl;
                    cout<<"Nr_player: "<<H[index].player_number<<endl;
                    cout<<"Echipa: "<<H[index].echipa<<endl;
                    cout<<"Stare mediacala:"<<H[index].alive<<endl;
                    cout<<endl;
                }
        }
          void pozitie(string nume, int pozitie)       // imi adauga numarul de senzori inmultit cu 3 cand trece prin fata unui senzor nou
        {
            int k = 0, contor = 0, ok = 0;
            int index = hash(nume) % HMAX;
            while(H[index].pozitie[k] != -1)
                k++;
            H[index].pozitie[k] = pozitie;
            for(int i = 0 ; i <= k ; i++)
            {
                if(i == 0)
                    contor++;
                else
                {
                    for(int j = 0 ; j < i ; j++)
                    {
                        if(H[index].pozitie[i] != H[index].pozitie[j]) // numar prin cati senzori trece intr-o repriza
                            ok = 1;
                        else
                        {
                            ok = 0;
                            break;
                        }
                    }
                    if(ok == 1)
                        contor++;    // aici contorizez
                }
            }
            H[index].distanta_joc = 3*contor; // adaug la distanta pe joc numarul de senzori prin care trece * 3
        }
         vect vector_pozitii(string nume)  // imi returneaza vecotorul cu pozitiile prin care trece un player
        {
            int k = 0;
            int index = hash(nume) % HMAX;
            while(H[index].pozitie[k] != -1)
                k++;
            struct vect vect;
            for(int i = 0; i < k; i++)
            {
                vect.poz[i] = H[index].pozitie[i];
            }
            vect.poz[k] = -1;
        return vect;
        }
            void add_distanta(string nume, int value)//imi adauga
        {                                   // la distanta finala distanta
            int index = hash(nume) % HMAX;  // disntre senzorii prin care trece
            H[index].distanta_totala = H[index].distanta_totala + H[index].distanta_joc + value;
        }
         void top_shooters()  // imi afiseaza top-ul shooter-ilor
        {
            int k = 0;
            struct matrix aux;
            struct matrix m[1000];
            for(int i = 0; i < HMAX ; i++)
            {
                if(H[i].nume != "null")  // salvez in structura matrix numele
                {                         // si numarul de puncte
                    m[k].nume = H[i].nume;  // pentru fiecare jucator
                    m[k].puncte = H[i].shoots;
                    k++;
                }
            }
           for(int i = 0 ; i < k; i++)
            {
                for(int j = 0 ; j < k; j++)
                    {
                        if(m[i].puncte > m[j].puncte) //sortez in functie
                        {                             // de puncte
                            aux.puncte = m[i].puncte;
                            aux.nume = m[i].nume;
                            m[i].puncte = m[j].puncte;
                            m[i].nume = m[j].nume;
                            m[j].puncte = aux.puncte;
                            m[j].nume = aux.nume;
                        }
                    }
            }
            for(int i = 0 ; i < k; i++)
            {
                for(int j = 0 ; j < k; j++)
                    {
                        if(m[i].puncte == m[j].puncte) // daca doi jucatori
                        {                              // au acelasi numar
                            if(m[i].nume < m[j].nume)  // de puncte
                            {                          // atunci ii sortez
                            aux.puncte = m[i].puncte;   // alfabetic
                            aux.nume = m[i].nume;
                            m[i].puncte = m[j].puncte;
                            m[i].nume = m[j].nume;
                            m[j].puncte = aux.puncte;
                            m[j].nume = aux.nume;
                            }
                        }
                    }
            }
            if(k >= 4)                      // aici fac afisarea topului
            {
                for(int i = 0; i < 5 ; i++)  // daca numarul de jucatori e mai
                {                            // mic de 5 ii afisez pe primi 5
                    cout<<i+1<<"."<<" "<<m[i].nume<<" "<<m[i].puncte<<"p"<<endl;
                }
                int limita = 5;
                while(m[4].puncte == m[limita].puncte)
                {    //daca ultimul jucator are nr. de puncte egal cu urmatorii
                    cout<<limita+1<<"."<<" "<<m[limita].nume<<" "<<m[limita].puncte<<"p"<<endl;
                    limita++;
                    // ii afisez pe toti cu acelasi numar de puncte
                }
            }
            else   // daca numarul de jucatori e mai mic de 5 ii afisez pe toti
            {
                for(int i = 0; i < k ; i++)
                {
                    cout<<i+1<<"."<<" "<<m[i].nume<<" "<<m[i].puncte<<"p"<<endl;
                }
            }
        }
         void winnig_chance()   // imi calculeaza sansa de castig
        {                       // pentru ultima runda
            double winc1 = 0, winc2 = 0;
            double bestshooter, dist_max;
            int aux = 0, k = 0;
            double c1[100] = {0};
            double c2[100] = {0};
            for(int i = 0; i < HMAX; i++)
            {
                if(H[i].nume != "null")// salvez intr-un vector distanta totala
                {                        // numarul de impuscaturi
                    c1[k] = H[i].distanta_totala;
                    c2[k] = H[i].shoots;
                    k++;
                }

            }
            for(int i = 0; i < k; i++)
            {
                for(int j = 0; j < k ; j++)
                {
                    if(c1[i] >= c1[j])  //sortez matrice in functie de distanta
                    {
                        aux = c1[i];
                        c1[i] = c1[j];
                        c1[j] = aux;
                    }
                    if(c2[i] >= c2[j]) // sortez in functie de trageri
                    {
                        aux = c1[i];
                        c2[i] = c2[j];
                        c2[j] = aux;
                    }
                }
            }
            bestshooter = c2[0];  // setez cel mai bun tragator
            dist_max = c1[0];     // setez jucatorul cu cea mai mare distanta
            if(dist_max == 0)
                dist_max = 1;
            if(bestshooter == 0)
                bestshooter = 1;
            for(int i = 0 ; i < HMAX ; i++)
            {
            	if(H[i].nume != "null")
            	{
                if(H[i].echipa == 1) // aplic formula pentru fiecare echipa
                {
                    winc1 = winc1 + (H[i].alive * ((H[i].shoots/bestshooter) + (H[i].distanta_totala/dist_max)));
                }
                if(H[i].echipa == 2)
                {
                    winc2 = winc2 + (H[i].alive * ((H[i].shoots/bestshooter) + (H[i].distanta_totala/dist_max)));
                }
            	}
            }               // aproximez cu precizie de 3 fiecare valoare
            winc1 = round( winc1 * 1000.0 ) / 1000.0;
            winc2 = round( winc2 * 1000.0 ) / 1000.0;
            if(winc1 > winc2) // in functie de care e mai mare cresc scorul
                st1++;        // unei echipe
            else
                st2++;
        }
         void winner()           //functia winner imi creste scorul unei echipe
        {                        // la sfarsitul uinui joc
            int ok = 0, ok1 = 0;
            for(int i = 0; i < HMAX; i++)
            {
                if(H[i].nume != "null")
                {
                if(H[i].echipa == 1)
                {
                    if(H[i].alive == 0) // daca toti dintr-o ecipa sunt morti
                        ok = 1;         // atunci celalta ecipa a castigat
                    else
                    {
                        ok = 0;
                        break;
                    }
                }
                }
            }
            for(int i = 0; i < HMAX; i++)
            {
                if(H[i].nume != "null")
                {
                if(H[i].echipa == 2)
                {
                    if(H[i].alive == 0)
                        ok1 = 1;
                    else
                    {
                        ok1 = 0;
                        break;
                    }
                }
                }
            }

            if(ok == 1 || ok1 == 1)
            {
                if(ok == 1)
                    st2++;
                if(ok1 == 1)
                    st1++;
            }
        }
         void restart()         // imi restarteaza caracteristicile fiecarui
        {                       // la inceputul unui joc
            for(int i = 0; i < HMAX; i++)
            {
                if(H[i].nume != "null")
                {
                    H[i].vieti = 2;
                    H[i].alive = 1;
                    H[i].distanta_joc = 0;
                    H[i].shoot_joc = 0;
                    for(int j = 0; j < 100 ; j++)
                    {
                        H[i].pozitie[j] = -1;
                    }
                }
            }
        }
        void print_distanta()  // imi printeaza topul distantelor
        {
            int k = 0;
            struct matrix aux;
            struct matrix m[100];
            for(int i = 0; i < HMAX; i++)  // salvez intr-o matrice numele
            {                              // si distanta parcursa de un player
                if(H[i].nume != "null")
                {
                m[k].nume = H[i].nume;
                m[k].puncte = H[i].distanta_totala;
                k++;
                }
            }

            for(int i = 0 ; i < k; i++)
            {
                for(int j = 0 ; j < k; j++)
                    {
                        if(m[i].puncte > m[j].puncte)
                        {                       // ii sortez in functie de punctaj
                            aux.puncte = m[i].puncte;
                            aux.nume = m[i].nume;
                            m[i].puncte = m[j].puncte;
                            m[i].nume = m[j].nume;
                            m[j].puncte = aux.puncte;
                            m[j].nume = aux.nume;
                        }
                    }
            }
            for(int i = 0 ; i < k; i++)
            {
                for(int j = 0 ; j < k; j++)
                    {
                        if(m[i].puncte == m[j].puncte)
                        {                      //daca au punctaj egal ii sortez
                            if(m[i].nume < m[j].nume)
                            {                   // in functie de nume
                            aux.puncte = m[i].puncte;
                            aux.nume = m[i].nume;
                            m[i].puncte = m[j].puncte;
                            m[i].nume = m[j].nume;
                            m[j].puncte = aux.puncte;
                            m[j].nume = aux.nume;
                            }
                        }
                    }
            }

            if(k >= 4)   // daca nr de jucatori e mai mare de 5 atunci
            {
                for(int i = 0; i < 5 ; i++)
                {               // ii afisez pe ptrimi 5
                    cout<<i+1<<"."<<" "<<m[i].nume<<" "<<m[i].puncte<<"p"<<endl;
                }
                int limita = 5;     // dupa care atata timp cat punctajul
                while(m[4].puncte == m[limita].puncte)
                {                   //jucatorului 5 e egal cu urmatorul
                                    // il afisez
                    if(limita < k)
                        {
                            cout<<limita+1<<"."<<" "<<m[limita].nume<<" "<<m[limita].puncte<<"p"<<endl;

                        }
					limita++;
					if(limita == k)
                       	break;

                }

            }
            else            //daca numarul de jucatori e mai mic de 5 ii afisez
            {               // pe toti
                for(int i = 0; i < k ; i++)
                {
                    cout<<i+1<<"."<<" "<<m[i].nume<<" "<<m[i].puncte<<"p"<<endl;
                }
            }
        }
};
unsigned int fhash(string nume)
{               // functia hash este o simpla operatie matematica
    unsigned int hkey = 0;
    for (unsigned int i = 0; i < nume.length(); i++)
    {
        hkey = (hkey + pow(i ,3)*nume[i]);
    }
    return hkey;
}
int main()
{
    Hashtable joc(10000,fhash);
    string aux1, aux2, aux3, player;
    int n, l_e1, l_e2, value, nr_players, best_shooter;
    int puncte ,contor = 0, contor1 = 0;
    struct matrix_trageri var;
    struct matrix_trageri m_trageri[10000];
    cin>>n;                     // citesc marimea grafului de senzori
    Graph distanta(n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n ; j++)
        {
            if(i != j)
            {
                cin>>value;
                distanta.add_edge(i,j,value);  // adaug nodurile in graf
            }
        }
        distanta.add_edge(i,i,0);   // fac diag principala din graf 0
    }
    cin>>l_e1;       // citesc numarul de jucatori ai echipei 1 si a echioei 2
    cin>>l_e2;
    nr_players = l_e1 + l_e2;
    string vector_player[nr_players];
    Graph trageri(nr_players);
    for(int i = 0; i  < l_e1; i++)
    {
        cin>>player;                // citesc numele jucatorului
        vector_player[contor] = player;  // il adaug in vectorul de jucatori
        contor++;
        joc.put_player(player,1);     // il adaug in hashtable
    }
    for(int j = 0; j < l_e2; j++)
    {
        cin>>player;
        vector_player[contor] = player;
        contor++;
        joc.put_player(player,2);
    }
     cin>>aux1;
    while(aux1 != "END_CHAMPIONSHIP") //atata timp cat cuvantul citit e diferit
    {                                  // END_CHAPIONSHIP
        int jocul = aux1[0]*10000 + aux1[1]*100 + aux1[2];
        if(jocul != 747967)           // si diferit de JOC_*
        {
            if(aux1[aux1.length()-1] == 58) // verific sa vad ce operatie voi
            {                               // folosi
                int poz ;
                cin>>aux2;
                if(aux1.length() == 2)
                {
                    poz = aux1[0] - 48;
                }
                if(aux1.length() == 3)
                {
                    poz = (aux1[0] - 48)*10 + (aux1[1] - 48);
                }
                joc.pozitie(aux2,poz);  // adaug un nou senzor in vectorul
            }                           // de pozitii ai player ului aux2
            else
            {
                cin>>aux2;
                cin>>aux3;
                joc.kill(aux1, aux3);
                trageri.add_shot(joc.get_number(aux1),joc.get_number(aux3));
                            // operatia de tragere care adauga puncte pt killer
            }               // si scade o viata jucatorului victim
        }
        else
        {
            struct vect vect;
            for(int i = 0; i < nr_players;  i++)
            {
                int sum = 0;
                int lungime_vector = 0;
                vect = joc.vector_pozitii(vector_player[i]);
                while(vect.poz[lungime_vector] != -1)       //calculez valoarea
                    lungime_vector++;                   // toata a distantei
                for(int j = 0; j < lungime_vector - 1; j++) //unui player
                {
                   sum = sum + distanta.get_distanta(vect.poz[j],vect.poz[j+1]);
                }
                joc.add_distanta(vector_player[i],sum); // o adaug in campul
            }                                       //corespunzator jucatorului
            joc.winner();   // apelez winner pentru a vedea cine castiga runda
            joc.restart(); // restartez valorile pentru jucatori
        }
        cin>>aux1;
    }
     struct vect vect;
    for(int i = 0; i < nr_players;  i++) // adaug valorile care s-au modificat
    {                           // in ultima repriza care a fost intrerupta
        int sum = 0;            // pentru a putea calcula winning chance
        int lungime_vector = 0;
        vect = joc.vector_pozitii(vector_player[i]);
        while(vect.poz[lungime_vector] != -1)
            lungime_vector++;
        for(int j = 0; j < lungime_vector - 1; j++)
        {
            sum = sum + distanta.get_distanta(vect.poz[j],vect.poz[j+1]);
        }
        joc.add_distanta(vector_player[i],sum);
    }
    joc.winnig_chance();
    cout<<"I. Top shooters"<<endl;
    joc.top_shooters();   // apelez metoda to_shooters petru a afisa topul I.
    cout <<endl;
    cout<<"II. Top distance"<<endl;
   	joc.print_distanta();   // apelez print_distanta pentru a afisa
    cout<<endl;             // topul distantelor
    cout<<"III. Top fire exchange "<<endl;
    for(int i = 0; i < contor; i++)     // acum salvez intr-o matrice nume1
    {                                   // nume2 si totalul de trageri intre ei
        for(int j = i+1; j < contor ; j++)
        {       // calculez numarul de impuscaturi dintre ce doi jucatori
                m_trageri[contor1].puncte = trageri.get_value(joc.get_number(vector_player[i]),joc.get_number(vector_player[j]));
                if(vector_player[i] > vector_player[j]) // pe parcursul
                {                                       // campionatului
                    m_trageri[contor1].nume1 = vector_player[j];
                    m_trageri[contor1].nume2 = vector_player[i];
                    contor1++;
                }
                else
                {
                    m_trageri[contor1].nume1 = vector_player[i];
                    m_trageri[contor1].nume2 = vector_player[j];
                    contor1++;
                }
        }
    }
    for(int i = 0; i < contor1; i++)
    {
        for(int j = 0; j< contor1; j++)
        {
            if(m_trageri[i].puncte > m_trageri[j].puncte)  // ordonez matricea
                        {                               // in functie de puncte
                            var.puncte = m_trageri[i].puncte;
                            var.nume1 = m_trageri[i].nume1;
                            var.nume2 = m_trageri[i].nume2;
                            m_trageri[i].puncte = m_trageri[j].puncte;
                            m_trageri[i].nume1 = m_trageri[j].nume1;
                            m_trageri[i].nume2 = m_trageri[j].nume2;
                            m_trageri[j].puncte = var.puncte;
                            m_trageri[j].nume1 = var.nume1;
                            m_trageri[j].nume2 = var.nume2;
                        }
        }
    }
    if(contor1 <= 4) // daca numarul de jucatori e mai mic sau egal cu 5
    {               // ii sortez pe toti in functie de nume
    	for(int i = 0; i < contor1; i++)
    	{
        for(int j = 0; j< contor1; j++)
        {
            if(m_trageri[i].puncte == m_trageri[j].puncte)
                        {
                        	if((m_trageri[i].nume1 + m_trageri[i].nume2) < (m_trageri[j].nume1 + m_trageri[j].nume2))
                        	{
                            var.puncte = m_trageri[i].puncte;
                            var.nume1 = m_trageri[i].nume1;
                            var.nume2 = m_trageri[i].nume2;
                            m_trageri[i].puncte = m_trageri[j].puncte;
                            m_trageri[i].nume1 = m_trageri[j].nume1;
                            m_trageri[i].nume2 = m_trageri[j].nume2;
                            m_trageri[j].puncte = var.puncte;
                            m_trageri[j].nume1 = var.nume1;
                            m_trageri[j].nume2 = var.nume2;
                        	}
                        }
        }
    	}
    for(int i = 0; i < contor1 ; i++) // si ii afisez
        {
            cout<<i+1<<"."<<" "<<m_trageri[i].nume1<<" - "<<m_trageri[i].nume2<<" "<<m_trageri[i].puncte<<endl;
        }

    }
    else  // daca sunt mai multi de 5 jucatori atunci verific cati au scorul
    {int kk = 5;                // egal cu jucatorul 5
    	while(m_trageri[4].puncte == m_trageri[kk].puncte)
                {
                    kk++;
                }
      for(int i = 0; i < kk; i++) // dupa care ii sortez
    	{
        for(int j = 0; j< kk; j++)
        {
            if(m_trageri[i].puncte == m_trageri[j].puncte)
                        {
                        	if((m_trageri[i].nume1 + m_trageri[i].nume2) < (m_trageri[j].nume1 + m_trageri[j].nume2))
                        	{
                            var.puncte = m_trageri[i].puncte;
                            var.nume1 = m_trageri[i].nume1;
                            var.nume2 = m_trageri[i].nume2;
                            m_trageri[i].puncte = m_trageri[j].puncte;
                            m_trageri[i].nume1 = m_trageri[j].nume1;
                            m_trageri[i].nume2 = m_trageri[j].nume2;
                            m_trageri[j].puncte = var.puncte;
                            m_trageri[j].nume1 = var.nume1;
                            m_trageri[j].nume2 = var.nume2;
                        	}
                        }
        }}
       for(int i = 0; i < kk ; i++) // si ii afisez in ordinea descrescatoare
        {                           // a punctelor
            cout<<i+1<<"."<<" "<<m_trageri[i].nume1<<" - "<<m_trageri[i].nume2<<" "<<m_trageri[i].puncte<<endl;
        }
    }
    cout<<endl;
    cout<<"IV. Final score"<<endl;// st1 si st2 sunt 2 variabile publice
    cout<<joc.st1<<" - "<<joc.st2;// din hashtable, reprezinta scorul final
}
