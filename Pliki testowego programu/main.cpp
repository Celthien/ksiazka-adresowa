#include <iostream>
#include "testowanie.h"

using namespace std;

int main()
{
    Lista_uzytkownikow zarejestrowaniUzytkownicy;
    cout << "Zaczynamy" <<endl;
    getchar();

    zarejestrowaniUzytkownicy.otworzeniePlikuUzytkownikow();
    zarejestrowaniUzytkownicy.rejestracjaUzytkownika();


    return 0;
}
