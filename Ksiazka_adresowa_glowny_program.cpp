#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct ksiazka_adresowa
{
    int pozycjaWpisu;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string telefon;
    string email;
    string adres;
};

struct lista_uzytkownikow
{
    int idUzytkownika;
    string login;
    string haslo;
};


void otworzeniePlikuUzytkonikow (vector <lista_uzytkownikow> &zarejestrowaniUzytkownicy);
int logowanieUzytkownika (vector <lista_uzytkownikow> &listaUzytkownikow);
void rejestracjaUzytkownika (vector <lista_uzytkownikow> &zarejestrowaniUzytkownicy);
void zmianaHasla (vector <lista_uzytkownikow> &zarejestrowaniUzytkownicy, int idUzytkownika);
void zapisaniePlikuUzytkownicy (vector <lista_uzytkownikow> &zarejestrowaniUzytkownicy);

int dodaniePozycji (vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int liczbaPozycjiWKsiazce, int idUzytkownika);
void wypisanieDanejPozycji (vector <ksiazka_adresowa> WpisWKsiazceAdresowej, int liczbaPozycjiWKsiazce);
void wyszukiwanieOsobyWKsiazce (vector <ksiazka_adresowa> WpisWKsiazceAdresowej, int liczbaPozycjiWKsiazce, int idUzytkownika);
int usuniecieWpisu (vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int idUzytkownika);
int otworzeniePlikuAdresatow(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int idUzytkownika);
void wyswietlenieWszystkichOsob(vector <ksiazka_adresowa> WpisWKsiazceAdresowej, int idUzytkownika);
void edycjaWybranejPozycji(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int liczbaPozycjiWKsiazce, int idUzytkownika);
void zapisaniePlikuTymczasowego(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int liczbaPozycji);
void zapisaniePlikuWlasciwego(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej);
int liczenieLiniiWPliku(int usuwanaLinia);
int pobranieIDAdresata(string pobieranaLiniaZPliku);
void zapisaniePozycjiDoPlikuTymczasowego(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int pozycjaWKsiazce);
void usunieciePozycjiZPliku(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int usuwanaLinia);
void zamianaPlikuTymczasowegoNaWlasciwy();

int main()
{
    vector <ksiazka_adresowa> WpisWKsiazceAdresowej;
    vector <lista_uzytkownikow> zarejestrowaniUzytkownicy;
    char wybraneZadanie;
    int liczbaPozycjiWKsiazce=0, licznikPomocniczy=0;
    otworzeniePlikuUzytkonikow(zarejestrowaniUzytkownicy);
    int ktoZalogowany = 0;

    while (true)
    {
poczatek:
        system("cls");

        cout << "Twoja ksiazka adresowa. " << endl;
        cout << "Aby wyswietlic dane, konieczne jest zalogowanie sie. " << endl;
        cout << "Zaloguj sie badz zarejestruj. " << endl<<endl;

        cout << "Wybierz opcje: " << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl<<endl;
        cout << "Podaj numer opcji: ";
        cin >> wybraneZadanie;

        if (wybraneZadanie=='1')
        {
            if (zarejestrowaniUzytkownicy.size()==0)
            {
                cout << "Brak zarejestrowanych uzytkownikow. Zarejestruj sie przed zalogowaniem."<<endl<<endl;
                system("pause");
                goto poczatek;
            }
            else ktoZalogowany=logowanieUzytkownika(zarejestrowaniUzytkownicy);
            if (ktoZalogowany==0) goto poczatek;
            else goto ksiazka;
        }
        else if (wybraneZadanie=='2')
        {
            rejestracjaUzytkownika(zarejestrowaniUzytkownicy);
            goto poczatek;
        }
        else if (wybraneZadanie=='3')
        {
            zapisaniePlikuWlasciwego(WpisWKsiazceAdresowej);
            exit(0);
        }
    }


ksiazka:

    WpisWKsiazceAdresowej.clear();
    liczbaPozycjiWKsiazce=otworzeniePlikuAdresatow(WpisWKsiazceAdresowej, ktoZalogowany);
    licznikPomocniczy=WpisWKsiazceAdresowej.size();


    while (true)
    {
        system("cls");

        cout << "Ksiazka adresowa. Wybierz zadanie: " << endl<<endl;
        cout << "1. Nowy wpis." << endl;
        cout << "2. Znajdz osobe." << endl;
        cout << "3. Wyswietl wszystkich." << endl;
        cout << "4. Edycja wybranej pozycji." << endl;
        cout << "5. Usuniecie wybranej pozycji" << endl;
        cout << "6. Zmien haslo" << endl;
        cout << "7. Wyloguj sie" << endl;
        cout << "8. Zapisz i zakoncz" << endl<<endl;
        cout << "Podaj numer opcji: ";
        cin >> wybraneZadanie;

        if (wybraneZadanie=='1')
        {
            liczbaPozycjiWKsiazce=dodaniePozycji(WpisWKsiazceAdresowej, liczbaPozycjiWKsiazce, ktoZalogowany);
        }
        else if (wybraneZadanie=='2')
        {
            wyszukiwanieOsobyWKsiazce(WpisWKsiazceAdresowej,liczbaPozycjiWKsiazce,ktoZalogowany);
        }
        else if (wybraneZadanie=='3')
        {
            wyswietlenieWszystkichOsob(WpisWKsiazceAdresowej,ktoZalogowany);
        }
        else if (wybraneZadanie=='4')
        {
            edycjaWybranejPozycji(WpisWKsiazceAdresowej,WpisWKsiazceAdresowej.size(),ktoZalogowany);
            zapisaniePlikuTymczasowego(WpisWKsiazceAdresowej, WpisWKsiazceAdresowej.size());
        }
        else if (wybraneZadanie=='5')
        {
            liczbaPozycjiWKsiazce=usuniecieWpisu(WpisWKsiazceAdresowej,ktoZalogowany);
        }
        else if (wybraneZadanie=='6')
        {
            zmianaHasla(zarejestrowaniUzytkownicy, ktoZalogowany);
        }
        if (wybraneZadanie=='7')
        {
            goto poczatek;
        }
        else if (wybraneZadanie=='8')
        {
            zapisaniePlikuWlasciwego(WpisWKsiazceAdresowej);
            exit(0);
        }
    }
    return 0;
}

void otworzeniePlikuUzytkonikow (vector <lista_uzytkownikow> &zarejestrowaniUzytkownicy)
{
    zarejestrowaniUzytkownicy.clear();
    string login, haslo, idUzytkownika;
    int id;
    lista_uzytkownikow Uzytkownik;
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

            Uzytkownik.idUzytkownika=id;
            Uzytkownik.login=login;
            Uzytkownik.haslo=haslo;

            zarejestrowaniUzytkownicy.push_back(Uzytkownik);
        }
        plik.close();

    }
    else return;
}

int logowanieUzytkownika (vector <lista_uzytkownikow> &zarejestrowaniUzytkownicy)
{
    int ktoZalogowany;
    string login, haslo, weryfikacjaHasla;
    int pomocniczy = zarejestrowaniUzytkownicy.size();

    system("cls");
    cout <<"Podaj login i haslo, by sie zalogowac."<<endl;
    cout <<"**Zeby wrocic do menu glownego, wprowadz zero.**"<<endl<<endl;
    cout <<"Login: ";
    cin >> login;

    if (login=="0") return 0;

    for (int i=0; i<= pomocniczy; i++)
    {
        if (login==zarejestrowaniUzytkownicy[i].login)
        {
            weryfikacjaHasla=zarejestrowaniUzytkownicy[i].haslo;
            ktoZalogowany=zarejestrowaniUzytkownicy[i].idUzytkownika;
            break;
        }
        if (i==pomocniczy)
        {
            cout <<endl<< "Brak uzytkownika o tej nazwie. Sprobuj ponownie. "<<endl;
            system("pause");
            logowanieUzytkownika(zarejestrowaniUzytkownicy);
        }
    }

    cout <<"Haslo: ";
    cin >> haslo;

    if (haslo==weryfikacjaHasla)
    {

        cout << "Poprawne zalogowanie.";
        Sleep(1500);
        return ktoZalogowany;
    }
    else
    {
        cout << "Nieudane logowanie. Ponownie wprowadz haslo: ";;
        cin >> haslo;
        if (haslo==weryfikacjaHasla)
        {
            cout << "Poprawne zalogowanie.";
            Sleep(1500);
            return ktoZalogowany;
        }
        else cout << "Nieudana druga proba. Sprobuj ponownie";
        logowanieUzytkownika(zarejestrowaniUzytkownicy);
    }
}

void rejestracjaUzytkownika (vector <lista_uzytkownikow> &zarejestrowaniUzytkownicy)
{
    int idUzytkownika;
    int pomocniczy =0;
    string login, haslo, hasloWeryfikacyjne;
    lista_uzytkownikow nowyUzytkownik;
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
        rejestracjaUzytkownika(zarejestrowaniUzytkownicy);
    }

    if (zarejestrowaniUzytkownicy.size()!=0)
    {

        for (int i=0; i<=zarejestrowaniUzytkownicy.size(); i++)
        {
            if (login==zarejestrowaniUzytkownicy[i].login)
            {
                cout << "Istnieje juz uzytkownik o takiej nazwie. Sprobuj ponownie."<<endl;
                rejestracjaUzytkownika(zarejestrowaniUzytkownicy);
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

void zmianaHasla (vector <lista_uzytkownikow> &zarejestrowaniUzytkownicy, int idUzytkownika)
{
    string haslo, nowehaslo, weryfikacjaHasla;
    system("cls");
    cout << "Zmiana hasla." << endl;
    cout << "**Jesli chcesz wrocic do menu glownego, wpisz zero.**"<<endl;
    cout << "Potwierdz stare haslo, by moc ustawic nowe: ";
    cin >> haslo;

    if (haslo=="0") return;

    if (haslo==zarejestrowaniUzytkownicy[idUzytkownika-1].haslo)
    {
        cout << "Podaj nowe haslo: ";
        cin >> nowehaslo;
        cout << "Dla potwierdzenia wpisz nowe haslo ponownie: ";
        cin >> weryfikacjaHasla;

        if (nowehaslo!=weryfikacjaHasla)
        {
            cout << "Hasla sie nie zgadzaja, sprobuj ponownie.";
            Sleep(1500);
            zmianaHasla(zarejestrowaniUzytkownicy, idUzytkownika);
        }
        else cout << "Zamiana hasla przebiegla pomyslnie.";
        Sleep(1500);
        zarejestrowaniUzytkownicy[idUzytkownika-1].haslo=nowehaslo;
        zapisaniePlikuUzytkownicy(zarejestrowaniUzytkownicy);
        otworzeniePlikuUzytkonikow(zarejestrowaniUzytkownicy);
        return;
    }
    else cout << "Niepoprawne haslo. Sprobuj ponownie.";
    zmianaHasla(zarejestrowaniUzytkownicy, idUzytkownika);


}

void zapisaniePlikuUzytkownicy (vector <lista_uzytkownikow> &zarejestrowaniUzytkownicy)
{
    int liczbaPozycji = zarejestrowaniUzytkownicy.size();

    fstream plik;
    plik.open("ZarejestrowaniUzytkownicy.txt", ios::out | ios::trunc);

    for (int i=0; i<liczbaPozycji; i++)
    {
        plik << zarejestrowaniUzytkownicy[i].idUzytkownika<<"|";
        plik << zarejestrowaniUzytkownicy[i].login<<"|";
        plik << zarejestrowaniUzytkownicy[i].haslo <<"|"<<endl;
    }
    plik.close();
}

//funkcje ksiazki

int dodaniePozycji (vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int liczbaPozycjiWKsiazce, int idUzytkownika)
{
    string imie;
    string nazwisko;
    string telefon;
    string email;
    string adres;
    ksiazka_adresowa Adresat;


    system("cls");
    cout << "Podaj imie: "<<endl;
    cin.sync();
    getline(cin, imie);
    cout << "Podaj nazwisko: "<<endl;
    cin.sync();
    getline(cin, nazwisko);
    cout << "Podaj telefon: "<<endl;
    cin.sync();
    getline(cin, telefon);
    cout << "Podaj email: "<<endl;
    cin >> email;
    cout << "Podaj adres: "<<endl;
    cin.sync();
    getline(cin, adres);

    Adresat.pozycjaWpisu=liczbaPozycjiWKsiazce+1;
    Adresat.idUzytkownika=idUzytkownika;
    Adresat.imie=imie;
    Adresat.nazwisko=nazwisko;
    Adresat.telefon=telefon;
    Adresat.email=email;
    Adresat.adres=adres;

    WpisWKsiazceAdresowej.push_back(Adresat);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    plik << liczbaPozycjiWKsiazce+1<<"|";
    plik << idUzytkownika<<"|";
    plik << imie<<"|";
    plik << nazwisko <<"|";
    plik << telefon <<"|";
    plik << email <<"|";
    plik << adres <<"|"<<endl;

    plik.close();

    liczbaPozycjiWKsiazce++;

    cout << "Dziekuje, adresat zostal zapisany.";
    Sleep(1500);
    return liczbaPozycjiWKsiazce;
}

void wypisanieDanejPozycji (vector <ksiazka_adresowa> WpisWKsiazceAdresowej, int liczbaPozycjiWKsiazce)
{
    cout << "Numer pozycji w ksiazce adresowej: "<<WpisWKsiazceAdresowej[liczbaPozycjiWKsiazce].pozycjaWpisu<<endl;
    cout <<"Imie i nazwisko: " <<WpisWKsiazceAdresowej[liczbaPozycjiWKsiazce].imie<<" "<< WpisWKsiazceAdresowej[liczbaPozycjiWKsiazce].nazwisko<<endl;
    cout << "Telefon: "<<WpisWKsiazceAdresowej[liczbaPozycjiWKsiazce].telefon<<endl;
    cout << "Email: "<<WpisWKsiazceAdresowej[liczbaPozycjiWKsiazce].email<<endl;
    cout << "Adres: "<<WpisWKsiazceAdresowej[liczbaPozycjiWKsiazce].adres<<endl<<endl;
    Sleep(1000);
}

void wyszukiwanieOsobyWKsiazce (vector <ksiazka_adresowa> WpisWKsiazceAdresowej, int liczbaPozycjiWKsiazce, int idUzytkownika)
{

    char wyborSzukaniePozycji;
    int weryfikacjaPetliWyszukania=liczbaPozycjiWKsiazce;
    string podaneDaneSzukanie;

    system("cls");

    cout << "Wybierz dane do wyszukania:"<<endl;
    cout << "1. Szukaj po imieniu."<<endl;
    cout << "2. Szukaj po nazwisku."<<endl;
    cout << "3. Szukaj po numerze telefonu."<<endl;
    cout << "4. Szukaj po adresie email."<<endl;
    cout << "5. Powrot."<<endl;

    cout << "Podaj numer opcji: ";
    cin >> wyborSzukaniePozycji;

    if (wyborSzukaniePozycji=='1')
    {
        cout << "Podaj imie: "<<endl;
        cin.sync();
        getline(cin, podaneDaneSzukanie);

        for (int i=0; i<=liczbaPozycjiWKsiazce; i++)
        {
            if ((WpisWKsiazceAdresowej[i].imie==podaneDaneSzukanie)&&(WpisWKsiazceAdresowej[i].idUzytkownika==idUzytkownika))
            {
                wypisanieDanejPozycji(WpisWKsiazceAdresowej,i);
                weryfikacjaPetliWyszukania++;
            }
        }
        if (weryfikacjaPetliWyszukania==liczbaPozycjiWKsiazce)
            cout << "Brak takiej osoby. Mozesz wprowadzic ja w menu glownym, opcja 1."<<endl;
        system("pause");
    }
    if (wyborSzukaniePozycji=='2')
    {
        cout << "Podaj nazwisko: "<<endl;
        cin >> podaneDaneSzukanie;

        for (int i=0; i<=liczbaPozycjiWKsiazce; i++)
        {
            if ((WpisWKsiazceAdresowej[i].nazwisko==podaneDaneSzukanie)&&(WpisWKsiazceAdresowej[i].idUzytkownika==idUzytkownika))
            {
                wypisanieDanejPozycji(WpisWKsiazceAdresowej,i);
                weryfikacjaPetliWyszukania++;
            }
        }
        if (weryfikacjaPetliWyszukania==liczbaPozycjiWKsiazce)
            cout << "Brak takiej osoby. Mozesz wprowadzic ja w menu glownym, opcja 1."<<endl;
        system("pause");
    }
    if (wyborSzukaniePozycji=='3')
    {
        cout << "Podaj numer telefonu: "<<endl;
        cin >> podaneDaneSzukanie;

        for (int i=0; i<=liczbaPozycjiWKsiazce; i++)
        {
            if ((WpisWKsiazceAdresowej[i].telefon==podaneDaneSzukanie)&&(WpisWKsiazceAdresowej[i].idUzytkownika==idUzytkownika))
            {
                wypisanieDanejPozycji(WpisWKsiazceAdresowej,i);
                weryfikacjaPetliWyszukania++;
            }
        }
        if (weryfikacjaPetliWyszukania==liczbaPozycjiWKsiazce)
            cout << "Brak takiej osoby. Mozesz wprowadzic ja w menu glownym, opcja 1."<<endl;
        system("pause");
    }
    if (wyborSzukaniePozycji=='4')
    {
        cout << "Podaj adres email: "<<endl;
        cin >> podaneDaneSzukanie;

        for (int i=0; i<=liczbaPozycjiWKsiazce; i++)
        {
            if ((WpisWKsiazceAdresowej[i].email==podaneDaneSzukanie)&&(WpisWKsiazceAdresowej[i].idUzytkownika==idUzytkownika))
            {
                wypisanieDanejPozycji(WpisWKsiazceAdresowej,i);
                weryfikacjaPetliWyszukania++;
            }
        }
        if (weryfikacjaPetliWyszukania==liczbaPozycjiWKsiazce)
            cout << "Brak takiej osoby. Mozesz wprowadzic ja w menu glownym, opcja 1."<<endl;
        system("pause");
    }
}

int usuniecieWpisu (vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int idUzytkownika)
{
    system("cls");
    int liczbaPozycji=WpisWKsiazceAdresowej.size();
    int numerLiniiWPliku;
    int pozycjaDoUsuniecia;
    char pozycjaDoUsunieciaZnak;
    cout << "Usuwanie pozycji z ksiazki adresowej"<<endl;
    cout << "**Jesli chcesz wrocic do menu glownego, wpisz zero.**"<<endl;
    cout <<"Podaj pozycje do usuniecia: ";
    cin >> pozycjaDoUsunieciaZnak;
    string potwierdzenieCheciEdycji;

    pozycjaDoUsuniecia=pozycjaDoUsunieciaZnak-48;

    if (pozycjaDoUsuniecia==0) return liczbaPozycji;

    for (int i=0; i<WpisWKsiazceAdresowej.size(); i++)
    {

        if ((pozycjaDoUsuniecia==WpisWKsiazceAdresowej[i].pozycjaWpisu))
        {
            if (WpisWKsiazceAdresowej[i].idUzytkownika!=idUzytkownika)
            {
                cout << "Probujesz usunac wpis innego uzytkownika. Podaj inny numer pozycji. ";
                Sleep(1000);
                usuniecieWpisu(WpisWKsiazceAdresowej, idUzytkownika);
            }
            else
                cout << "Potwierdz usuniecie danych adresata: "<<WpisWKsiazceAdresowej[i].imie<< " "<<WpisWKsiazceAdresowej[i].nazwisko<<"."<<endl;
            cout << "Czy usunac dane tej osoby? Wpisz TAK dla potwierdzenia. ";
            cin >> potwierdzenieCheciEdycji;

            if ((potwierdzenieCheciEdycji=="TAK")||(potwierdzenieCheciEdycji=="tak"))
            {
                WpisWKsiazceAdresowej.erase(WpisWKsiazceAdresowej.begin()+i);
                cout <<".";
                Sleep(500);
                cout <<".";
                Sleep(500);
                cout <<"."<<endl;
                Sleep(500);
                cout <<"Wybrana pozycja zostala usunieta. Powrot do menu glownego.";
                system("pause");


                numerLiniiWPliku=liczenieLiniiWPliku(pozycjaDoUsuniecia);
                usunieciePozycjiZPliku(WpisWKsiazceAdresowej, numerLiniiWPliku);


                liczbaPozycji--;
                return liczbaPozycji;
            }
            else cout << "Pozycja nie zostala usunieta. Powrot do menu glownego. ";
            system("pause");
            return liczbaPozycji;
        }
    }

    cout << "Brak podanej pozycji w ksiazce adresowej. ";
    cout << "Zweryfikuj, czy na pewno podajesz pozycje swojego Adresata. ";
    cout << "Sprobuj ponownie. ";
    system("pause");
    usuniecieWpisu(WpisWKsiazceAdresowej, idUzytkownika);
}

int liczenieLiniiWPliku(int usuwanaLinia)
{
    int licznikLinii, idPobraneZLinii;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    string pobieranaLiniaZPliku;

    licznikLinii=1;

    while(getline(plik,pobieranaLiniaZPliku))
    {
        idPobraneZLinii = pobranieIDAdresata(pobieranaLiniaZPliku);
        if (idPobraneZLinii==usuwanaLinia)
        {
            plik.close();
            return licznikLinii;
        }
        else licznikLinii++;
    }

    plik.close();
}

void usunieciePozycjiZPliku(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int usuwanaLinia)
{
    fstream plik, plikTymczasowy;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    plikTymczasowy.open("KsiazkaTymczasowa.txt", ios::out | ios::trunc);

    string pobieranaLinia;
    int licznikLinii=1;


    while(getline(plik,pobieranaLinia))
    {
        if (licznikLinii!=usuwanaLinia)
            plikTymczasowy<<pobieranaLinia<<endl;

        licznikLinii++;
    }

    plik.close();
    plikTymczasowy.close();

    zamianaPlikuTymczasowegoNaWlasciwy();

}


int pobranieIDAdresata(string pobieranaLiniaZPliku)
{
    string idOryginalne;
    char znak;
    int dlugoscLinii, idAdresata;


    idOryginalne.clear();
    dlugoscLinii = pobieranaLiniaZPliku.length();

    for (int i=0; i<dlugoscLinii; i++)
    {
        znak = pobieranaLiniaZPliku[i];
        if (znak=='|') break;
        else idOryginalne+=znak;
    }
    idAdresata=atoi(idOryginalne.c_str());

    return idAdresata;
}

int otworzeniePlikuAdresatow(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int idUzytkownika)
{
    string imie, nazwisko, email,adres, telefon, numerPozycji, numerUzytkownika;
    int pozycja, wlasciciel;
    int liczbaWpisow=0;
    ksiazka_adresowa Adresat;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (!plik.good())
    {
        return 0;
    }
    else if (plik.good())
    {
        string kolejnaLinia;
        char znak;


        while(getline(plik,kolejnaLinia))
        {
            int dlugoscSlowa = kolejnaLinia.length();
            imie.clear();
            nazwisko.clear();
            telefon.clear();
            email.clear();
            adres.clear();
            pozycja=0;
            numerPozycji.clear();
            numerUzytkownika.clear();
            wlasciciel=0;

            int licznikPrzerywnikowDanych=1;

            for (int i=0; i<=dlugoscSlowa; i++)
            {
                znak=kolejnaLinia[i];
                if (znak=='|')
                    licznikPrzerywnikowDanych++;
                else switch(licznikPrzerywnikowDanych)
                    {
                    case 1:
                        numerPozycji+=znak;
                        break;
                    case 2:
                        pozycja=atoi(numerPozycji.c_str());
                        numerUzytkownika+=znak;
                        break;
                    case 3:
                        wlasciciel=atoi(numerUzytkownika.c_str());
                        imie+=kolejnaLinia[i];
                        break;
                    case 4:
                        nazwisko+=kolejnaLinia[i];
                        break;
                    case 5:
                        telefon+=kolejnaLinia[i];
                        break;
                    case 6:
                        email+=kolejnaLinia[i];
                        break;
                    case 7:
                        adres+=kolejnaLinia[i];
                        break;
                    }

            }

            Adresat.pozycjaWpisu=pozycja;
            Adresat.idUzytkownika=wlasciciel;
            Adresat.imie=imie;
            Adresat.nazwisko=nazwisko;
            Adresat.telefon=telefon;
            Adresat.email=email;
            Adresat.adres=adres;

            if (wlasciciel==idUzytkownika)
                WpisWKsiazceAdresowej.push_back(Adresat);

        }
        plik.close();

    }

    return pozycja;
}

void wyswietlenieWszystkichOsob(vector <ksiazka_adresowa> WpisWKsiazceAdresowej, int idUzytkownika)
{
    system("cls");
    int liczbaPozycjiWKsiazce = WpisWKsiazceAdresowej.size();
    if (liczbaPozycjiWKsiazce==0)
    {
        cout << "Brak pozycji do wyswielenia"<<endl;
        Sleep(2000);
    }
    else
    {
        int petla = 0;
        while (petla<liczbaPozycjiWKsiazce)
        {
            //  if (WpisWKsiazceAdresowej[petla].idUzytkownika!=idUzytkownika)
            // {
            //    petla++;
            //   continue;
            // }
            cout << (petla+1) <<endl;
            wypisanieDanejPozycji (WpisWKsiazceAdresowej, petla);
            petla++;
        }
        cout << "Koniec wpisow."<<endl;
        system("pause");
    }
}

void edycjaWybranejPozycji(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int liczbaPozycjiWKsiazce, int idUzytkownika)
{
    string potwierdzenieCheciEdycji;
    int pozycjaWpisu;
    int licznikPomocniczy=0;

    system("cls");
    cout << "Edycja wpisu." << endl;
    cout << "**Jesli chcesz wrocic do menu glownego, wpisz zero.**"<<endl;
//    cout << "Obecnie w ksiazce adresowej masz "<<liczbaPozycjiWKsiazce<< " wpisanych osob."<<endl;
    cout << "Podaj numer pozycji do edycji: ";
    cin >> pozycjaWpisu;

    if (pozycjaWpisu==0) return;

    for (int i=0; i<WpisWKsiazceAdresowej.size(); i++)
    {
        if (pozycjaWpisu!=WpisWKsiazceAdresowej[i].pozycjaWpisu)
        {
            licznikPomocniczy++;
        }
    }

    if (licznikPomocniczy==WpisWKsiazceAdresowej.size())
    {
        cout << "Bledny numer pozycji wpisu. Sprobuj jeszcze raz. "<<endl;
        Sleep(1000);
        edycjaWybranejPozycji(WpisWKsiazceAdresowej, WpisWKsiazceAdresowej.size(),idUzytkownika);
    }


    for (int i=0; i<WpisWKsiazceAdresowej.size(); i++)
    {
        if ((pozycjaWpisu==WpisWKsiazceAdresowej[i].pozycjaWpisu)&&(WpisWKsiazceAdresowej[i].idUzytkownika==idUzytkownika))
        {
            wypisanieDanejPozycji(WpisWKsiazceAdresowej,i);
            cout << "Czy chcesz podac nowe dane tej osoby? Wpisz TAK dla potwierdzenia. ";
            cin >> potwierdzenieCheciEdycji;

            if ((potwierdzenieCheciEdycji=="TAK")||(potwierdzenieCheciEdycji=="tak"))
            {
                int wyborElementuDoZmiany;
                cout << "Co chcesz zmienic? Podaj numer opcji."<<endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Telefon" << endl;
                cout << "4. Email" << endl;
                cout << "5. Adres" << endl << endl;
                cin >> wyborElementuDoZmiany;

                switch(wyborElementuDoZmiany)
                {
                case 1:
                    cout << "Obecne imie: "<< WpisWKsiazceAdresowej[i].imie << ". Podaj nowe imie: ";
                    cin.sync();
                    getline(cin, WpisWKsiazceAdresowej[i].imie);
                    break;
                case 2:
                    cout << "Obecne nazwisko: "<< WpisWKsiazceAdresowej[i].nazwisko << ". Podaj nowe nazwisko: ";
                    cin.sync();
                    getline(cin, WpisWKsiazceAdresowej[i].nazwisko);
                    break;
                case 3:
                    cout << "Obecny telefon: "<< WpisWKsiazceAdresowej[i].telefon << ". Podaj nowy telefon: ";
                    cin.sync();
                    getline(cin, WpisWKsiazceAdresowej[i].telefon);
                    break;
                case 4:
                    cout << "Obecny email: "<< WpisWKsiazceAdresowej[i].email <<  ". Podaj nowy email: ";
                    cin.sync();
                    getline(cin, WpisWKsiazceAdresowej[i].email);
                    break;
                case 5:
                    cout <<"Obecny adres: "<< WpisWKsiazceAdresowej[i].adres << ". Podaj nowy adres: ";
                    cin.sync();
                    getline(cin, WpisWKsiazceAdresowej[i].adres);
                    break;
                }
                cout << "Zapisano zmiany.";
                system("pause");
                return;
            }
            else cout << "Powrot do menu glownego."<<endl;
            system("pause");
            return;
        }
    }
    cout << "Probujesz edytowac nie swoj wpis. Sprobuj ponownie.";
    Sleep(2000);
    edycjaWybranejPozycji(WpisWKsiazceAdresowej, liczbaPozycjiWKsiazce, idUzytkownika);


}

void zapisaniePlikuTymczasowego(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int liczbaPozycji)
{
    //zapis do pliku tymczasowego
//    plikTymczasowy.open("ZastepczaKsiazka.txt")

    for (int i=0; i<liczbaPozycji; i++)
    {
        zapisaniePozycjiDoPlikuTymczasowego(WpisWKsiazceAdresowej,i);
    }

}

void zapisaniePozycjiDoPlikuTymczasowego(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej, int pozycjaWKsiazce)
{

    fstream plikTymczasowy;
    plikTymczasowy.open("KsiazkaTymczasowa.txt", ios::out | ios::app);

    plikTymczasowy << WpisWKsiazceAdresowej[pozycjaWKsiazce].pozycjaWpisu<<"|";
    plikTymczasowy << WpisWKsiazceAdresowej[pozycjaWKsiazce].idUzytkownika<<"|";
    plikTymczasowy << WpisWKsiazceAdresowej[pozycjaWKsiazce].imie<<"|";
    plikTymczasowy << WpisWKsiazceAdresowej[pozycjaWKsiazce].nazwisko <<"|";
    plikTymczasowy << WpisWKsiazceAdresowej[pozycjaWKsiazce].telefon <<"|";
    plikTymczasowy << WpisWKsiazceAdresowej[pozycjaWKsiazce].email <<"|";
    plikTymczasowy << WpisWKsiazceAdresowej[pozycjaWKsiazce].adres <<"|"<<endl;

    plikTymczasowy.close();
}


void zapisaniePlikuWlasciwego(vector <ksiazka_adresowa> &WpisWKsiazceAdresowej)
{
    fstream plikGlowny, plikTymczasowy;
    plikGlowny.open("KsiazkaAdresowa.txt", ios::in);
    plikTymczasowy.open("KsiazkaTymczasowa.txt", ios::out);

    string porownywanaLiniaOryginalna;
    int dlugoscLiniiOryginalnej;
    string idOryginalne;
    int idAdresata, weryfikacja;
    char znak;

    if (plikGlowny.good())
    {
        while(getline(plikGlowny,porownywanaLiniaOryginalna))
        {

          idAdresata = pobranieIDAdresata(porownywanaLiniaOryginalna);

            weryfikacja=0;

            for (int p=0; p<WpisWKsiazceAdresowej.size(); p++)
            {
                if (idAdresata==WpisWKsiazceAdresowej[p].pozycjaWpisu)

                {
                   zapisaniePozycjiDoPlikuTymczasowego(WpisWKsiazceAdresowej,p);
                    break;
                }
                else weryfikacja++;

                if (weryfikacja==WpisWKsiazceAdresowej.size())
                {
                    plikTymczasowy << porownywanaLiniaOryginalna<<endl;
                    break;
                }
            }
        }
    }

    plikGlowny.close();
    plikTymczasowy.close();


    zamianaPlikuTymczasowegoNaWlasciwy();

}


void zamianaPlikuTymczasowegoNaWlasciwy()
{
    if (remove("KsiazkaAdresowa.txt")==0);
    {
        rename("KsiazkaTymczasowa.txt", "KsiazkaAdresowa.txt");
    }
}
