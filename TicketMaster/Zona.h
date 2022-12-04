#pragma once
#include <string>
#include "Utils.h"

class Zona
{
private:
	std::string nume;

	int nrRanduri;
	int nrLocuriPerRand;
	Loc** hartaLocuri;

	void deleteHartaLocuri();

public:
	Zona();
	Zona(std::string nume, int nrRanduri, int nrLocuriPerRand);
	Zona(const Zona& z);
	Zona& operator=(const Zona& z);
	~Zona();

	/* Getters si Setters */

	void setNume(std::string nume);
	std::string getNume();

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

