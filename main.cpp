#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <vector>


using namespace std;

struct DaneZnajomego
{
    string imie, nazwisko, nrTel, email, adres;
    int id;
};

int przydzielanieNumeruID (int potencjalnyNumerID, vector <DaneZnajomego> dane)
{
    for (int i = 0; i < dane.size(); i++)
    {
        if (potencjalnyNumerID == dane[i].id)
        {
            potencjalnyNumerID++;
            i = 0;
        }
    }

    return potencjalnyNumerID;
}

void dodawanie (vector <DaneZnajomego> dane)
{
    DaneZnajomego zestawDanych;

    int potencjalnyNumerID = dane.size() + 1;
    zestawDanych.id = przydzielanieNumeruID(potencjalnyNumerID, dane);

    cout << "Wprowadz dane znajomego" << endl;
    cout << "-----------------------" << endl;
    cout << "Imie: ";
    cin >> zestawDanych.imie;
    cout << "Nazwisko: ";
    cin >> zestawDanych.nazwisko;
    cout << "Numer telefonu: ";
    cin.sync();
    getline(cin,zestawDanych.nrTel);
    cout << "Email: ";
    cin >> zestawDanych.email;
    cout << "Adres: ";
    cin.sync();
    getline(cin,zestawDanych.adres);

    dane.insert(dane.begin() + dane.size(), zestawDanych);

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);

    plik << zestawDanych.id << "|" << zestawDanych.imie << "|";
    plik << zestawDanych.nazwisko << "|" << zestawDanych.nrTel << "|";
    plik << zestawDanych.email << "|" << zestawDanych.adres << "|" << endl;

    plik.close();

    cout << endl;
    cout << "SUKCES! Wlasnie dodano nowego znajomego!" << endl;

    system("pause");
}

void wyswietl_liste(vector <DaneZnajomego> dane)
{
    if (dane.size() != 0)
    {
        cout << "Oto wszystkie kontakty znajdujace sie w Twojej ksiazce:" << endl;

        for (int i = 0; i < dane.size(); i++)
        {
            cout << dane[i].id << "|" << dane[i].imie << "|";
            cout << dane[i].nazwisko << "|" << dane[i].nrTel << "|";
            cout << dane[i].email << "|" << dane[i].adres << "|" << endl;
        }
    }

    else if (dane.size() == 0)
    {
        cout << "Brak kontaktow w ksiazce." << endl;
    }

    system("pause");
}


void wyszukajImie (vector <DaneZnajomego> dane)
{
    string imieZnajomego;
    int wskaznik = 0;

    cout << "Podaj imie: ";
    cin >> imieZnajomego;


    for (int i = 0; i < dane.size(); i++)
    {
        if (dane[i].imie == imieZnajomego)
        {
            wskaznik = 1;
        }
    }

    if (wskaznik == 1)
    {
        cout << "Oto osoby o takim imieniu w Twojej ksiazce:" << endl;

        for (int i = 0; i < dane.size(); i++)
        {
            if (dane[i].imie == imieZnajomego)
            {
                cout << dane[i].id << "|" << dane[i].imie << "|";
                cout << dane[i].nazwisko << "|" << dane[i].nrTel << "|";
                cout << dane[i].email << "|" << dane[i].adres << "|" << endl;
            }
        }
    }

    if (wskaznik == 0)
    {
        cout << "Brak osoby o takim imieniu na liscie." << endl;
    }

    system("pause");
}

void wyszukajNazwisko (vector <DaneZnajomego> dane)
{
    string nazwiskoZnajomego;
    int wskaznik = 0;

    cout << "Podaj nazwisko: ";
    cin >> nazwiskoZnajomego;


    for (int i = 0; i < dane.size(); i++)
    {
        if (dane[i].nazwisko == nazwiskoZnajomego)
        {
            wskaznik = 1;
        }
    }

    if (wskaznik == 1)
    {
        cout << "Oto osoby o takim nazwisku w Twojej ksiazce:" << endl;

        for (int i = 0; i < dane.size(); i++)
        {
            if (dane[i].nazwisko == nazwiskoZnajomego)
            {
                cout << dane[i].id << "|" << dane[i].imie << "|";
                cout << dane[i].nazwisko << "|" << dane[i].nrTel << "|";
                cout << dane[i].email << "|" << dane[i].adres << "|" << endl;
            }
        }
    }

    if (wskaznik == 0)
    {
        cout << "Brak osoby o takim nazwisku na liscie." << endl;
    }

    system("pause");
}

vector <DaneZnajomego> daneZPilkuDoWektora(vector <DaneZnajomego> dane)
{
    DaneZnajomego zestawDanych;

    string linia, informacje[6];
    int nr_linii = 1;

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::in);

    while (getline(plik, linia))
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < linia.length(); j++)
            {
                if (linia[j] == '|')
                {
                    informacje[i] = linia.substr(0, j);
                    linia = linia.erase(0, informacje[i].length() + 1);
                    break;
                }
            }
        }

        zestawDanych.id = atoi(informacje[0].c_str());
        zestawDanych.imie = informacje[1];
        zestawDanych.nazwisko = informacje[2];
        zestawDanych.nrTel = informacje[3];
        zestawDanych.email = informacje[4];
        zestawDanych.adres = informacje[5];

        dane.insert(dane.begin() + dane.size(), zestawDanych);

        nr_linii++;
    }

    plik.close();

    return dane;
}

void edycjaDanychZnajomego (vector <DaneZnajomego> dane, char wybor)
{
    DaneZnajomego zestawDanych;

    int nrID, wskaznik = 0;

    cout << "Podaj ID znajomego: ";
    cin >> nrID;


    for (int i = 0; i < dane.size(); i++)
    {
        if (dane[i].id == nrID)
        {
            zestawDanych = dane[i];

            if (wybor == '1')
            {
                cout << "Jakim imieniem zastapic obecne?" << endl;
                cin >> zestawDanych.imie;
            }
            else if (wybor == '2')
            {
                cout << "Jakim nazwiskiem zastapic obecne?" << endl;
                cin >> zestawDanych.nazwisko;
            }
            else if (wybor == '3')
            {
                cout << "Jakim numerem telefonu zastapic obecny?" << endl;
                getline(cin, zestawDanych.nrTel);
            }
            else if (wybor == '4')
            {
                cout << "Jakim emailem zastapic obecny?" << endl;
                cin >> zestawDanych.email;
            }
            else if (wybor == '5')
            {
                cout << "Jakim adresem zastapic obecny?" << endl;
                getline(cin, zestawDanych.adres);
            }

            cout << endl << "Pomyslnie zapisano zmiany." << endl;

            wskaznik = 1;
            dane[i] = zestawDanych;

            system("pause");
        }
    }


    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out);

    for (int i = 0; i < dane.size(); i++)
    {
        plik << dane[i].id << "|" << dane[i].imie << "|";
        plik << dane[i].nazwisko << "|" << dane[i].nrTel << "|";
        plik << dane[i].email << "|" << dane[i].adres << "|" << endl;
    }

    plik.close();

    if (wskaznik == 0)
    {
        cout << "Nie ma osoby o takim ID w Twojej ksiazce."<< endl;

        system("pause");
    }
}

void usunZapis (vector <DaneZnajomego> dane)
{
    int wskaznik = 0, idZnajomegoDoUsuniecia;
    char wybor;

    cout << "Podaj ID znajomego: ";
    cin >> idZnajomegoDoUsuniecia;
    cout << endl;

    cout << "Potwierdz swoj wybor naciskajac 't'" << endl;
    cout << "                LUB" << endl;
    cout << "Nacisnij dowolny inny klawisz, aby wrocic do menu." << endl;
    cout << endl;
    cin >> wybor;

    if(wybor == 't')
    {
        for (int i = 0; i < dane.size(); i++)
        {
            if (dane[i].id == idZnajomegoDoUsuniecia)
            {
                auto iteracja = dane.begin() + i;
                dane.erase(iteracja);
                wskaznik = 1;
                i--;
            }
        }

        fstream plik;
        plik.open("ksiazka_adresowa.txt", ios::out);


        for (int i = 0; i < dane.size(); i++)
        {
            plik << dane[i].id << "|" << dane[i].imie << "|";
            plik << dane[i].nazwisko << "|" << dane[i].nrTel << "|";
            plik << dane[i].email << "|" << dane[i].adres << "|" << endl;
        }

        plik.close();

        if (wskaznik == 0)
        {
            cout << "Nie ma osoby o takim ID w Twojej ksiazce." << endl;

            system("pause");
        }
        else
        {
            cout << "Pomyslnie usunieto zapis." << endl;

            system("pause");
        }
    }
    else
    {
        ;
    }
}


int main()
{
    char wybor;

    while (1)
    {
        vector <DaneZnajomego> dane;
        dane = daneZPilkuDoWektora(dane);

        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";

        cin >> wybor;

        cout << endl;

        if (wybor == '1')
        {
            dodawanie(dane);
        }
        else if (wybor == '2')
        {
            wyszukajImie(dane);
        }
        else if (wybor == '3')
        {
            wyszukajNazwisko(dane);
        }
        else if (wybor == '4')
        {
            wyswietl_liste(dane);
        }
        else if (wybor == '5')
        {
            usunZapis(dane);
        }
        else if (wybor == '6')
        {
            while(1)
            {
                system("cls");
                cout << "1 - imie" << endl;
                cout << "2 - nazwisko" << endl;
                cout << "3 - numer telefonu" << endl;
                cout << "4 - email" << endl;
                cout << "5 - adres" << endl;
                cout << "6 - powrot do menu" << endl;
                cout << "Twoj wybor: ";

                cin >> wybor;

                cout << endl;

                if (wybor == '1' || wybor == '2' || wybor == '3' || wybor == '4' || wybor == '5')
                {
                    edycjaDanychZnajomego(dane, wybor);
                }
                else if (wybor == '6')
                {
                    break;
                }
            }
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}
