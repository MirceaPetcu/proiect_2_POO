# proiect_2_POO
134 Petcu Mircea
  Clasa Card si clasa Banca au variabile protected deoarece am nevoie de variabile pentru obiectele de tip Card_Standard si Card_Premium. Clasa Banca este o clasa 
abstracta unde am declarat functiile virtual pure iar clasa Card am pastrat-o "neabstracta" pentru ca am nevoie de ea cand imi declar vectorul de carduri (colectia de
carduri de la subpunctul 3 din meniul principal) pentru a face upcasting si downcasting la clasele card standard si card premium.
  Ca variabila statica o am pe cea de tip int incercari si ca functii statice am functia set_incercari() ce imi seteaza variabila incercari la 1 si modifica_incercari()
ce imi ce imi incrementeaza variabila incercari cu 1. Toate acestea le utilizez in functia de autentificare ce apartine de clasa card si este mostenita de clasele copii
ale acesteia. Functia autentificare primeste ca parametru(CVV-ul cardului, un fel de PIN) si verifica daca se potriveste cu data membru CVV. Daca da returnez true si 
afisez un mesaj, daca nu, si aici voi folosi variabila statica mai mult ca o variabila globala dar si functiile statice, ai voie maxim 3 incercati de introducere a codului
cu tot cu cea primita ca parametru. Cu fiecare incercare gresita incrementez incercarile cu functia modifica si reapelez functia de autentificare. Daca se ajunge la 3 
incercari ii dau valoarea 1 variabilei incercari si returnez false.
  Ca functii virtuale pure am 4 functii: retragere(), facilitati(), credit_bancar si verificare_cont(). Functiile ce apartin de clasa Card,in afara de cea de autentificare,
sunt mai mult functii fictive, ele neavand un rol important in scopul programului. Le-am definit pentru a nu deveni clasa Card o clasa abstracta. 
  Functia de retragere ce apartine de clasa Card_Standard, si in general mai toate functiile de la toate clasele in afara de facilitati, verifica intai daca ai reusit sa
te autentifici cu codul corect. Daca te-ai autentificat verifica daca suma dorita pentru a fi retrasa de pe card nu depaseste banii din cont si limita de extragere.
Daca nu a depasit returneaza suma asa cum utilizatorul a cerut-o. Daca a depasit limita de extragere se aplica comisionul. Daca a suma ceruta a depasit suma din cont se
intreaba utilizatorul daca doreste sa efectueza un credit bancar(se raspunde simplu prin "da"/"nu"). Daca raspunsul este "da" atunci se apeleaza functia de credit_bancar
asignata clasei Card_Standard. Functia credit_bancar ia ca parametri codul de autentificare a cardului si suma dorita pentru a fi imprumutata. Pentru cardul standard daca
nu se afla bani in cont nu se poate efectua un imprumut. Daca in schimb exista se ofera un imprumut nu mai mare de 10000 de ron sau 9999 ron daca suma dorita este mai mare.
Daca raspunsul este "nu" se ofera toti banii din cont daca mai exista bani in cont. Functia de vericare_cont() afiseaza pe ecran cati bani sunt in cont, nu inainte de a 
se autentifica cu codul(CVV din clasa). Functia facilitati este mai mult o functie publicitara si scrie pe ecran ce se poate face cu cardul standard.
  Functiile Cardului Premium au aceasi denumire ca cele de la card standard doar ca aduc unele benificii in plus. Majoritatea acestor beneficii sunt descrise in functia
de facilitati. Inafara de functia de facilitati toate solicita autentificare inainte. Functia de retragere este apoximativ aceasi ca cea de la clasa parinte(Card_Standard)
doar ca primesti si un cashback la retragere(data membra in clasa). La fel ca cea anterioara cand nu sunt destui bani in cont pentru a retrage suma ceruta, se intreaba 
utilizatorul daca doreste sa faca un credit bancar. Daca "da" se apeleaza functia de credit_bancar ce apartine de clasa card premium, aceasta are ca parametri tot un cod
si o suma de imprumutat. Odata autentificat, se verifica daca imprumutul nu este mai mare de 40000 de ron (fata de 10000 fata de cel standard) si spre deosebire de functia
de card standard nu mai este nevoie sa ai bani in cont. Daca suma depaseste 40000 de ron se ofera 39999 ron. Functia de autentificare se aseamana foarte mult cu cea de 
card standard doar ca scrie frumos, cu majuscule PREMIUM sus:).
  Mai exista si functiile get_cashback_premium(returneaza cashbackul) si standard_cashback_standard(returneaza -1) ce ne ajuta la casting din vectorul de carduri de la 
subpunctul 3 din meniul principal. Pentru supraincarcarea operatorului de citire am facut casting. Pentru card premium nu este nevoie sa cititi si datele clasei de card
standard.
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Exemplu citire Card_Standard:
Raiffeisen<br />
805<br />
12000.4<br />
05/25<br />
03472823<br />
ionesculescu<br />
3500<br />
0.04<br />
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Exemplu citire Card:
Raiffeisen<br />
805<br />
12000.4<br />
05/25<br />
03472823<br />
ionesculescu<br />
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Exemplu citire Card_Premium:
Raiffeisen<br />
805<br />
20000.4<br />
05/25<br />
03472823<br />
ionesculescu<br />
0.01<br />
8000<br />
0.02<br />
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  Programul a fost scris in Clion si se poate rula si in terminal.
