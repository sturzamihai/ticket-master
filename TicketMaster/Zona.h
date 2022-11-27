#pragma once
#include <string>
class Zona
{
private:
	std::string nume;

	int nrRanduri;
	int* nrLocuriPerRand;

public:
	Zona(std::string nume, int nrRanduri, int nrLocuriPerRand);
	Zona(std::string nume, int nrRanduri, int* nrLocuriPerRand);

	void setNume(std::string nume);
	std::string getNume();

	void setNrLocuri(int nrRanduri, int nrLocuriPerRand);
	void setNrLocuri(int nrRanduri, int* nrLocuriPerRand);
	int getNrLocuri();
	int getNrRanduri();
	int* getLocuriPerRand();
	
};

