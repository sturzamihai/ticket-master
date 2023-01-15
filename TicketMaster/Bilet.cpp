#include "Bilet.h"
#include "Client.h"
#include "Eveniment.h"
#include <iostream>
#include "TicketMaster.h"

Bilet::Bilet()
{
	pret = 0;
	eveniment = nullptr;
	nrZona = -1;
	nrRand = -1;
	nrLoc = -1;
}

Bilet::Bilet(Eveniment& eveniment, int nrZona, int nrRand, int nrLoc, unsigned int pret) : Bilet()
{
	this->eveniment = &eveniment;
	this->pret = pret;
	this->nrZona = nrZona;
	this->nrRand = nrRand;
	this->nrLoc = nrLoc;
}

void Bilet::reinitId(std::string id)
{
	this->id.reinit(id);
}

Bilet::Bilet(const Bilet& b) : id(b.id)
{
	this->pret = b.pret;
	this->eveniment = b.eveniment;
	this->nrRand = b.nrRand;
	this->nrLoc = b.nrLoc;
	this->nrZona = b.nrZona;
}

Bilet& Bilet::operator=(const Bilet& b)
{
	if (this != &b)
	{
		this->pret = b.pret;
		this->eveniment = b.eveniment;
		this->nrRand = b.nrRand;
		this->nrLoc = b.nrLoc;
		this->nrZona = b.nrZona;
	}

	return *this;
}

std::string Bilet::getId()
{
	return (std::string)id;
}

float Bilet::getPret()
{
	return pret;
}

Eveniment Bilet::getEveniment()
{
	return *eveniment;
}

int Bilet::getNrZona()
{
	return nrZona;
}

int Bilet::getNrRand()
{
	return nrRand;
}

int Bilet::getNrLoc()
{
	return nrLoc;
}

void Bilet::serializare(std::ofstream& f)
{
	Utils::serializareString((std::string)id, f);

	f.write((char*)&pret, sizeof(pret));
	f.write((char*)&nrZona, sizeof(nrZona));
	f.write((char*)&nrRand, sizeof(nrRand));
	f.write((char*)&nrLoc, sizeof(nrLoc));
}

void Bilet::deserializare(std::ifstream& f)
{
	std::string idBilet = Utils::deserializareString(f);
	id.reinit(idBilet);

	f.read((char*)&pret, sizeof(pret));
	f.read((char*)&nrZona, sizeof(nrZona));
	f.read((char*)&nrRand, sizeof(nrRand));
	f.read((char*)&nrLoc, sizeof(nrLoc));
}