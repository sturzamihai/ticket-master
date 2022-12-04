#include "Bilet.h"
#include <iostream>

Bilet::Bilet() : id("N/A")
{
	pret = 0;
	client = nullptr;
	eveniment = nullptr;
}

Bilet::Bilet(std::string id, Eveniment& eveniment, Client& client) : id(id)
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