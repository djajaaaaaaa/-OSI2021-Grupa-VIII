#include "Administrator.h"
#include <iostream>

Administrator::Administrator(string ime, string lozinka) : Korisnik(ime, lozinka, 'A')
{

}


void Administrator::kreirajNalog()
{
	fstream fin;
	fin.open("korisnici.dat", ios::in);

	string ime;char ime1[21];string lozinka;char lozinka1[21];
	char tip1;

	std::cout << "Korisnicko ime: ";
	std::cin >> ime;
	std::cout << "Lozinka: ";
	std::cin >> lozinka;
	std::cout << "Tip naloga: ";
	std::cin >> tip1;

	try
	{
		dozvoljenoDodavanje(ime, tip1);
	}
	catch (const std::exception& e) 
	{
		std::cout << e.what() << std::endl;
	}
	
	Korisnik novi(ime, lozinka, tip1);
	novi.upisiuFajl(fin);
	
}

void Administrator::dozvoljenoDodavanje(string username, char tip)
{
	int countS = 0, countA = 0;
	string ime;char ime1[21];string lozinka;char lozinka1[21];
	char tip1;
	fstream fin;
	fin.open("korisnici.dat", ios::in);

	while (!fin.eof())
	{
		fin.read((char*)ime1, sizeof(char[21]));
		fin.read((char*)lozinka1, sizeof(char[21]));
		fin.read(&tip1, sizeof(char));
		if (ime1 == username)
			throw std::exception("Korisnicko ime vec postoji!"); // druga vrsta exceptiona, definisati
		if (tip1 == 'S')
			countS++;
		else if (tip1 == 'A')
			countA++;
	}

	if (tip == 'S')
	{
		if (countS == 3)
			throw std::exception("Prekoracen broj naloga!");
	}
	else if (tip == 'A')
	{
		if (countA == 2)
			throw std::exception("Prekoracen broj naloga!");
	}
}

void Administrator::obrisiNalog()
{
	string ime;
	std::cout << "Unesi korisnicko ime: ";
	std::cin >> ime;

	char ime1[21] = {};
	char c; int i;
	ifstream file;
	ofstream temp;
	file.open("korisnici.dat", ios::binary || ios::in);
	temp.open("temp.dat", ios::binary || ios::app);
	while (!file.eof())
	{
		file.get(c);
		while (c != ',')
		{
			i = 0;
			ime1[i++] = c;
			file.get(c);
		}
		ime1[i] = '\0';

		if (ime == ime1)
		{
			std::cout << "Korisnik pronadjen!";
			obrisiLinijuIzDatoteke(file, temp);
			remove("korisnici.dat");
			rename("temp.dat", "korisnici.dat");
		}
		else
		{
			while (c != '\n') // c je u prvoj iteraciji zarez
				file.get(c);
			file.get(c);
		}

	}

	string tmp;
	tmp = ime1;
	if (tmp.empty() == true)
		std::cout << "Korisnik nije pronadjen u bazi podataka!";

}


void obrisiLinijuIzDatoteke(std::istream& from, std::ostream& to)
{
	// kopiraju se do sad procitani bajtovi u drugu datoteku
	std::copy_n(std::istreambuf_iterator<char>(from), from.gcount(), std::ostreambuf_iterator<char>(to));
	char c;
	from.get(c);
	while (c != '\n') // ucitati sve do kraja reda da se dodje u sljedeci
		from.get(c); // ucitava 

	// dosao je do newline karaktera
	from.get(c);
	// dosao je do reda poslije ovog kojeg treba obrisati, sada sve do kraja datoteke upisuje u drugu
	while (!from.eof())
	{
		from.get(c);
		to.put(c);
	}
}

void Administrator::suspenzijaNaloga()
{
	char flag;
	do
	{
		std::cout << "Suspenzija ili ukidanje suspenzije?(1/0)";
		std::cin >> flag;
	} while (flag != 1 && flag != 0);

	string ime;
	std::cout << "Unesi korisnicko ime naloga: ";
	std::cin >> ime;

	// dupliranje koda??
	char ime1[21] = {};
	char c; int i;
	ifstream file;
	ofstream temp;
	file.open("korisnici.dat", ios::binary || ios::in);
	temp.open("temp.dat", ios::binary || ios::app);
	while (!file.eof())
	{
		file.get(c);
		while (c != ',')
		{
			i = 0;
			ime1[i++] = c;
			file.get(c);
		}
		ime1[i] = '\0';

		if (ime == ime1)
		{
			std::cout << "Korisnik pronadjen!"; // doci do zadnjeg bajta u redu, dodati bajt i kopirati ostatak
			/*file.get(c); // zarez poslije username-a
			while (c != ',')
			{
				i = 0;
				ime1[i++] = c;
				file.get(c);
			}
			file.get(c); // zarez
			while (c != ',')
			{
				i = 0;
				ime1[i++] = c;
				file.get(c);
			}
			file.get(c);*/
			remove("korisnici.dat");
			rename("temp.dat", "korisnici.dat");
		}
		else
		{
			while (c != '\n') // c je u prvoj iteraciji zarez
				file.get(c);
			file.get(c);
		}

	}

}