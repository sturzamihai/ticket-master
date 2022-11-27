#pragma once
#include <string.h>
#include <iostream>
#include "Zona.h"

class Locatie
{
private:
	char* nume;

	int nrZone;
	Zona* zone;

public:
	Locatie(const char* nume);
	Locatie(const Locatie& l);
	~Locatie();

	void setNume(const char* nume);
	char* getNume();

	friend std::istream& operator>>(std::istream& in, Locatie l);
};

