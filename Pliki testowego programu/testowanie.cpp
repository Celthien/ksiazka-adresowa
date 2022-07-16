#include <iostream>
#include "testowanie.h"

using namespace std;


void Lista_uzytkownikow::otworzeniePlikuUzytkownikow()
{
    zarejestrowaniUzytkownicy.clear();
    Uzytkownik uzytkownik;
    string login, haslo, idUzytkownika;
    int id;

    fstream plik;
    plik.open("ZarejestrowaniUzytkownicy.txt", ios::in);
    if (!plik.good())
    {
        return;
    }
    else    if (plik.good())
    {
        string kolejnaLinia;
        char znak;

        while(getline(plik,kolejnaLinia))
        {
            int dlugoscSlowa = kolejnaLinia.length();
            login.clear();
            haslo.clear();
            id=0;
            idUzytkownika.clear();
            int licznikPrzerywnikowDanych=1;

            for (int i=0; i<=dlugoscSlowa; i++)
            {
                znak=kolejnaLinia[i];
                if (znak=='|')
                    licznikPrzerywnikowDanych++;
                else switch(licznikPrzerywnikowDanych)
                    {
                    case 1:
                        idUzytkownika+=znak;
                        break;
                    case 2:
                        id=atoi(idUzytkownika.c_str());
                        login+=kolejnaLinia[i];
                        break;
                    case 3:
                        haslo+=kolejnaLinia[i];
                        break;
                    }

            }

            uzytkownik.idUzytkownika=id;
            uzytkownik.login=login;
            uzytkownik.haslo=haslo;

            zarejestrowaniUzytkownicy.push_back(uzytkownik);
        }
        plik.close();

    }
    else return;
}

void Lista_uzytkownikow::rejestracjaUzytkownika()
{

    int idUzytkownika;
    int pomocniczy =0;
    string login, haslo, hasloWeryfikacyjne;
    Uzytkownik nowyUzytkownik;
    if (zarejestrowaniUzytkownicy.size()!=0)
    {
        pomocniczy = zarejestrowaniUzytkownicy.size()-1;
        idUzytkownika=zarejestrowaniUzytkownicy[pomocniczy].idUzytkownika+1;
    }

    else idUzytkownika=1;

    system("cls");
    cout <<"Rejestracja nowego uzytkownika Ksiazki Adresowej."<<endl;
    cout <<"**Jesli chcesz wrocic do menu glownego, wprowadz zero jako login.**"<<endl;
    cout <<"Podaj login, ktorym bedziesz sie logowac: ";
    cin >> login;

    if (login=="0") return;

    cout <<"Podaj haslo, ktorym sie bedziesz logowac: ";
    cin >> haslo;
    cout <<"Dla potwierdzenia wpisz haslo ponownie: ";
    cin >>hasloWeryfikacyjne;
    cout << endl;

    if (haslo!=hasloWeryfikacyjne)
    {
        cout << "Nieudana rejestracja. Sprobuj ponownie.";
        Sleep(1500);
        Lista_uzytkownikow::rejestracjaUzytkownika();
    }

    if (zarejestrowaniUzytkownicy.size()!=0)
    {

        for (int i=0; i<=zarejestrowaniUzytkownicy.size(); i++)
        {
            if (login==zarejestrowaniUzytkownicy[i].login)
            {
                cout << "Istnieje juz uzytkownik o takiej nazwie. Sprobuj ponownie."<<endl;
                Lista_uzytkownikow::rejestracjaUzytkownika();
                break;
            }
        }
    }
    nowyUzytkownik.idUzytkownika=idUzytkownika;
    nowyUzytkownik.login=login;
    nowyUzytkownik.haslo=haslo;

    zarejestrowaniUzytkownicy.push_back(nowyUzytkownik);

    fstream plik;
    plik.open("ZarejestrowaniUzytkownicy.txt", ios::out | ios::app);

    plik << idUzytkownika<<"|";
    plik << login<<"|";
    plik << haslo <<"|"<<endl;

    plik.close();


}
