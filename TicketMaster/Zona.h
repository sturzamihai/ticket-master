#pragma once
#include <string>

struct Loc {
	bool blocat;
	bool vandut;
};

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

	void setNume(std::string nume);
	std::string getNume();

	void setHartaLocuri(Loc** hartaLocuri, int nrRanduri, int nrLocuriPerRand);

	void deblocareLoc(int nrRand, int nrLoc);
	void blocareLoc(int nrRand, int nrLoc);
	// void setNrLocuri(int nrRanduri, int nrLocuriPerRand);
	// int getNrLocuriPerRand();
	// int getNrRanduri();

	friend std::ostream& operator<<(std::ostream&, Zona);
	friend std::istream& operator>>(std::istream&, Zona&);
};

