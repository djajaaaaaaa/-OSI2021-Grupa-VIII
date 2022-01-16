#include "Kontrolor.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>
#include <filesystem>
#include "Let.h"

Kontrolor::Kontrolor(string ime, string lozinka, char susp) : Korisnik(ime, lozinka, 'K', susp)
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
	string status = "nijeSletio";

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
	char f = cin.get();
	while (f != '\n')
	{
		opis += f;
		f = cin.get();
	}
	cout << "Vrijeme polaska (format ss:mm):" << endl;
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
		char k = cin.get();
		while (k != '\n')
		{
			opis += k;
			k = cin.get();
		}
	} while (opis.length() > 150);
	cout << "Broj mjesta:" << endl;
	cin >> brojMjesta;
	brojSlobodnihMjesta = brojMjesta;

	Let let1(sifra, odlazak, dolazak, vrijemePolaska, vrijemeDolaska, datum, opis, brojMjesta, brojSlobodnihMjesta, status);
	string odgovor;
	cout << "Potvrdite kreiranje leta: " << endl;
	cout << "A) Da, kreiraj     B) Ne, odustani" << endl;
	cin >> odgovor;
	if (odgovor == "A")
	{
		if (provjeraSifre(let1, letovi) && provjeraVremena(let1, letovi))
		{
			cout << "Uspjesno ste kreirali let." << endl;
			azurirajRaspored(let1);
			return;

		}
		else
		{
			cout << "Raspored je popunjen! Nije moguce kreirati let." << endl;
			return;
		}
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
bool Kontrolor::provjeraSifre(Let& let1, std::vector<Let>& letovi)
{
	string sifra = let1.sifra;
	string datum = let1.datum;
	std::vector<Let>::iterator it1 = std::find_if(letovi.begin(), letovi.end(), [sifra, datum](const Let& let2)
		{
			return ((sifra == let2.sifra) && (datum == let2.datum));
		});
	if (it1 == letovi.end())
	{
		letovi.push_back(let1);
		return true;
	}
	return false;
}

bool Kontrolor::provjeraVremena(Let& let1, std::vector<Let>& letovi)
{
	string datum = let1.datum;
	string odlazak = let1.odlazak;
	string vp = let1.vrijemePolaska;
	string vd = let1.vrijemeDolaska;
	std::vector<Let>::iterator it1 = std::find_if(letovi.begin(), letovi.end(), [datum, odlazak, vp, vd](const Let& let2)
		{
			if (odlazak == "Moskva")
			{
				return((datum == let2.datum) && (vp == let2.vrijemePolaska) && (vp == let2.vrijemeDolaska));
			}
			else
			{
				return((datum == let2.datum) && (vd == let2.vrijemePolaska) && (vd == let2.vrijemeDolaska));
			}
		});
	if (it1 == letovi.end())
	{
		letovi.push_back(let1);
		return true;
	}
	return false;
}

void Kontrolor::azurirajRaspored(const Let& let)
{
	fstream fout;
	fout.open("raspored.txt", ios::out | ios::app);
	fout << let.sifra << ",";
	fout << let.odlazak << ",";
	fout << let.dolazak << ",";
	fout << let.vrijemePolaska << ",";
	fout << let.vrijemeDolaska << ",";
	fout << let.datum << ",";
	fout << let.opis << ",";
	fout << let.brojMjesta << ",";
	fout << let.brojSlobodnihMjesta << ",";
	fout << let.status << "\n";

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


void Kontrolor::informacijeLet(std::vector<Let>& letovi)
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
	else
	{
		cout << "Detalji leta:" << endl;
		cout << "Sifra: " << (*it).sifra << endl;
		cout << "od: " << (*it).odlazak << " do: " << (*it).dolazak << endl;
		cout << "Vrijeme polaska: " << (*it).vrijemePolaska << endl;
		cout << "Vrijeme dolaska: " << (*it).vrijemeDolaska << endl;
		cout << "Datum: " << (*it).datum << endl;
		cout << "Opis: " << (*it).opis << endl;
		cout << "Broj mjesta: " << (*it).brojMjesta << endl;
		cout << "Broj slobodnih mjesta: " << (*it).brojSlobodnihMjesta << endl;
		return;
	}
}


void Kontrolor::otkazivanjeLeta(std::vector<Let>& letovi)
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
	else
	{
		letovi.erase(it);
		cout << "Uspjesno ste obrisali let." << endl;
		promijeniRaspored(letovi);

		namespace fs = filesystem;
		fs::path path = filesystem::current_path() / "rezervacije";
		fs::path path1 = filesystem::current_path() / "odobrene rezervacije";
		fs::path path2 = filesystem::current_path() / "otkazane rezervacije";

		for (auto const& entry : fs::directory_iterator(path))
		{
			string filename = entry.path().filename().string();
			string sifra1 = filename.substr(0, 6);
			if (sifra1 == sifra)
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
}


void Kontrolor::promijeniRaspored(std::vector<Let>& letovi)
{
	fstream fout;
	fout.open("raspored.txt", ios::out);
	for (std::vector<Let>::iterator it = letovi.begin(); it != letovi.end(); ++it)
	{
		fout << (*it).sifra << ",";
		fout << (*it).odlazak << ",";
		fout << (*it).dolazak << ",";
		fout << (*it).vrijemePolaska << ",";
		fout << (*it).vrijemeDolaska << ",";
		fout << (*it).datum << ",";
		fout << (*it).opis << ",";
		fout << (*it).brojMjesta << ",";
		fout << (*it).brojSlobodnihMjesta << ",";
		fout << (*it).status << "\n";
	}
}