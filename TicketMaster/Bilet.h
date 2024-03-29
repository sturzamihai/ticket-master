#pragma once
#include <string>
#include "Eveniment.fwd.h"
#include "Utils.h"
#include "Serializabil.h"

class Bilet : public Serializabil
{
private:
	const Utils::GUID id;

	unsigned int pret;

	int nrZona;
	int nrRand;
	int nrLoc;

	Eveniment* eveniment;

	/* Constructori privati intentionat - dorim sa nu poata sa fie create bilete decat prin clasa Eveniment */
	Bilet();
	Bilet(Eveniment& eveniment, int nrZona, int nrRand, int nrLoc, unsigned int pret);

	void reinitId(std::string id);

public:
	Bilet(const Bilet& b);
	Bilet& operator=(const Bilet& b);
	
	/* Getters*/
	std::string getId();
	float getPret();
	Eveniment getEveniment();
	int getNrZona();
	int getNrRand();
	int getNrLoc();

	/* Operatori */
	friend std::ostream& operator<<(std::ostream& out, const Bilet& b);

	/* Serializabil */
	void serializare(std::ofstream& f);
	void deserializare(std::ifstream& f);

	friend class Eveniment;
};