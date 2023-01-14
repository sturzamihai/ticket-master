#pragma once
#include <string.h>
#include <iostream>
#include "Zona.h"
#include "Serializabil.h"

class Locatie : public Serializabil
{
private:
	char* nume;

	int nrZone;
	Zona* zone;

public:
	/* Constructori */
	Locatie();
	Locatie(const char* nume);
	Locatie(const char* nume, int nrZone, Zona* zone);
	Locatie(const Locatie& l);
	Locatie& operator=(const Locatie& l);
	~Locatie();

	/* Getters*/
	char* getNume();
	std::string getNumeString();
	int getNrZone();
	Zona getZona(int index);

	/* Setters */
	void setNume(const char* nume);
	void setZone(Zona* zone, int nrZone);
	void adaugareZona(const Zona& z);

	/* Metode */
	int getCapacitateMaxima();
	bool vanzareLoc(int zona, int nrRand, int nrLoc);
	void setPretLocuri(int zona, float pret);
	void setPretLocuri(float pret);

	/* Operatori */
	Zona operator[](int index);
	friend std::ostream& operator<<(std::ostream&, Locatie);
	friend std::istream& operator>>(std::istream&, Locatie&);

	/* Serializabil */
	void serializare(std::ofstream& f);
	void deserializare(std::ifstream& f);
};

