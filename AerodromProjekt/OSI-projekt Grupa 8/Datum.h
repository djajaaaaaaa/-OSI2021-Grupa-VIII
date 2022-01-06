#pragma once

class Datum
{
private:
	int dan;
	int mjesec;
	int godina;
public:
	Datum() : dan(1), mjesec(1), godina(2000)
	{

	}

	Datum(int dan, int mjesec, int godina) : dan(dan), mjesec(mjesec), godina(godina)
	{

	}

	friend class Kontrolor;
};