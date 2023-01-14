#pragma once
#include <string>
#include "Utils.h"
#include "Serializabil.h"
#include "Locatie.fwd.h"

class Zona : public Serializabil
{
private:
	std::string nume;

	int nrRanduri;
	int nrLocuriPerRand;
	Loc** hartaLocuri;
	float pretPerLoc;

	void deleteHartaLocuri();

public:
	/* Constructori */
	Zona();
	Zona(std::string nume, int nrRanduri, int nrLocuriPerRand, float pretPerLoc);
	Zona(const Zona& z);
	Zona& operator=(const Zona& z);
	~Zona();

	/* Getters */
	std::string getNume();
	float getPret();
	int getNrRanduri();
	int getNrLocuriPerRand();

	/* Setters */
	void setNume(std::string nume);
	void setPret(float pretPerLoc);
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

	/* Serializabil */
	void serializare(std::ofstream& f);
	void deserializare(std::ifstream& f);
};

