#pragma once
#include <string>
#include "Eveniment.fwd.h"
#include "Utils.h"

class Bilet
{
private:
	const GUID id;

	Eveniment* eveniment;
	unsigned int pret;
	Client* client;

	/* Constructori privati intentionat - dorim sa nu poata sa fie create bilete decat prin clasa Eveniment */
	
	Bilet();
	Bilet(Eveniment& eveniment, Client& client);

public:
	Bilet& operator=(const Bilet& b);

	friend class Eveniment;
};