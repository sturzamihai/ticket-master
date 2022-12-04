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

	/* Getters si Setters*/

	char* getNume();
	std::string getNumeString();
	void setNume(const char* nume);

	int getNrZone();
	Zona getZona(int index);
	Zona operator[](int index);

	void setZone(Zona* zone, int nrZone);
	void adaugareZona(const Zona& z);

	/* Metode */

	int getCapacitateMaxima();
	bool vanzareLoc(int zona, int nrRand, int nrLoc);

	/* Operatori */

	// TODO: verificam daca o locatie a unui eveniment este egala (are ac zone "ocupate") cu o alta locatie pentru blocarea crearii unui eveniment nou in ac perioada
	bool operator==(const Locatie& l);

	friend std::ostream& operator<<(std::ostream&, Locatie);
	friend std::istream& operator>>(std::istream&, Locatie&);
};

