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
	Locatie();
	Locatie(const char* nume);
	Locatie(const char* nume, int nrZone, Zona* zone);
	Locatie(const Locatie& l);
	Locatie& operator=(const Locatie& l);
	~Locatie();

	char* getNume();
	void setNume(const char* nume);

	int getNrZone();

	Zona getZona(int index);
	Zona operator[](int index);

	void setZone(Zona* zone, int nrZone);
	void adaugareZona(const Zona& z);

	friend std::ostream& operator<<(std::ostream&, Locatie);
	friend std::istream& operator>>(std::istream&, Locatie&);
};

