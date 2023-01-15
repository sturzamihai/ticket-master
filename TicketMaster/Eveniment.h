#pragma once
#include <string>
#include "Locatie.h"
#include "Eveniment.fwd.h"
#include "Utils.h"
#include "TicketMaster.h"

class Eveniment : Serializabil
{
private:
	std::string nume;
	Locatie locatie;

	//int nrBileteVandute;
	//Bilet* bilete;
	//void setBilete(Bilet* bilete, int nrBilete);
	std::map<std::string, Bilet> bilete;
	void reassignareBilete();

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
	int getNrBileteVandute();
	Bilet getBilet(std::string idBilet);

	/* Setters */
	void setNume(std::string nume);
	void setLocatie(Locatie locatie);
	void setData(Data dataInceput, Data dataSfarsit);

	/* Metode */
	std::string vanzareBilet(int zona, int nrRand, int nrLoc);
	float getSumaBileteVandute();

	/* Operatori */
	friend std::ostream& operator<<(std::ostream&, Eveniment);
	friend std::istream& operator>>(std::istream&, Eveniment&);

	/* Serializabil */
	void serializare(std::ofstream& f);
	void deserializare(std::ifstream& f);
};

