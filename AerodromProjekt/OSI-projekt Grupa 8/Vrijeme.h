#pragma once

class Vrijeme
{
private:
	int sat;
	int minut;
public:
	Vrijeme() : sat(0), minut(0)
	{

	}

	Vrijeme(int sat, int minut) : sat(sat), minut(minut)
	{

	}

	friend class Kontrolor;
};