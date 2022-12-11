#include "Bilet.h"
#include <iostream>

Bilet::Bilet()
{
	pret = 0;
	client = nullptr;
	eveniment = nullptr;
}

Bilet::Bilet(Eveniment& eveniment, Client& client) : Bilet()
{
	this->eveniment = &eveniment;
	this->client = &client;
}

Bilet& Bilet::operator=(const Bilet& b)
{
	if (this != &b)
	{
		pret = b.pret;

		client = b.client;
		eveniment = b.eveniment;
	}

	return *this;
}