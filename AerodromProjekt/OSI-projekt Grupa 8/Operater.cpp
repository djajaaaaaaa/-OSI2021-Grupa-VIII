#include "Operater.h"

Operater::Operater(string ime, string lozinka) : Korisnik(ime, lozinka, 'O')
{

}

void Operater::spisakRezervacija() const
{
	namespace fs = filesystem;
	fs::path path = filesystem::current_path() / "rezervacije";

	int i = 0;
	for (auto const& entry : fs::directory_iterator(path))
	{
		i++;
		string filename = entry.path().filename().string();
		filename = filename.substr(0, filename.find_last_of("."));
		cout << i << ". " << filename << endl;
	}
}

void Operater::otvaranjeRezervacije(std::vector<Let>& letovi) const
{
	string sifrarez;
	cout << "Unesite sifru rezervacije: ";
	cin >> sifrarez;

	namespace fs = filesystem;
	fs::path path = filesystem::current_path() / "rezervacije";

	string imefajla = sifrarez + ".txt";
	ifstream fin(path / imefajla, ios::in);

	string sifraleta, odakle, gdje, vremena, uzlet, slet, datum;
	if (fin.is_open())
	{
		getline(fin, sifraleta);
		getline(fin, odakle);
		getline(fin, gdje);
		getline(fin, vremena);
		stringstream s(vremena);
		getline(s, uzlet, ',');
		getline(s, slet);
		getline(fin, datum);

		cout << "Sifra leta: " << sifraleta << endl
			<< "Polazak: " << datum << " iz " << odakle << " u " << uzlet << " casova; Dolazak: "
			<< gdje << " u " << slet << " casova" << endl;
		fin.close();
		cout << "Validnost rezervacije:\n";
		for (int i = 0; i < letovi.size(); i++)
		{
			if (letovi[i].getSifra() == sifraleta && letovi[i].getDatum() == datum)
			{
				cout << "Let postoji.\n";
				if (letovi[i].getBrSlobMjesta() == "0")
					cout << "Let nema vise slobodnih mjesta.\n";
				else
				{
					char opcija;
					cout << "Slobodnih mjesta je " << letovi[i].getBrSlobMjesta() << endl;
					cout << "A) Odobri rezervaciju\n" << "B) Otkazi rezervaciju\n" << "C) Prekini\n";
					cin >> opcija;
					if (opcija == 'A')
					{
						odobriRezervaciju(sifrarez);
						return;
					}
					else if (opcija == 'B')
					{
						otkaziRezervaciju(sifrarez);
						return;
					}
					else if (opcija == 'C')
						return;
					else
					{
						cout << "Nepoznata opcija!\n";
						return;
					}
				}
			}
		}
		cout << "Let ne postoji.\n";
	}
	else
	{
		cout << "Rezervacija sa tom sifrom nije nadjena\n";
	}
}

void Operater::odbijeneRezervacije() const
{
	namespace fs = filesystem;
	fs::path path = filesystem::current_path() / "otkazane rezervacije";

	int i = 0;
	for (auto const& entry : fs::directory_iterator(path))
	{
		i++;
		string filename = entry.path().filename().string();
		filename = filename.substr(0, filename.find_last_of("."));
		cout << i << ". " << filename << endl;
	}
}

void Operater::odobreneRezervacije() const
{
	namespace fs = filesystem;
	fs::path path = filesystem::current_path() / "odobrene rezervacije";

	int i = 0;
	for (auto const& entry : fs::directory_iterator(path))
	{
		i++;
		string filename = entry.path().filename().string();
		filename = filename.substr(0, filename.find_last_of("."));
		cout << i << ". " << filename << endl;
	}
}

void  Operater::odobriRezervaciju(string sifrarez) const
{
	namespace fs = filesystem;
	fs::path path = filesystem::current_path();

	filesystem::copy_file(path / "rezervacije" / (sifrarez + ".txt"),
		path / "odobrene rezervacije" / (sifrarez + ".txt"));
	fs::remove(path / "rezervacije" / (sifrarez + ".txt"));
	cout << "Rezervacija odobrena!\n";
}

void  Operater::otkaziRezervaciju(string sifrarez) const
{
	namespace fs = filesystem;
	fs::path path = filesystem::current_path();

	filesystem::copy_file(path / "rezervacije" / (sifrarez + ".txt"),
		path / "otkazane rezervacije" / (sifrarez + ".txt"));
	fs::remove(path / "rezervacije" / (sifrarez + ".txt"));
	cout << "Rezervacija otkazana!\n";
}