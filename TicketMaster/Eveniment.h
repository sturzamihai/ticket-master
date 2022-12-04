#pragma once
#include <string>
#include "Locatie.h"
#include "Eveniment.fwd.h"
#include "Utils.h"

class Eveniment
{
private:
	std::string nume;
	Locatie locatie;

	int nrBileteVandute;
	Bilet* bilete;
	void setBilete(Bilet* bilete, int nrBilete);

	Data dataInceput;
	Data dataSfarsit;

public:
	Eveniment();
	Eveniment(std::string nume, Locatie locatie, Data dataInceput, Data dataSfarsit);
	Eveniment(const Eveniment& e);
	Eveniment& operator=(const Eveniment& e);
	~Eveniment();

	/* Getters & Setters */

	std::string getNume();
	void setNume(std::string nume);

	Locatie getLocatie();
	void setLocatie(Locatie locatie);

	Data getDataInceput();
	Data getDataSfarsit();

	void setData(Data dataInceput, Data dataSfarsit);

	/* Metode */

	bool vanzareBilet(Client& client, int zona, int nrRand, int nrLoc);
};

