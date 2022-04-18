#include<iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;
class Banca
{
public:
    Banca();
    Banca(string);
    Banca(const Banca&);
    Banca& operator=(const Banca&);
    ~Banca() = default;
    friend istream& operator>>(istream&, Banca&);
    friend ostream& operator<<(ostream&, const Banca&);
    virtual double retragere(int cod,double suma) = 0;
    virtual vector<string> facilitati() = 0;
    virtual void verificare_cont() = 0;
    virtual double credit_bancar(int,double ) = 0;



protected:
    string nume_banca;
private:


};



//constructor de initializare fara parametrii
Banca::Banca() : nume_banca("BCR") {}
Banca::Banca(string nume) : nume_banca(nume) {}
Banca::Banca(const Banca& b) {
    nume_banca = b.nume_banca;
}
Banca& Banca::operator=(const Banca& b) {
    nume_banca = b.nume_banca;
    return *this;
}
istream& operator>>(istream& i, Banca& b) {
    i >> b.nume_banca;
    return i;
}
ostream& operator<<(ostream& o, const Banca& b) {
    o <<"nume banca: "<< b.nume_banca<<'\n';
    return o;
}


class Card :
        public Banca
{
public:
    Card();
    Card(string, int, string, double, string, string);
    Card(const Card&);
    Card& operator=(const Card&);
    ~Card() = default;
    friend istream& operator>>(istream&, Card&);
    friend ostream& operator<<(ostream&, const Card&);
    double retragere(int ,double ){cout<<"Doar de pe card standard sau premium se poate extrage";return -1;}
    vector<string> facilitati(){return {};}
    void verificare_cont() {cout<<"\nTrebuie sa aveti card standard sau premium pentru a vedea.\n";}
    bool autentificare(int cod);
    double credit_bancar(int cod,double suma) {return 0;}
    static void set_incercari();
    static void modifica_incercari();

protected:
    int CVV;
    string data_expirare;
    double bani;
    string nr_card;
    string nume_detinator;
private:
    static int incercari;


};

int Card::incercari = 1;
void Card::set_incercari(){incercari = 1;}
void Card::modifica_incercari(){incercari++;}
//constructor de initializare fara parametrii
Card::Card() : nr_card("000000"), nume_detinator("Ionel Vasilescu"), data_expirare("12/02/2025"),
               CVV(000), bani(10000.5) {}
Card::Card(string banca, const int cvv, string nume, double cred, string data, string nr) : Banca(banca), CVV(cvv), nume_detinator(nume), bani(cred),
                                                                                            data_expirare(data), nr_card(nr) {}
Card::Card(const Card& card) : Banca(card) {
    CVV = card.CVV;
    nr_card = card.nr_card;
    nume_detinator = card.nume_detinator;
    data_expirare = card.data_expirare;
    bani = card.bani;

}
Card& Card::operator=(const Card& card) {
    Banca::operator=(card);
    CVV = card.CVV;
    nr_card = card.nr_card;
    nume_detinator = card.nume_detinator;
    data_expirare = card.data_expirare;
    bani = card.bani;
    return *this;
}

istream& operator>>(istream& i, Card& c) {
    i >> dynamic_cast<Banca&>(c) >> c.CVV>>c.bani >> c.data_expirare >> c.nr_card >> c.nume_detinator;
    return i;
}
ostream& operator<<(ostream& o, const Card& c) {
    o << dynamic_cast<const Banca&>(c) << "valoare bani: " << c.bani << "\ncvv: " << c.CVV << "\ndata expirare: " << c.data_expirare << "\n nr_card: "
      << c.nr_card << "\n nume detinator: " << c.nume_detinator<<'\n';
    return o;
}

//functionalitati
bool Card::autentificare(int cod) {
    if (cod == CVV) { cout<<"\nAti introdus codul corect.\n";return true; }
    else {
        if (incercari != 3) {
            cout << "\nMai incercati odata!\n";
            cin >> cod;
            modifica_incercari();
            autentificare(cod);
        } else {
            set_incercari();
            cout << "\n NU mai aveti incercari.\n";
            return false;
        }

    }
}


class Card_Standard :
        public Card
{
public:
    Card_Standard();
    Card_Standard(string banca, int cvv, string nume, double cred, string data, string nr, int limita, double comision);
    Card_Standard(const Card_Standard&);
    Card_Standard& operator=(const Card_Standard&);
    ~Card_Standard() {limita_extragere = 0;}
    friend istream& operator>>(istream&, Card_Standard&);
    friend ostream& operator<<(ostream&, const Card_Standard&);
    double retragere(int, double );
    double credit_bancar(int,double);
    void verificare_cont();
    vector<string> facilitati();
    inline double get_chashback_standard()const{return -1;}
protected:
private:
    int limita_extragere;
    double comision_depasire_limita;
};


//constructor de initializare fara parametrii
Card_Standard::Card_Standard() :limita_extragere(3000), comision_depasire_limita(0.02) {}

Card_Standard::Card_Standard(string banca, const int cvv, string nume, double cred, string data, string nr, int limita, double comision) :
        Card(banca, cvv, nume, cred, data, nr), limita_extragere(limita), comision_depasire_limita(comision) {}
Card_Standard::Card_Standard(const Card_Standard& cs) : Card(cs) {
    limita_extragere = cs.limita_extragere;
    comision_depasire_limita = cs.comision_depasire_limita;
}
Card_Standard& Card_Standard::operator=(const Card_Standard& cs) {
    Card::operator=(cs);
    limita_extragere = cs.limita_extragere;
    comision_depasire_limita = cs.comision_depasire_limita;
    return *this;

}

istream& operator>>(istream& i, Card_Standard& cs) {
    i >> dynamic_cast<Card&>(cs) >> cs.limita_extragere >> cs.comision_depasire_limita;
    return i;
}
ostream& operator<<(ostream& o, const Card_Standard& cs) {
    o << dynamic_cast<const Card&>(cs) <<"\nlimita extragere: "<<cs.limita_extragere<<"\ncomision depasire limita extragere:" << cs.comision_depasire_limita<<'\n';
    return o;
}

//functionalitati
double Card_Standard::credit_bancar(int cod, double suma) {

    if(autentificare(cod) == true) {
        if(bani>0) {
            if (suma < 10000) {
                cout << '\n';
                cout << suma << " ron imprumutati de la banca.\n";
                return suma;
            } else {
                cout << "\nSuma dorita pentru credit bancar a depasit 10000 de ron.\n";
                cout << "\nAti imprumatat doar 9999 ron.\n";

                return 9999;
            }
        }
        else
            cout<<"\nNu sunteti eligibil pentru imprumut.\n";
    }
    else
        return 0;

}
double Card_Standard::retragere(int cod,double suma) {
    if (autentificare(cod) == true) {
        if (suma < bani) {
            if (suma < limita_extragere) {
                bani -= suma;
                cout<<"\nAti retras: "<<suma<<" ron.\n";
                return suma;
            } else {
                bani -= (suma + suma * comision_depasire_limita);
                suma -= suma * comision_depasire_limita;
                cout<<"\nAti retras: "<<suma<<" ron. Deorarece s-a aplicaat comisionul de depasire de "<<comision_depasire_limita<<" din suma ceruta.\n";
                return suma;
            }
        } else {
            cout << "\nFonduri insuficiente doriti sa efectuati un credit Bancar?\n";
            string raspuns;
            cin >> raspuns;
            if (raspuns == "da") {
                double imprumut = credit_bancar(cod, suma - bani);
                if (imprumut == suma - bani) {
                    bani = 0;
                    bani -= imprumut;
                    cout << "\nAti primit banii.\n";
                    return suma;
                }
                else {
                    suma = bani+imprumut;
                    bani = 0;bani -= imprumut;
                    cout << "\nImprumut prea mare!\n";
                    return suma;}
            } else if (raspuns == "nu") {
                if(bani>0) {
                    double y = bani;
                    bani = 0;
                    cout << "Ati retras doar: " << y << " ron\n";
                    return y;
                } else {
                    cout << "\nAti retras 0 lei.\n";
                    return 0;
                }
            }

        }
        return 0;

    }
}
void Card_Standard::verificare_cont() {
    cout<<"\nIntroduceti codul:\n";
    int cod;cin>>cod;
    if(autentificare(cod) == true)
        cout<<"\nBani: "<<bani<<endl;
    else
        cout<<"\nCod gresit. Card blocat pentru 24 de ore.\n";
}

vector<string> Card_Standard::facilitati() {
    return {"\nposibilitate de imprumut\n","\nplata cu cardul\n"};
}
class Card_Premium :
        public Card_Standard
{
public:
    Card_Premium();
    Card_Premium(string banca, int cvv, string nume, double cred, string data, string nr, int limita, double comision, double, int, double);
    Card_Premium(const Card_Premium&);
    Card_Premium& operator=(const Card_Premium&);
    ~Card_Premium() = default;
    friend istream& operator>>(istream&, Card_Premium&);
    friend ostream& operator<<(ostream&, const Card_Premium&);
    double retragere(int,double);
    vector<string> facilitati();
    double credit_bancar(int cod,double suma);
    void verificare_cont();
    inline double get_cashback_premium()const{return cashback;}
private:
    double cashback;
    int limita_extragere_premium;
    double comision_depasire_premium;
};


Card_Premium::Card_Premium() :cashback(0.005), limita_extragere_premium(6000), comision_depasire_premium(0.1) {}
Card_Premium::Card_Premium(string banca, const int cvv, string nume, double cred, string data, string nr, int limita, double comision, double cash, int limp, double comp) :
        Card_Standard(banca, cvv, nume, cred, data, nr, limita, comision), cashback(cash), limita_extragere_premium(limp), comision_depasire_premium(comp) {}
Card_Premium::Card_Premium(const Card_Premium& cp) : Card_Standard(cp) {
    cashback = cp.cashback;
    limita_extragere_premium = cp.limita_extragere_premium;
    comision_depasire_premium = cp.comision_depasire_premium;
}

Card_Premium& Card_Premium::operator=(const Card_Premium& cp) {
    Card_Standard::operator=(cp);
    cashback = cp.cashback;
    limita_extragere_premium = cp.limita_extragere_premium;
    comision_depasire_premium = cp.comision_depasire_premium;
    return *this;
}

istream& operator>>(istream& i, Card_Premium& cp) {
    i >> dynamic_cast<Card_Standard&>(cp) >> cp.cashback >> cp.limita_extragere_premium >> cp.comision_depasire_premium;
    return i;
}
ostream& operator<<(ostream& o, const Card_Premium& cp) {
    o << dynamic_cast<const Card&>(cp) <<"cashback: "<< cp.cashback <<"\nlimita extragere card premium: "<< cp.limita_extragere_premium<<
      "\ncomision depasire card premium: "<< cp.comision_depasire_premium<<'\n';
    return o;
}
//functionalitati
double Card_Premium::credit_bancar(int cod,double suma){


    if(autentificare(cod) == true) {
        if (suma < 40000) {
            cout<<'\n';
            cout<<suma<<" ron imprumutati de la banca.\n";
            return suma;
        } else
        {
            cout<<"\nSuma dorita pentru credit bancar a depasit 40000 de ron.\n";
            cout<<"\nAti imprumatat doar 39999 ron.\n";

            return 39999;}
    }
    else
        return 0;


}
void Card_Premium::verificare_cont() {
    cout<<"--------------";
    cout<<"\n    PREMIUM\n";
    cout<<"---------------";
    cout<<"\nIntroduceti codul:\n";
    int cod;cin>>cod;
    if(autentificare(cod) == true)
        cout<<"\nBani: "<<bani<<endl;
    else
        cout<<"\nCod gresit. Card blocat pentru 24 de ore.\n";
}

double Card_Premium::retragere(int cod,double suma){
    if(autentificare(cod) == true) {
        if(suma<bani) {
            if (suma < limita_extragere_premium) {
                cout << "\nAti retras " << suma << " ron.\n";
                cout<<"\nvaloare cashback: "<<(suma*cashback)<<" ron.\n"<<endl;
                return (suma+ (suma*cashback/100));
            } else {
                cout << "\nAti depasit limita de extragere.\n";
                bani -= (suma + suma * comision_depasire_premium);
                cout<<"\nAti retras: "<<((suma - suma * comision_depasire_premium  ) + (suma - suma * comision_depasire_premium  )*cashback)<<" ron.\n";
                return ((suma - suma * comision_depasire_premium  ) + (suma - suma * comision_depasire_premium  )*cashback);
            }
        }
        else
        {
            cout<<"\nDoriti sa efectuati un credit bancar?\n";
            string raspuns;
            cin>>raspuns;
            if(raspuns == "da") {
                double imprumut = credit_bancar(cod, suma - bani);
                if (imprumut == suma - bani)
                {
                    bani = 0;
                    bani -= imprumut;
                    cout<<"\nAti primit banii";
                    cout<<"\nAti primit cashbach: "<<suma*cashback<<" ron.\n";
                    return (suma+ suma*cashback);
                }
                else {
                    suma = bani + 39999;
                    bani = 0;bani -= imprumut;
                    cout << "\nImprumut prea mare!\n";
                    cout<<"\nAti primit cashbach: "<<suma*cashback<<" ron.\n";
                    return (suma+ suma*cashback);}
            } else if (raspuns == "nu") {
                if(bani>0)
                { double y = bani;
                    bani = 0;
                    cout<<"\nAti retras doar:"<<(y+y*cashback)<<" ron\n";
                    return (y+y*cashback);}
                else {
                    cout << "\nAti retras 0 lei.\n";
                    return 0;
                }
            }}

    }
    return 0;

}
vector<string> Card_Premium::facilitati() {
    return {"\ncashback generos la retragere\n","\nsuma de imprumut mai mare\n","\nlimita mai mare de extragere\n","\ncomision de depasire a limitei de extragere mai mic\n","\nplus toate avantajele cardului standard\n"};
}


int main()
{


    int comanda;bool meniu = true;
    while (meniu) {
        citire_comanda:
        cout << "Apasati 0 pentru a iesi din program.\n";
        cout << "Apasati 1 pentru a va crea cardul standard.\n";
        cout<<"Apasati 2 pentru constructori si operatori.\n";
        cout << "Apasati 3 pentru crea o colectie de carduri.\n";




        cin >> comanda;
        try {
            if (comanda > 4)
                throw comanda;
        }
        catch (...) {
            cout << "Comanda invalida.\n";
            goto citire_comanda;
        }
        if (comanda == 0)
            meniu = false;
        else if (comanda == 1) {
            cout<< "Cititi proprietatiile cardului standard: banca(string),cvv(int),(double) banii din card, (string) data expirarii, (string) nr cardului, (string) nume detinator,(int) limita extragere, (double) comision depasire limita\n";
            Card_Standard csc;
            cin >> csc;
            Card_Standard *cs = &csc;
            crds_sub:
            cout << "Apasati 0 pentru a nu mai folosi cardul standard\n";
            cout << "Apasati 1 pentru a face o retragere.\n";
            cout << "Apasati 2 pentru a face un credit bancar.\n";
            cout << "Apasati 3 pentru a vedea cat bani aveti pe card.\n";
            cout << "Apasati 4 pentru a face upgrade la card premium.\n";
            cout << "Apasati 5 pentru a vedea facilitatiile.\n";
            cout << "Apasati 6 pentru a mai da comenzi.\n";
            int subcomanda_css;
            int cod;
            double suma;
            cin >> subcomanda_css;
            try {
                if (subcomanda_css > 6)
                    throw subcomanda_css;

            }
            catch (...) {
                cout << "subcomanda pentru card standard invalida.\n";
                goto crds_sub;

            }
            if (subcomanda_css == 0)
                goto citire_comanda;
            else if (subcomanda_css == 1) {
                cout << "Introduceti codul de deblocare a cardului si suma pe care vreti sa o retrageti.\n";
                cin >> cod >> suma;
                cs->retragere(cod, suma);
                goto crds_sub;
            } else if (subcomanda_css == 2) {
                cout << "Introduceti codul de deblocare a cardului si suma pe care vreti sa o imprumutati.\n";
                cin >> cod >> suma;
                cs->credit_bancar(cod, suma);
                goto crds_sub;
            } else if (subcomanda_css == 3) {
                cs->verificare_cont();
                goto crds_sub;
            } else if (subcomanda_css == 4) {

                ///upcasting
                cs = new Card_Premium;
                cout << "Acum explorati noile facilitati ale cardului premium. Codul de deblocare este 0.\n";
                vector<string> vp = cs->facilitati();
                for (long long i = 0; i < vp.size(); i++)
                    cout << vp[i];
                csp_et:
                cout << "Apasati 0 pentru a nu mai folosi cardul premium\n";
                cout << "Apasati 1 pentru a face o retragere.\n";
                cout << "Apasati 2 pentru a face un credit bancar.\n";
                cout << "Apasati 3 pentru a vedea cat bani aveti pe card.\n";
                cout << "Apasati 4 pentru a face downgrade la card standard.\n";
                cout << "Apasati 5 pentru a mai da comenzi.\n";

                int csp_sub;
                cin >> csp_sub;
                try {
                    if (csp_sub > 5)
                        throw csp_sub;
                }
                catch (...) {
                    cout << "comanda invalida.\n";
                    goto csp_et;
                }
                switch (csp_sub) {
                    case 0:
                        goto citire_comanda;
                        break;
                    case 1: {
                        cout << "Introduceti codul de deblocare a cardului si suma pe care vreti sa o retrageti.\n";
                        cin >> cod >> suma;
                        cs->retragere(cod, suma);
                        goto csp_et;
                        break;
                    }
                    case 2: {
                        cout << "Introduceti codul de deblocare a cardului si suma pe care vreti sa o imprumutati.\n";
                        cin >> cod >> suma;
                        cs->credit_bancar(cod, suma);
                        goto csp_et;
                        break;
                    }
                    case 3: {
                        cs->verificare_cont();
                        goto csp_et;
                        break;
                    }
                    case 4:
                    {
                        cout<<"\nAti facut downgrade la cardul standard. Codul de deblocare este tot 0.\n";
                        cs = new Card_Standard;
                        cs = dynamic_cast<Card_Standard*>(cs);
                        cs->verificare_cont();
                        goto crds_sub;
                        break;

                    }
                }
            } else if (subcomanda_css == 5) {
                vector<string> v = cs->facilitati();
                for (long long i = 0; i < v.size(); i++)
                    cout << v[i];
                goto crds_sub;
                break;
            } else if (subcomanda_css == 6) {
                goto crds_sub;
            }


            break;
        }
        else if(comanda == 2){
            constructori:
            cout<<"Apasati 0 pentru a iesi.\n";
            cout<<"Apasati 1 pentru clasa Card.\n";
            cout<<"Apasati 2 pentru clasa Card Standard.\n";
            cout<<"Apasati 3 pentru clasa Card Premium.\n";
            short cons_sub;
            cin>>cons_sub;
            switch (cons_sub) {
                case 0: {
                    goto citire_comanda;
                    break;
                }
                case 1:
                {
                    cout<<"\nconstructor fara parametrii si operatorul <<.\n";
                    Card co;
                    cout<<co;
                    cout<<"\nconstructor cu paramentrii.\n";
                    Card co1("BRD",100,"Ionescu Vasile",12000.25,"12/26","023222922");
                    cout<<co1;
                    cout<<"\nconstructor de copiere si operator de atribuire.\n";
                    Card co2(co1);
                    cout<<"\nco2:\n"<<co2;
                    co = co1;
                    cout<<"\nco2:\n"<<co;
                    cout<<"\noperatorul >> si <<";
                    cout<< "Cititi proprietatiile cardului standard: banca(string),cvv(int),(double) banii din card, (string) data expirarii, (string) nr cardului, (string) nume detinator.\n";
                    cin>>co;
                    cout<<co;
                    goto constructori;
                    break;
                }
                case 2:
                {
                    cout<<"\nconstructor fara parametrii si operatorul <<.\n";
                    Card_Standard cso;
                    cout<<cso;
                    cout<<"\nconstructor cu paramentrii.\n";
                    Card_Standard cso1("BRD",100,"Ionescu Vasile",12000.25,"12/26","023222922",2000,0.03);
                    cout<<cso1;
                    cout<<"\nconstructor de copiere si operator de atribuire.\n";
                    Card_Standard cso2(cso1);
                    cout<<"\ncso2:\n"<<cso2;
                    cso = cso1;
                    cout<<"\ncso2:\n"<<cso;
                    cout<<"\noperatorul >> si <<";
                    cout<< "Cititi proprietatiile cardului standard: banca(string),cvv(int),(double) banii din card, (string) data expirarii, (string) nr cardului, (string) nume detinator,(int) limita extragere, (double) comision depasire limita\n";
                    cin>>cso;
                    cout<<cso;
                    goto constructori;
                    break;

                }
                case 3:
                {
                    cout<<"\nconstructor fara parametrii si operatorul <<.\n";
                    Card_Premium cpo;
                    cout<<cpo;
                    cout<<"\nconstructor cu paramentrii.\n";
                    Card_Premium cpo1("BRD",100,"Ionescu Vasile",12000.25,"12/26","023222922",2000,0.03,0.005,5500,0.01);
                    cout<<cpo1;
                    cout<<"\nconstructor de copiere si operator de atribuire.\n";
                    Card_Premium cpo2(cpo1);
                    cout<<"\ncpo2:\n"<<cpo2;
                    cpo = cpo1;
                    cout<<"\ncpo2:\n"<<cpo;
                    cout<<"\noperatorul >> si <<";
                    cout<< "Cititi proprietatiile cardului standard: banca(string),cvv(int),(double) banii din card, (string) data expirarii, (string) nr cardului, (string) nume detinator, (double) cashback, (int) limita extragere premium, (double) comision depasire limita premium\n";
                    cin>>cpo;
                    cout<<cpo;
                    goto constructori;
                    break;

                }



            }
        }
        else if (comanda == 3) {
            long long n;
            cout << "Introduceti numarul de carduri:\n";
            cin >> n;
            try {
                if (n < 1) throw runtime_error("Vectorul nu poate avea un mai mic de 1 de elemente!");
            }
            catch (...) {
                cout << "Ati introdus un numar invalid de elemente ale vectorului.";
                return 0;
            }
            Card *carduri[n + 1];
            for (long long i = 0; i < n; i++)
                if (i % 2)
                    carduri[i] = new Card_Standard;
                else
                    carduri[i] = new Card_Premium;
            int count = 1;
            for (long long i = 0; i < n; i++) {
                cout<<"\nCardul: "<<count<<endl;
                if (Card_Premium *cpp = dynamic_cast<Card_Premium *>(carduri[i])) {
                    cout<<"\n-----------------------------------------------";
                    cout<<"Cardul: "<<count<<'\n';
                    cout<<"\nVerifica contul codul este 0:\n";
                    if (cpp->get_cashback_premium() != -1) {
                        cpp->verificare_cont();
                        cout << "\nCardul dvs. are cashback: " << cpp->get_cashback_premium() << '\n';
                    }
                } else if (Card_Standard *csp = dynamic_cast<Card_Standard *>(carduri[i])) {
                    if (csp->get_chashback_standard() == -1) {
                        csp->verificare_cont();
                        cout << "\nCardul standard nu are optiunea de cashback.\n";
                    }                }count++;
                cout<<"---------------------------------------------------\n";
            }
            for(long long i = 0;i<n;i++)
                delete carduri[i];
        }
    }



    return 0;
}

