#include "Kontrolor.h"
#include <iostream>

Kontrolor::Kontrolor(string ime, string lozinka) : Korisnik(ime, lozinka, 'K')
{

}

void Kontrolor::kreirajLet()
{
	string sifra;
	string odlazak;
	string dolazak;
	Vrijeme vrijemePolaska;
	Vrijeme vrijemeDolaska;
	Datum datum;
	string opis;
	int brojMjesta;
	int brojSlobodnihMjesta;

	cout << "Unesite podatke o letu:" << endl;
	cout << "Sifra leta:" << endl;
	cin >> sifra;
	cout << "Mjesto polaska:" << endl;
	cin >> odlazak;
	cout << "Mjesto dolaska:" << endl;
	cin >> dolazak;
	cout << "Vrijeme polaska:" << endl;
	cout << "Sat: ";
	cin >> vrijemePolaska.sat;
	cout << endl;
	cout << "Minut: ";
	cin >> vrijemePolaska.minut;
	cout << endl;
	cout << "Datum:" << endl;
	cout << "Dan: ";
	cin >> datum.dan;
	cout << endl;
	cout << "Mjesec: ";
	cin >> datum.mjesec;
	cout << endl;
	cout << "Godina: ";
	cin >> datum.godina;
	cout << endl;
	cout << "Kratak opis leta:" << endl;
	cin >> opis;
	cout << "Broj mjesta:" << endl;
	cin >> brojMjesta;
	
	string odgovor;
	cout << "Potvrdite kreiranje leta: " << endl;
	cout << "A) Da, kreiraj     B) Ne, odustani" << endl;
	if (odgovor == "A")
	{
		if (dodajLetURaspored(datum, vrijemeDolaska))
			cout << "Uspjesno ste kreirali let." << endl;
		else
			cout << "Raspored je popunjen! Nije moguce kreirati let." << endl;
	}
	else
	{
		return;
	}

}

bool Kontrolor::dodajLetURaspored(Datum datum1, Vrijeme vrijeme1)
{
	fstream fin;
	fin.open("raspored.txt", ios::in);

	
}