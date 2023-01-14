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

	int nrRand;
	int nrLoc;

	Eveniment* eveniment;
	Client* client;

	/* Constructori privati intentionat - dorim sa nu poata sa fie create bilete decat prin clasa Eveniment */
	Bilet();
	Bilet(Eveniment& eveniment, Client& client, int nrRand, int nrLoc, unsigned int pret);

	void reinitId(std::string id);

public:
	Bilet(const Bilet& b);
	Bilet& operator=(const Bilet& b) = delete;
	
	/* Getters*/
	std::string getId();

	/* Serializabil */
	void serializare(std::ofstream& f);
	void deserializare(std::ifstream& f);

	friend class Eveniment;
};