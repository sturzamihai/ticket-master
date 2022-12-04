#pragma once
#include <string>
#include "Eveniment.fwd.h"

class Bilet
{
private:
	const std::string id;
	Eveniment* eveniment;
	unsigned int pret;
	Client* client;

	/* Constructori privati intentionat - dorim sa nu poata sa fie create bilete decat prin clasa Eveniment */
	
	Bilet();
	Bilet(std::string id, Eveniment& eveniment, Client& client);

public:
	Bilet& operator=(const Bilet& b);

	friend class Eveniment;
};