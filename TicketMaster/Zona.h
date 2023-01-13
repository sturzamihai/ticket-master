#pragma once
#include <string>
#include "Utils.h"
#include "Serializabil.h"
#include "Locatie.fwd.h"

class Zona
{
private:
	std::string nume;

	int nrRanduri;
	int nrLocuriPerRand;
	Loc** hartaLocuri;
	float pretPerLoc;

	void deleteHartaLocuri();

public:
	Zona();
	Zona(std::string nume, int nrRanduri, int nrLocuriPerRand, float pretPerLoc);
	Zona(const Zona& z);
	Zona& operator=(const Zona& z);
	~Zona();

	/* Getters si Setters */

	void setNume(std::string nume);
	std::string getNume();

	void setPret(float pretPerLoc);
	float getPret();

	int getNrRanduri();
	int getNrLocuriPerRand();
	
	void setHartaLocuri(Loc** hartaLocuri, int nrRanduri, int nrLocuriPerRand);

	/* Metode */

	void deblocareLoc(int nrRand, int nrLoc);
	void blocareLoc(int nrRand, int nrLoc);
	bool vanzareLoc(int nrRand, int nrLoc);
	int getCapacitateMaxima();

	static Loc** generareHartaLocuri(int nrRanduri, int nrLocuriPerRand);

	/* Operatori */

	friend std::ostream& operator<<(std::ostream&, Zona);
	friend std::istream& operator>>(std::istream&, Zona&);

};

