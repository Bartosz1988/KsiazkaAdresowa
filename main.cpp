#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, nr_tel, email, adres;
};

//Odczyt z pliku txt
int wczytajZPliku(vector <Kontakt> &listaKontaktow)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()==false)
    {
        cout << "Plik o podanej nazwie nie istnieje!";
        exit(0);
    }

    Kontakt kontakt;
    string pozycja;
    char ogranicznik = '|';
    int nr_linii=1;
    int nr_pozycji=1;

    for (int i = 0; plik.eof() != 1; i++)
    {
        while(getline(plik, pozycja, ogranicznik))
        {
            switch(nr_pozycji%7)
            {
            case 1:
                kontakt.id = atoi(pozycja.c_str());
                break;
            case 2:
                kontakt.imie = pozycja;
                break;
            case 3:
                kontakt.nazwisko = pozycja;
                break;
            case 4:
                kontakt.nr_tel = pozycja;
                break;
            case 5:
                kontakt.email = pozycja;
                break;
            case 6:
                kontakt.adres = pozycja;
                break;
            case 7:
                kontakt.adres = pozycja;
                break;
            }
            nr_pozycji++;

            if (nr_pozycji > 6)
            {
                nr_pozycji = 1;
                listaKontaktow.push_back(kontakt);
                nr_linii++;
            }
        }
    }
    plik.close();
    return nr_linii-1;
}

void dopiszKontaktDoPliku(Kontakt daneOsoby)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik << daneOsoby.id << '|';
        plik << daneOsoby.imie << '|';
        plik << daneOsoby.nazwisko << '|';
        plik << daneOsoby.nr_tel << '|';
        plik << daneOsoby.email << '|';
        plik << daneOsoby.adres << '|' << endl;

        plik.close();

        //cout << endl << "Kontakt " << daneOsoby.imie << " " << daneOsoby.nazwisko << " zostal dodany do ksiazki adresowej" << endl;
        //Sleep(3000);
    }
    else cout << "Nie mozna otworzyc pliku" << endl;
}

Kontakt dodawanieKontaktu(vector <Kontakt> &listaKontaktow)
{
    Kontakt osoba;

    system("cls");
    cout << "Dodaj nowy kontakt" << endl << endl;

    if(listaKontaktow.empty() == true)
        osoba.id = 1;
    else
        osoba.id = listaKontaktow.back().id + 1;

    cout << "Imie: " << endl;
    cin.sync();
    getline (cin, osoba.imie);
    cout << "Nazwisko: " << endl;
    cin.sync();
    getline (cin, osoba.nazwisko);
    cout << "Numer telefonu: " << endl;
    cin.sync();
    getline (cin, osoba.nr_tel);
    cout << "Adres email: " << endl;
    cin.sync();
    getline (cin, osoba.email);
    cout << "Adres zamieszkania: " << endl;
    cin.sync();
    getline (cin, osoba.adres);

    //dodawanie danych do wektora
    listaKontaktow.push_back(osoba);

    //zapis do pliku .txt
    dopiszKontaktDoPliku(osoba);
    cout << endl << "Kontakt " << osoba.imie << " " << osoba.nazwisko << " zostal dodany do ksiazki adresowej" << endl;
    Sleep(3000);

    return osoba;
}

void szukajPoImieniu(vector <Kontakt> &listaKontakow)
{
    string imieDoWyszukania;
    vector <string> znalezioneImiona;
    cout << "Podaj imie: ";
    cin >> imieDoWyszukania;

    int licznikOsob = 0;
    while(licznikOsob < listaKontakow.size())
    {
        if (imieDoWyszukania[0]>95) imieDoWyszukania[0]=imieDoWyszukania[0]-32;
        if (listaKontakow[licznikOsob].imie==imieDoWyszukania)
        {
            znalezioneImiona.push_back (imieDoWyszukania);
            cout << listaKontakow[licznikOsob].imie << " " << listaKontakow[licznikOsob].nazwisko << endl;
            cout << "tel. " << listaKontakow[licznikOsob].nr_tel << ", email: " << listaKontakow[licznikOsob].email << endl;
            cout << "adres: " << listaKontakow[licznikOsob].adres << endl << endl;
            system("pause");
        }
        licznikOsob++;
    }
    if (znalezioneImiona.empty())
    {
        cout << "Nie masz kontaktow o tym imieniu" << endl;
        Sleep(4000);
    }

}

void szukajPoNazwisku(vector <Kontakt> &listaKontakow)
{
    string nazwiskoDoWyszukania;
    vector <string> znalezioneNazwiska;
    cout << "Podaj nazwisko: ";
    cin >> nazwiskoDoWyszukania;

    int licznikOsob = 0;
    while(licznikOsob < listaKontakow.size())
    {
        if (nazwiskoDoWyszukania[0]>95) nazwiskoDoWyszukania[0]=nazwiskoDoWyszukania[0]-32;
        if (listaKontakow[licznikOsob].nazwisko==nazwiskoDoWyszukania)
        {
            znalezioneNazwiska.push_back (nazwiskoDoWyszukania);
            cout << listaKontakow[licznikOsob].imie << " " << listaKontakow[licznikOsob].nazwisko << endl;
            cout << "tel. " << listaKontakow[licznikOsob].nr_tel << ", email: " << listaKontakow[licznikOsob].email << endl;
            cout << "adres: " << listaKontakow[licznikOsob].adres << endl << endl;
            system("pause");
        }
        licznikOsob++;
    }
    if (znalezioneNazwiska.empty())
    {
        cout << "Nie masz kontaktow o tym imieniu" << endl;
        Sleep(4000);
    }

}

void wyswietlWszystkieKontakty(vector <Kontakt> &wszystkieKontakty)
{
    for(int licznik=0; licznik<wszystkieKontakty.size(); licznik++)
    {
        cout << wszystkieKontakty[licznik].id << " ";
        cout << wszystkieKontakty[licznik].imie << " " << wszystkieKontakty[licznik].nazwisko << endl;
        cout << "tel. " << wszystkieKontakty[licznik].nr_tel << ", email: " << wszystkieKontakty[licznik].email << endl;
        cout << "adres: " << wszystkieKontakty[licznik].adres << endl << endl;
    }
    system("Pause");
}

void wyswietlImionaNazwiska(vector <Kontakt> &wszystkieKontakty)
{
    for(int licznik=0; licznik<wszystkieKontakty.size(); licznik++)
    {
        cout << wszystkieKontakty[licznik].id << " ";
        cout << wszystkieKontakty[licznik].imie << " ";
        cout << wszystkieKontakty[licznik].nazwisko << endl;
    }
}

void usuwanieKontaktu(vector<Kontakt> &wszystkieKontakty)
{
    char potwierdzenie;
    int numerKontaktuDoUsuniecia;

    cin >> numerKontaktuDoUsuniecia;

    for(int licznik=0; licznik<wszystkieKontakty.size(); licznik++)
    {
        if(numerKontaktuDoUsuniecia == wszystkieKontakty[licznik].id)
        {
            cout << endl << "Czy na pewno chcesz usunac kontakt: " << wszystkieKontakty[licznik].imie << " " <<wszystkieKontakty[licznik].nazwisko << "? [y/n]";
            cin >> potwierdzenie;
            if(potwierdzenie == 'y')
            {
                wszystkieKontakty.erase(wszystkieKontakty.begin()+licznik);
                cout << endl << "Kontakt " << wszystkieKontakty[licznik].imie << " " << wszystkieKontakty[licznik].nazwisko << " zostal usuniety z ksiazki adresowej" << endl;
                Sleep(3000);
            }
        }
    }
}

void aktualizacjaID(vector<Kontakt> &wszystkieKontakty)
{
    for(int i=0; i<wszystkieKontakty.size(); i++)
    {
        wszystkieKontakty[i].id = i+1;
    }
}

void edycjaDanychOsoby(vector<Kontakt> &wszystkieKontakty)
{
    int numerKontaktuDoEdycji;
    int numerAtrybutu = 0;

    cout << "Wybierz z listy numer osoby, ktorej dane chcesz edystowac" << '\n' << '\n';
    wyswietlImionaNazwiska(wszystkieKontakty);
    //system("pause");

    cout << endl << "podaj numer: ";
    cin >> numerKontaktuDoEdycji;

    for(int i=0; i<wszystkieKontakty.size(); i++)
    {
        if(numerKontaktuDoEdycji == wszystkieKontakty[i].id)
        {
            system("cls");

            cout << "Wybierz ktory z atrybutow wybranej osoby chcesz edytowac" << endl << endl;
            cout << "1. ID: " << wszystkieKontakty[i].id << endl;
            cout << "2. imie: " << wszystkieKontakty[i].imie << endl;
            cout << "3. nazwisko: " << wszystkieKontakty[i].nazwisko << endl;
            cout << "4. nr tel: " << wszystkieKontakty[i].nr_tel << endl;
            cout << "5. email: " << wszystkieKontakty[i].email << endl;
            cout << "6. adres: " << wszystkieKontakty[i].adres << endl << endl;

            cout << "podaj numer atrybutu: ";
            cin >> numerAtrybutu;

            if(numerAtrybutu == 1)
            {
                cout << "Nie mozna edytowac numeru ID. Mozesz usunac caly kontakt z listy" << endl;
                Sleep(3000);
            }
            else if(numerAtrybutu == 2)
            {
                string noweImie = "";
                cout << "Podaj nowe imie: ";
                cin.sync();
                getline(cin, noweImie);
                wszystkieKontakty[i].imie = noweImie;
            }
            else if(numerAtrybutu == 3)
            {
                string noweNazwisko = "";
                cout << "Podaj nowe nazwisko: ";
                cin.sync();
                getline(cin, noweNazwisko);
                wszystkieKontakty[i].nazwisko = noweNazwisko;
            }
            else if(numerAtrybutu == 4)
            {
                string nowyTel = "";
                cout << "Podaj nowy numer tel: ";
                cin.sync();
                getline(cin, nowyTel);
                wszystkieKontakty[i].nr_tel = nowyTel;
            }
            else if(numerAtrybutu == 5)
            {
                string nowyEmail = "";
                cout << "Podaj nowy email: ";
                cin.sync();
                getline(cin, nowyEmail);
                wszystkieKontakty[i].email = nowyEmail;
            }
            else if(numerAtrybutu == 6)
            {
                string nowyAdres = "";
                cout << "Podaj nowy adres: ";
                cin.sync();
                getline(cin, nowyAdres);
                wszystkieKontakty[i].adres = nowyAdres;
            }
            cout << endl << "Dane zostaly poprawnie zmienione";
            Sleep(3000);
        }
    }
}

int main()
{
    //utworzenie obiektu struktury/klasy Kontakt
    Kontakt osoba;
    int iloscKontaktow = 0;
    char wyborMenuGlowne;

    //utworzenie vectora, ktory ma przechowywac obiekty typu Kontakt. Narazie ten wektor jest pusty.
    vector<Kontakt> listaKontaktow;

    //wczytanie listy kontaktow z pliku .txt
    iloscKontaktow = wczytajZPliku(listaKontaktow);

    while(1)
    {
        system("cls");
        cout << "Menu glowne:" << endl;
        cout << "1. Dodaj nowy kontakt" << endl;
        cout << "2. Wyszukaj kontakt" << endl;
        cout << "3. Wyswietl wszystkie kontakty" << endl;
        cout << "4. Edytuj kontakt" << endl;
        cout << "5. Usun kontakt" << endl;
        cout << "9. Zakoncz dzialanie programu" << endl << endl;
        cout << "Wybieram opcje: ";
        wyborMenuGlowne=getch();
        cout << endl;

        if (wyborMenuGlowne=='1')
        {
            system("cls");
            osoba = dodawanieKontaktu(listaKontaktow);
        }
        else if (wyborMenuGlowne=='2')
        {
            system("cls");
            char sposobWyszukiwania;

            system("cls");
            cout << "1. Wyszukaj po imieniu" << endl;
            cout << "2. Wyszukaj po nazwisku" << endl;
            cout << "Wybieram opcje: ";
            sposobWyszukiwania=getch();

            if (sposobWyszukiwania=='1')
            {
                system("cls");
                szukajPoImieniu(listaKontaktow);
            }
            else if (sposobWyszukiwania=='2')
            {
                system("cls");
                szukajPoNazwisku(listaKontaktow);
            }
        }
        else if (wyborMenuGlowne=='3')
        {
            system("cls");
            wyswietlWszystkieKontakty(listaKontaktow);
        }
        else if (wyborMenuGlowne=='4')
        {
            system("cls");
            edycjaDanychOsoby(listaKontaktow);

            ofstream plik("KsiazkaAdresowa.txt");
            plik << "";
            for(int i=0; i<listaKontaktow.size(); i++)
            {
                dopiszKontaktDoPliku(listaKontaktow[i]);
            }
        }
        else if (wyborMenuGlowne=='5')
        {
            system("cls");
            cout << endl << "Wybierz z listy numer kontaktu do usuniecia" << '\n' << '\n';
            wyswietlImionaNazwiska(listaKontaktow);
            cout << endl << "podaj numer: ";
            usuwanieKontaktu(listaKontaktow);
            aktualizacjaID(listaKontaktow);

            ofstream plik("KsiazkaAdresowa.txt");
            plik << "";
            for(int i=0; i<listaKontaktow.size(); i++)
            {
                dopiszKontaktDoPliku(listaKontaktow[i]);
            }
        }
        else if (wyborMenuGlowne=='9')
        {
            exit(0);
        }
    }

    return 0;
}
