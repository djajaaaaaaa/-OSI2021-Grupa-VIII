#include "Kontrolor.h"
#include <iostream>
#include <vector>
#include <sstream>

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
	cout << "Vrijeme dolaska:" << endl;
	cout << "Sat: ";
	cin >> vrijemeDolaska.sat;
	cout << endl;
	cout << "Minut: ";
	cin >> vrijemeDolaska.minut;
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
	cout << "Kratak opis leta: (najvise 150 karaktera)" << endl;
	do
	{
		cin >> opis;
		if (opis.length() > 150)
		{
			cout << "Prekoracili ste dozvoljen broj karaktera! Pokusajte ponovo. " << endl;
		}
	} while (opis.length() > 150);
	cout << "Broj mjesta:" << endl;
	cin >> brojMjesta;
	brojSlobodnihMjesta = brojMjesta;  //kad se let kreira sva mjesta su slobodna

	Let let1(sifra, odlazak, dolazak, vrijemePolaska, vrijemeDolaska, datum, opis, brojMjesta, brojSlobodnihMjesta);
	string odgovor;
	cout << "Potvrdite kreiranje leta: " << endl;
	cout << "A) Da, kreiraj     B) Ne, odustani" << endl;
	if (odgovor == "A")
	{
		if (dodajLetURaspored(let1))
			cout << "Uspjesno ste kreirali let." << endl;
		else
			cout << "Raspored je popunjen! Nije moguce kreirati let." << endl;
	}
	else if (odgovor == "B")
	{
		return;
	}
	else
	{
		cout << "Nepoznata opcija!" << endl;
	}

}

bool Kontrolor::dodajLetURaspored(Let& let1)
{
	fstream fin;
	fin.open("raspored.txt", ios::in);

	return true;
}

void Kontrolor::informacijeLet()
{
	string sifra;
	cout << "Unesite šifru leta (6 karaktera): ";
	cin >> sifra;
	cout << endl;

	if (!pretragaLeta(sifra))
		cout << "Neuspjesna pretraga! Trazeni let ne postoji." << endl;

}

bool Kontrolor::pretragaLeta(string sifraLeta)
{
	vector<string> row;
	string line, word;
	fstream fin;
	fin.open("raspored.csv", ios::in);
	while (!fin.eof())
	{
		row.clear();
		getline(fin, line);
		stringstream str(line);
		while (getline(str, word, ',')) {

			row.push_back(word);
		}

		if (sifraLeta == row[0])
		{
			cout << "Detalji leta:" << endl;
			cout << "Sifra: " << row[0] << endl;
			cout << "od: " << row[1] << " do: " << row[2] << endl;
			cout << "Vrijeme polaska: " << row[3] << endl;
			cout << "Vrijeme dolaska: " << row[4] << endl;
			cout << "Datum: " << row[5] << endl;
			cout << "Opis: " << row[6] << endl;
			cout << "Broj mjesta: " << row[7] << endl;
			cout << "Broj slobodnih mjesta: " << row[8] << endl;
			return true;
		}
	}
	return false;
}