#include "Kontrolor.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>
#include <filesystem>
#include "Let.h"

Kontrolor::Kontrolor(string ime, string lozinka) : Korisnik(ime, lozinka, 'K')
{

}

void Kontrolor::kreirajLet(std::vector<Let>& letovi)
{
	string sifra;
	string odlazak;
	string dolazak;
	string vrijemePolaska;
	string vrijemeDolaska;
	string datum;
	string opis;
	string brojMjesta;
	string brojSlobodnihMjesta;

	cout << "Unesite podatke o letu:" << endl;
	cout << "Sifra leta:" << endl;
	cin >> sifra;
	cout << "Mjesto polaska:" << endl;
	cin >> odlazak;
	char b = cin.get();
	while (b != '\n')
	{
		opis += b;
		b = cin.get();
	}
	cout << "Mjesto dolaska:" << endl;
	cin >> dolazak;
	b = cin.get();
	while (b != '\n')
	{
		opis += b;
		b = cin.get();
	}
	cout << "Vrijeme polaska (format ss:mm):" << endl;  //dodati provjeru da li je format ispostovan
	cin >> vrijemePolaska;
	cout << endl;
	cout << "Vrijeme dolaska (format ss:mm):" << endl;
	cin >> vrijemeDolaska;
	cout << "Datum (format dd.mm.gggg) " << endl;
	cin >> datum;
	cout << "Kratak opis leta: (najvise 150 karaktera)" << endl;
	do
	{
		cin >> opis;
		b = cin.get();
		while (b != '\n')
		{
			opis += b;
			b = cin.get();
		}
	} while (opis.length() > 150);
	cout << "Broj mjesta:" << endl;
	cin >> brojMjesta;
	brojSlobodnihMjesta = brojMjesta;

	Let let1(sifra, odlazak, dolazak, vrijemePolaska, vrijemeDolaska, datum, opis, brojMjesta, brojSlobodnihMjesta);
	string odgovor;
	cout << "Potvrdite kreiranje leta: " << endl;
	cout << "A) Da, kreiraj     B) Ne, odustani" << endl;
	cin >> odgovor;
	if (odgovor == "A")
	{
		if (dodajLetURaspored(let1, letovi))
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

// pomocne funkcije za kreirajLet()
bool Kontrolor::dodajLetURaspored(Let& let1, std::vector<Let>& letovi)
{
	vector<string> row;
	string line, word;
	fstream fin;
	fin.open("raspored.txt", ios::in);
	while (!fin.eof())
	{
		row.clear();
		getline(fin, line);
		stringstream str(line);
		while (getline(str, word, ',')) {

			row.push_back(word);
		}
		if (!(row.empty()))  // ako je raspored prazan
		{
			if (let1.sifra == row[0])
			{
				cout << "Postoji let sa sifrom " << let1.sifra << " Ne mozete kreirati novi let!" << endl;
				return false;
			}
			if (let1.datum == row[5])
			{
				if ((let1.vrijemePolaska == row[3]) || (let1.vrijemePolaska == row[4]))
					return false;
			}
		}
	}
	upisiLet(let1);
	letovi.push_back(let1);
	return true;
}


void Kontrolor::upisiLet(Let& let1)
{
	fstream fout;
	fout.open("raspored.txt", ios::out | ios::app);
	fout << let1.sifra << ",";
	fout << let1.odlazak << ",";
	fout << let1.dolazak << ",";
	fout << let1.vrijemePolaska << ",";
	fout << let1.vrijemeDolaska << ",";
	fout << let1.datum << ",";
	fout << let1.opis << ",";
	fout << let1.brojMjesta << ",";
	fout << let1.brojSlobodnihMjesta;
	fout << "\n";
	fout.close();
}

void Kontrolor::izmjenaStatusa(std::vector<Let>& letovi)
{
	string sifra;
	cout << "Unesite sifru leta (6 karaktera): ";
	cin >> sifra;
	cout << endl;
	string datum;
	cout << "Unesite datum leta (format: dd.mm.gggg.): ";
	cin >> datum;
	cout << endl;
	std::vector<Let>::iterator it = std::find_if(letovi.begin(), letovi.end(), [sifra, datum](Let& let1) { return (datum == let1.datum && sifra == let1.sifra); });
	if (it == letovi.end())
	{
		cout << "Greska! Let ne postoji." << endl;
		return;
	}
	string status;
	cout << "Promjena statusa u (poletio, leti, sletio): ";
	cin >> status;
	cout << endl;
	(*it).status = status;
	cout << "Uspjesno ste promijenili status leta." << endl;
}


void Kontrolor::informacijeLet()
{
	string sifra;
	cout << "Unesite sifru leta (6 karaktera): ";
	cin >> sifra;
	cout << endl;

	pretragaLeta(sifra);
}

// pomocne funkcije informacijeLet()
void Kontrolor::pretragaLeta(string sifraLeta)
{
	vector<string> row;
	string line, word;
	fstream fin;
	fin.open("raspored.txt", ios::in);
	while (!fin.eof())
	{
		row.clear();
		getline(fin, line);
		stringstream str(line);
		while (getline(str, word, ',')) {

			row.push_back(word);
		}

		if (!row.empty())
		{
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
				return;
			}
		}
	}
	cout << "Neuspjesna pretraga! Let ne postoji." << endl;
}


void Kontrolor::otkazivanjeLeta()
{
	string sifra;
	cout << "Unesite sifru leta (6 karaktera): ";
	cin >> sifra;
	cout << endl;

	int indikator = 0;
	vector<string> row;
	string line, word;
	ifstream fin;
	fin.open("raspored.txt", ios::in);
	ofstream temp;
	temp.open("temporary.txt", ios::in);
	while (fin.good())
	{
		row.clear();
		getline(fin, line);
		stringstream str(line);
		while (getline(str, word, ','))
		{

			row.push_back(word);
		}
		if (!row.empty())
		{
			if (row[0] != sifra)
			{
				temp << row[0] << ",";
				temp << row[1] << ",";
				temp << row[2] << ",";
				temp << row[3] << ",";
				temp << row[4] << ",";
				temp << row[5] << ",";
				temp << row[6] << ",";
				temp << row[7] << ",";
				temp << row[8];
				temp << "\n";
			}
			else if (row[0] == sifra)
				indikator = 1;
		}
	}
	fin.clear();
	fin.seekg(0, ios::beg);
	fin.close();
	temp.close();

	if (indikator == 0)
	{
		cout << "Greska! Trazeni let ne postoji." << endl;
		return;
	}
	else
	{
		cout << "Uspjesno ste obrisali let." << endl;
		namespace fs = filesystem;
		fs::path path = filesystem::current_path() / "rezervacije";
		fs::path path1 = filesystem::current_path() / "odobrene rezervacije";
		fs::path path2 = filesystem::current_path() / "otkazane rezervacije";

		for (auto const& entry : fs::directory_iterator(path))
		{
			string filename = entry.path().filename().string();
			string sifra1 = filename.substr(0, 6);
			if(sifra1 == sifra)
				fs::remove(path / (filename));
		}
		for (auto const& entry : fs::directory_iterator(path1))
		{
			string filename = entry.path().filename().string();
			string sifra1 = filename.substr(0, 6);
			if (sifra1 == sifra)
				fs::remove(path1 / (filename));
		}
		for (auto const& entry : fs::directory_iterator(path2))
		{
			string filename = entry.path().filename().string();
			string sifra1 = filename.substr(0, 6);
			if (sifra1 == sifra)
				fs::remove(path2 / (filename));
		}
		cout << "Sve rezervacije za let su izbrisane." << endl;
	}

	zamijeniDatoteke();
}

void Kontrolor::zamijeniDatoteke()
{
	ofstream fin;
	fin.open("raspored.txt", ios::trunc);
	ifstream temp;
	temp.open("temporary.txt", ios::in);

	vector<string> row;
	string line, word;

	while (temp.good())
	{
		row.clear();
		getline(temp, line);
		stringstream str(line);
		while (getline(str, word, ','))
		{
			row.push_back(word);
		}
		if (!row.empty())
		{
			fin << row[0] << ",";
			fin << row[1] << ",";
			fin << row[2] << ",";
			fin << row[3] << ",";
			fin << row[4] << ",";
			fin << row[5] << ",";
			fin << row[6] << ",";
			fin << row[7] << ",";
			fin << row[8];
			fin << "\n";
		}
	}
	fin.close();
	temp.close();

	ofstream deleteContent;
	deleteContent.open("temporary.txt", ios::trunc);
	deleteContent.close();
}