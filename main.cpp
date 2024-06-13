#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>

using namespace std;

struct Uzytkownik
{
    int id;
    string login, haslo;
};

struct Adresat
{
    int id;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
};

string wczytajLinie()
{
    string input;
    getline(cin, input);
    return input;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak = {0};

    while (true)
    {
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
        return 0;
    }
    return znak;
}

int wczytanieZPlikuUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    int iloscUzytkownikow = 0;
    string linia = "";
    int numerSlowa = 1;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good() == false)
    {
        return iloscUzytkownikow;
    }

    while(getline(plik, linia))
    {
        stringstream ss (linia);

        while (getline (ss, linia, '|'))
        {
            switch(numerSlowa)
            {
            case 1:
                uzytkownik.id = stoi(linia);
                if (iloscUzytkownikow < uzytkownik.id)
                    iloscUzytkownikow = uzytkownik.id;
                break;
            case 2:
                uzytkownik.login = linia;
                break;
            case 3:
                uzytkownik.haslo = linia;
                numerSlowa= 0;
                break;
            }
            numerSlowa++;
        }
        uzytkownicy.push_back(uzytkownik);
    }
    plik.close();

    return iloscUzytkownikow;
}

int logowanie(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    system("cls");

    string login, haslo;

    cout << ">>> LOGOWANIE <<<" << endl << endl;

    cout << "Podaj login: ";
    login = wczytajLinie();

    for(Uzytkownik uzytkownik : uzytkownicy)
    {
        if(uzytkownik.login == login)
        {
            for (int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                haslo = wczytajLinie();
                if (uzytkownik.haslo == haslo)
                {
                    cout << "Zalogowales sie" << endl;
                    Sleep(1000);
                    return uzytkownik.id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1000);
    return 0;


}

int rejestracja(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    system("cls");

    Uzytkownik uzytkownik;
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    string login, haslo;

    if (plik.good() == true)
    {
        cout << ">>> REJESTRACJA <<<" << endl << endl;

        cout << "Podaj nazwe uzytkownika: ";
        login = wczytajLinie();

        for(vector <Uzytkownik>:: iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            if(itr->login == login)
            {
                cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
                login = wczytajLinie();
                itr = uzytkownicy.begin() - 1;
            }
        }
        cout << "Podaj haslo: ";
        haslo = wczytajLinie();

        uzytkownik.login = login;
        uzytkownik.haslo = haslo;
        uzytkownik.id = iloscUzytkownikow + 1;


        plik << uzytkownik.id << '|';
        plik << uzytkownik.login << '|';
        plik << uzytkownik.haslo << '|' << endl;

        plik.close();

        uzytkownicy.push_back(uzytkownik);

        cout << "Konto zalozone" << endl;
        Sleep(1000);
    }

    return ++iloscUzytkownikow;
}

int wczytanieZPlikuAdresatow(vector <Adresat> &adresaci)
{
    Adresat adresat;
    int iloscAdresatow = 0;
    string linia = "";
    int numerSlowa = 1;

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if (plik.good() == false)
    {
        return iloscAdresatow;
    }

    while(getline(plik, linia))
    {
        stringstream ss (linia);

        while (getline (ss, linia, '|'))
        {
            switch(numerSlowa)
            {
            case 1:
                adresat.id = stoi(linia);
                if (iloscAdresatow < adresat.id)
                    iloscAdresatow = adresat.id;
                break;
            case 2:
                adresat.imie = linia;
                break;
            case 3:
                adresat.nazwisko = linia;
                break;
            case 4:
                adresat.numerTelefonu = linia;
                break;
            case 5:
                adresat.email = linia;
                break;
            case 6:
                adresat.adres = linia;
                numerSlowa= 0;
                break;
            }
            numerSlowa++;
        }
        adresaci.push_back(adresat);
    }
    plik.close();

    return iloscAdresatow;
}

int dodajAdresata(vector <Adresat> &adresaci, int iloscAdresatow)
{
    system("cls");

    Adresat adresat;
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good() == true)
    {
        cout << ">>> DODAWANIE OSOBY <<<" << endl << endl;

        adresat.id = iloscAdresatow + 1;

        cout << "Podaj imie: " << endl;
        adresat.imie = wczytajLinie();

        cout << "Podaj nazwisko: " << endl;
        adresat.nazwisko = wczytajLinie();

        cout << "Podaj numer telefonu: " << endl;
        adresat.numerTelefonu = wczytajLinie();

        cout << "Podaj email: " << endl;
        adresat.email = wczytajLinie();

        cout << "Podaj adres: " << endl;
        adresat.adres = wczytajLinie();


        plik << adresat.id << '|';
        plik << adresat.imie << '|';
        plik << adresat.nazwisko << '|';
        plik << adresat.numerTelefonu << '|';
        plik << adresat.email << '|';
        plik << adresat.adres << '|' << endl;

        plik.close();

        adresaci.push_back(adresat);
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych" << endl;
        system("pause");
    }
    cout << endl << "Osoba zostala dodana" << endl;
    Sleep(1000);

    return ++iloscAdresatow;
}

int wyszukajPoImieniu(vector <Adresat> adresaci, int iloscAdresatow)
{
    system("cls");

    string szukaneImie;
    bool osobaOdnaleziona = false;

    cout << ">>> WYSZUKIWANIE OSOBY PO IMIENIU <<<" << endl << endl;
    cout << "Podaj imie, ktore chcesz wyszukac: ";
    cin >> szukaneImie;

    for(Adresat adresat : adresaci)
    {
        if(adresat.imie == szukaneImie)
        {
            cout << "ID: " << adresat.id << endl;
            cout << "Imie: " << adresat.imie << endl;
            cout << "Nazwisko: " << adresat.nazwisko << endl;
            cout << "Numer telefonu: " << adresat.numerTelefonu << endl;
            cout << "Email: " << adresat.email << endl;
            cout << "Adres: " << adresat.adres << endl;
            osobaOdnaleziona = true;
        }
    }

    if(!osobaOdnaleziona)
        cout << "Nie ma osoby o takim imieniu" << endl;

    system("pause");

    return 0;
}

int wyszukajPoNazwisku(vector <Adresat> &adresaci, int iloscAdresatow)
{
    system("cls");

    string szukaneNazwisko;
    bool osobaOdnaleziona = false;

    cout << ">>> WYSZUKIWANIE OSOBY PO NAZWISKU <<<" << endl << endl;
    cout << "Podaj nazwisko, ktore chcesz wyszukac: ";
    cin >> szukaneNazwisko;

    for(Adresat adresat : adresaci)
    {
        if(adresat.nazwisko == szukaneNazwisko)
        {
            cout << "ID: " << adresat.id << endl;
            cout << "Imie: " << adresat.imie << endl;
            cout << "Nazwisko: " << adresat.nazwisko << endl;
            cout << "Numer telefonu: " << adresat.numerTelefonu << endl;
            cout << "Email: " << adresat.email << endl;
            cout << "Adres: " << adresat.adres << endl;
            osobaOdnaleziona = true;
        }
    }

    if (!osobaOdnaleziona)
        cout << "Nie ma osoby o takim nazwisku" << endl;

    system("pause");

    return 0;
}

int wyswietlWszystkichAdresatow(vector <Adresat> &adresaci, int iloscAdresatow)
{
    system("cls");

    for(Adresat adresat : adresaci)
    {
        cout << "ID: " << adresat.id << endl;
        cout << "Imie: " << adresat.imie << endl;
        cout << "Nazwisko: " << adresat.nazwisko << endl;
        cout << "Numer telefonu: " << adresat.numerTelefonu << endl;
        cout << "Email: " << adresat.email << endl;
        cout << "Adres: " << adresat.adres << endl;
        cout << endl;
    }

    system("pause");

    return 0;
}

void nadpiszPlik(vector <Adresat> &adresaci)
{
    ofstream plik;
    plik.open("ksiazkaAdresowa.txt", ofstream::trunc);

    for(Adresat adresat : adresaci)
    {
        plik << adresat.id << '|';
        plik << adresat.imie << '|';
        plik << adresat.nazwisko << '|';
        plik << adresat.numerTelefonu << '|';
        plik << adresat.email << '|';
        plik << adresat.adres << '|' << endl;
    }

    plik.close();
}

int usunAdresata(vector <Adresat> &adresaci, int iloscAdresatow)
{
    int adresatDoUsuniecia;

    system("cls");

    cout << ">>> USUWANIE WYBRANEJ OSOBY <<<" << endl << endl;
    cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
    cin >> adresatDoUsuniecia;

    for(vector <Adresat>:: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if(itr->id == adresatDoUsuniecia)
        {
            adresaci.erase(itr);
            nadpiszPlik(adresaci);

            if (adresatDoUsuniecia == iloscAdresatow)
                iloscAdresatow--;

            return iloscAdresatow;
        }

    }
    cout << endl << "Nie ma adresata o takim ID" << endl;
    Sleep(1000);
    return iloscAdresatow;

}

int edytujAdresata(vector <Adresat> &adresaci)
{
    int adresatDoEdycji;
    int wybor;
    string nowaDana;

    system("cls");

    cout << ">>> EDYTOWANIE WYBRANEJ OSOBY <<<" << endl << endl;
    cout << "Podaj numer ID adresata, ktorego chcesz edytowac: ";
    cin >> adresatDoEdycji;

    for(Adresat &adresat : adresaci)
    {
        if(adresat.id == adresatDoEdycji)
        {
            system("cls");

            cout << ">>> EDYTOWANIE WYBRANEJ OSOBY <<<" << endl << endl;
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;
            cout << "Podaj numer danej, ktora chcesz zmienic: ";
            cin >> wybor;

            switch(wybor)
            {
            case 1:
                system("cls");

                cout << ">>> EDYTOWANIE WYBRANEJ OSOBY <<<" << endl << endl;
                cout << "Wprowadz nowe imie: ";
                cin >> nowaDana;
                adresat.imie = nowaDana;
                break;
            case 2:
                system("cls");

                cout << ">>> EDYTOWANIE WYBRANEJ OSOBY <<<" << endl << endl;
                cout << "Wprowadz nowe nazwisko: ";
                cin >> nowaDana;
                adresat.nazwisko = nowaDana;
                break;
            case 3:
                system("cls");

                cout << ">>> EDYTOWANIE WYBRANEJ OSOBY <<<" << endl << endl;
                cout << "Wprowadz nowy numer telefonu: ";
                cin >> nowaDana;
                adresat.numerTelefonu = nowaDana;
                break;
            case 4:
                system("cls");

                cout << ">>> EDYTOWANIE WYBRANEJ OSOBY <<<" << endl << endl;
                cout << "Wprowadz nowy email: ";
                cin >> nowaDana;
                adresat.email = nowaDana;
                break;
            case 5:
                system("cls");

                cout << ">>> EDYTOWANIE WYBRANEJ OSOBY <<<" << endl << endl;
                cout << "Wprowadz nowy adres: ";
                cin >> nowaDana;
                adresat.adres = nowaDana;
                break;
            case 6:
                return 0;
                break;
            default:
                cout << "Nie ma takiej opcji w menu" << endl;
                Sleep(1000);
                return 0;
            }
            nadpiszPlik(adresaci);

            return 0;
        }

    }

    cout << endl << "Nie ma adresata o podanym ID";
    Sleep(1000);
    return 0;
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    int iloscUzytkownikow = 0;
    int iloscAdresatow = 0;
    int idZalogowanegoUzytkownika = 0;
    char wybor;

    iloscUzytkownikow = wczytanieZPlikuUzytkownikow(uzytkownicy);

    while(true)
    {
        system("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "9. Zakoncz program" << endl;

        wybor = wczytajZnak();

        switch(wybor)
        {
        case '1':
            idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
            break;
        case '2':
            iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);
            break;
        case '9':
            return 0;
            break;
        }
    }

    iloscAdresatow = wczytanieZPlikuAdresatow(adresaci);

    while(true)
    {
        system("cls");
        cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie osoby" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";

        wybor = wczytajZnak();

        switch(wybor)
        {
        case '1':
            iloscAdresatow = dodajAdresata(adresaci, iloscAdresatow);
            break;
        case '2':
            wyszukajPoImieniu(adresaci, iloscAdresatow);
            break;
        case '3':
            wyszukajPoNazwisku(adresaci, iloscAdresatow);
            break;
        case '4':
            wyswietlWszystkichAdresatow(adresaci, iloscAdresatow);
            break;
        case '5':
            iloscAdresatow = usunAdresata(adresaci, iloscAdresatow);
            break;
        case '6':
            edytujAdresata(adresaci);
            break;
        case '9':
            return 0;
            break;
        default:
            cout << "Nie ma takiej opcji w menu" << endl;
            Sleep(1000);
        }
    }
    return 0;
}
