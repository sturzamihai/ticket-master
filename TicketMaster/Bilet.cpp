#include "Bilet.h"
#include "Client.h"
#include <iostream>

Bilet::Bilet()
{
	pret = 0;
	client = nullptr;
	eveniment = nullptr;
	nrRand = -1;
	nrLoc = -1;
}

Bilet::Bilet(Eveniment& eveniment, Client& client, int nrZona, int nrRand, int nrLoc, unsigned int pret) : Bilet()
{
	this->eveniment = &eveniment;
	this->client = &client;
	this->pret = pret;
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
	this->client = b.client;
	this->nrRand = b.nrRand;
	this->nrLoc = b.nrLoc;
}

//Bilet& Bilet::operator=(const Bilet& b)
//{
//	if (this != &b)
//	{
//		pret = b.pret;
//
//		client = b.client;
//		eveniment = b.eveniment;
//	}
//
//	return *this;
//}

std::string Bilet::getId()
{
	return (std::string)id;
}

void Bilet::serializare(std::ofstream& f)
{
	std::string idBilet = (std::string)id;
	int dimId = idBilet.length();
	f.write((char*)&dimId, sizeof(dimId));
	f.write(idBilet.c_str(), dimId + 1);

	f.write((char*)&pret, sizeof(pret));
	f.write((char*)&nrZona, sizeof(nrZona));
	f.write((char*)&nrRand, sizeof(nrRand));
	f.write((char*)&nrLoc, sizeof(nrLoc));

	std::string emailClient = client->getEmail();
	int dimEmail = emailClient.length();
	f.write((char*)&dimEmail, sizeof(dimEmail));
	f.write(emailClient.c_str(), dimEmail + 1);
}

void Bilet::deserializare(std::ifstream& f)
{
	int dimId = 0;
	f.read((char*)&dimId, sizeof(dimId));
	char* n = new char[dimId + 1];
	f.read(n, dimId + 1);
	id.reinit(n);
	delete[] n;

	f.read((char*)&pret, sizeof(pret));
	f.read((char*)&nrZona, sizeof(nrZona));
	f.read((char*)&nrRand, sizeof(nrRand));
	f.read((char*)&nrLoc, sizeof(nrLoc));

	int dimEmail = 0;
	f.read((char*)&dimEmail, sizeof(dimEmail));
	char* e = new char[dimEmail + 1];
	f.read(e, dimEmail + 1);
	// TODO: get platform to link Bilet & Client
	delete[] e;
}