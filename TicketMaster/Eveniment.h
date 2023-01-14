#pragma once
#include <string>
#include "Locatie.h"
#include "Eveniment.fwd.h"
#include "Utils.h"
#include "TicketMaster.h"

class Eveniment
{
private:
	std::string nume;
	Locatie locatie;

	//int nrBileteVandute;
	//Bilet* bilete;
	//void setBilete(Bilet* bilete, int nrBilete);
	std::map<std::string, Bilet> bilete;

	Data dataInceput;
	Data dataSfarsit;

public:
	/* Constructori */
	Eveniment();
	Eveniment(std::string nume, Locatie locatie, Data dataInceput, Data dataSfarsit);
	Eveniment(const Eveniment& e);
	Eveniment& operator=(const Eveniment& e);
	~Eveniment();

	/* Getters */
	std::string getNume();
	Locatie getLocatie();
	Data getDataInceput();
	Data getDataSfarsit();

	/* Setters */
	void setNume(std::string nume);
	void setLocatie(Locatie locatie);
	void setData(Data dataInceput, Data dataSfarsit);

	/* Metode */
	bool vanzareBilet(Client& client, int zona, int nrRand, int nrLoc);

	/* Operatori */
	friend std::ostream& operator<<(std::ostream&, Eveniment);
	friend std::istream& operator>>(std::istream&, Eveniment&);
};

