#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>


using namespace std;

class Uzytkownik
{
public:
    string login;
    string haslo;

    int idUzytkownika;
};

class Lista_uzytkownikow : public Uzytkownik
{
public:
    //dziedziczy Uzytkownikow i tworzy wektor z nich
    vector <Uzytkownik> zarejestrowaniUzytkownicy;


    void otworzeniePlikuUzytkownikow ();
    int logowanieUzytkownika (vector <Uzytkownik> &zarejestrowaniUzytkownicy);
    void rejestracjaUzytkownika ();
    void zmianaHasla (vector <Uzytkownik> &zarejestrowaniUzytkownicy, int idUzytkownika);
    void zapisaniePlikuUzytkownicy (vector <Uzytkownik> &zarejestrowaniUzytkownicy);
};
