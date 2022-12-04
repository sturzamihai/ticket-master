#include "Eveniment.h"
#include "Bilet.h"

Eveniment::Eveniment()
{
	nume = "N/A";

	locatie = *(new Locatie());

	nrBileteVandute = 0;
	bilete = nullptr;

	Data dataInitiala{ 1,1,2000,0,0 };
	dataInceput = dataInitiala;
	dataSfarsit = dataInitiala;
}

Eveniment::Eveniment(std::string nume, Locatie locatie, Data dataInceput, Data dataSfarsit) : Eveniment::Eveniment()
{
	this->nume = nume;
	this->locatie = locatie;
	this->dataInceput = dataInceput;
	this->dataSfarsit = dataSfarsit;
}

Eveniment::Eveniment(const Eveniment& e) : Eveniment::Eveniment(e.nume, e.locatie, e.dataInceput, e.dataSfarsit)
{
	if (e.bilete != nullptr && e.nrBileteVandute)
	{
		nrBileteVandute = e.nrBileteVandute;
		bilete = new Bilet[e.nrBileteVandute];

		for (int i = 0; i < nrBileteVandute; i++)
		{
			bilete[i] = e.bilete[i];
		}
	}
}

Eveniment& Eveniment::operator=(const Eveniment& e)
{
	if (this != &e)
	{
		// TODO
	}

	return *this;
}

void Eveniment::setBilete(Bilet* bilete, int nrBileteVandute)
{
	if (bilete != nullptr && nrBileteVandute > 0)
	{
		this->nrBileteVandute = nrBileteVandute;

		if (this->bilete != nullptr)
			delete[] this->bilete;

		this->bilete = new Bilet[nrBileteVandute];
		for (int i = 0; i < nrBileteVandute; i++)
			this->bilete[i] = bilete[i];
	}
}

std::string Eveniment::getNume()
{
	return nume;
}

void Eveniment::setNume(std::string nume)
{
	this->nume = nume;
}

Locatie Eveniment::getLocatie()
{
	return locatie;
}

void Eveniment::setLocatie(Locatie locatie)
{
	this->locatie = locatie;
}

Data Eveniment::getDataInceput()
{
	return dataInceput;
}

Data Eveniment::getDataSfarsit()
{
	return dataSfarsit;
}

void Eveniment::setData(Data dataInceput, Data dataSfarsit)
{
	this->dataInceput = dataInceput;
	this->dataSfarsit = dataSfarsit;
}


// TODO: maybe returnam biletul (chiar pointer) pentru introducerea in lista clientului?
bool Eveniment::vanzareBilet(Client& client, int zona, int nrRand, int nrLoc)
{
	bool succesVanzare = locatie.vanzareLoc(zona, nrRand, nrLoc);

	if (succesVanzare)
	{
		Bilet biletNou("TODO: GENERATOR ID", *this, client);

		if (bilete != nullptr)
		{
			Bilet* copieBilete = new Bilet[nrBileteVandute + 1];
			for (int i = 0; i < nrBileteVandute; i++)
				copieBilete[i] = bilete[i];

			copieBilete[nrBileteVandute] = biletNou;
			setBilete(copieBilete, nrBileteVandute + 1);
		}
		else {
			Bilet* copieBilete = new Bilet[1];
			copieBilete[0] = biletNou;
			setBilete(copieBilete, 1);
		}
	}

	return false;
}