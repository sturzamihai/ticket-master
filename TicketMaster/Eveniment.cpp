#include "Eveniment.h"
#include "Bilet.h"
#include "Utils.h"

void Eveniment::reassignareBilete()
{
	for (std::map<std::string, Bilet>::iterator it = bilete.begin(); it != bilete.end(); it++)
	{
		(*it).second.eveniment = this;
	}
}

Eveniment::Eveniment()
{
	nume = "N/A";
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
	bilete = e.bilete;
	reassignareBilete();
}

Eveniment& Eveniment::operator=(const Eveniment& e)
{
	if (this != &e)
	{
		nume = e.nume;
		locatie = e.locatie;
		dataInceput = e.dataInceput;
		dataSfarsit = e.dataSfarsit;
		bilete = e.bilete;
		reassignareBilete();
	}

	return *this;
}

Eveniment::~Eveniment() {}

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

int Eveniment::getNrBileteVandute()
{
	return bilete.size();
}

Bilet Eveniment::getBilet(std::string idBilet)
{
	auto it = bilete.find(idBilet);

	if (it != bilete.end())
	{
		return it->second;
	}

	throw IndexInvalidException();
}

float Eveniment::getSumaBileteVandute()
{
	float sumaBilete = 0;
	for (std::map<std::string, Bilet>::iterator it = bilete.begin(); it != bilete.end(); it++)
	{
		sumaBilete += (*it).second.getPret();
	}

	return sumaBilete;
}

void Eveniment::setData(Data dataInceput, Data dataSfarsit)
{
	this->dataInceput = dataInceput;
	this->dataSfarsit = dataSfarsit;
}


// TODO: maybe returnam biletul (chiar pointer) pentru introducerea in lista clientului?
std::string Eveniment::vanzareBilet(int zona, int nrRand, int nrLoc)
{
	bool succesVanzare = locatie.vanzareLoc(zona, nrRand, nrLoc);

	if (succesVanzare)
	{
		Bilet biletNou(*this, zona, nrRand, nrLoc, locatie.getZona(zona).getPret());
		bilete.insert(make_pair(biletNou.getId(), biletNou));
		return biletNou.getId();
	}

	throw VanzareNereusitaException();
}

std::ostream& operator<<(std::ostream& out, Eveniment e)
{
	out << "--- DETALII EVENIMENT ---" << std::endl;
	out << "Nume eveniment: " << e.nume << std::endl;
	out << e.locatie;
	out << "Data inceput: " << e.dataInceput << std::endl;
	out << "Data sfarsit: " << e.dataSfarsit << std::endl;
	out << "--- PRETURI BILETE ---" << std::endl;

	int nrZone = e.locatie.getNrZone();
	if (nrZone > 0)
	{
		for (int i = 0; i < nrZone; i++)
		{
			std::cout << "Pretul biletului in " << e.locatie.getZona(i).getNume() << ": " << e.locatie.getZona(i).getPret() << std::endl;
		}
	}
	else
	{
		out << "Preturile biletelor inca nu au fost stabilite de organizator.";
	}

	return out;
}

std::istream& operator>>(std::istream& in, Eveniment& e)
{
	std::cout << "--- DETALII ORGANIZATORICE ---" << std::endl;
	std::cout << "Nume eveniment: ";
	in >> std::ws;
	std::getline(in, e.nume);

	TicketMaster* platforma = TicketMaster::getInstanta();
	std::vector<Locatie> locatii = platforma->getLocatii();

	if (!locatii.empty())
	{
		std::cout << "-- Locatii disponibile --" << std::endl;
		for (int i = 0; i < locatii.size(); i++)
		{
			std::cout << i + 1 << ". " << locatii[i].getNumeString() << std::endl;
		}

		int selectie;
		std::cout << "Introdu 0 pentru a crea o locatie noua sau orice numar din fata numelui locatiei pentru folosirea acesteia: ";
		in >> selectie;

		while ((selectie == 0 || (selectie-1) < locatii.size()) == false)
		{
			std::cout << "Comanda introdusa nu este corecta. Reintrodu comanda: ";
			in >> selectie;
		}

		if (selectie == 0)
		{
			in >> e.locatie;
		}
		else {
			e.locatie = locatii[selectie - 1];
		}
	}
	else
	{
		in >> e.locatie;
	}

	std::cout << " - Data inceput -" << std::endl;
	in >> e.dataInceput;
	std::cout << "- Data sfarsit -" << std::endl;
	in >> e.dataSfarsit;

	while (e.dataInceput > e.dataSfarsit)
	{
		std::cout << "Data de finalizare a evenimentului este inainte de data de incepere. Reintrodu data corecta." << std::endl;
		in >> e.dataSfarsit;
	}

	std::cout << "--- PRETURI BILETE ---" << std::endl;
	std::cout << "Doresti sa impui preturi diferite in functie de zona biletului? (y/n)";
	in >> std::ws;
	std::string alegere;
	std::getline(in, alegere);

	while (alegere != "y" && alegere != "n")
	{
		std::cout << "Optiunea selectata nu este valida. Te rugam introduce \"y\" pentru confirmare si \"n\" pentru trecere peste.";
		in >> std::ws;
		std::getline(in, alegere);
	}

	if (alegere == "y") 
	{
		int nrZone = e.locatie.getNrZone();
		for (int i = 0; i < nrZone; i++)
		{
			float pretZona;
			std::cout << "Preturile biletelor in zona " << e.locatie.getZona(i).getNume() << ": ";
			in >> pretZona;

			e.locatie.setPretLocuri(i, pretZona);
		}
	}
	else {
		std::cout << "Pretul general al biletului: ";
		float pretZone;
		in >> pretZone;

		e.locatie.setPretLocuri(pretZone);
	}

	return in;
}


void Eveniment::serializare(std::ofstream& f)
{
	Utils::serializareString(nume, f);

	locatie.serializare(f);

	int dimBilete = bilete.size();
	f.write((char*)&dimBilete, sizeof(dimBilete));
	for (std::map<std::string, Bilet>::iterator it = bilete.begin(); it != bilete.end(); it++)
	{
		(*it).second.serializare(f);
	}

	dataInceput.serializare(f);
	dataSfarsit.serializare(f);
}

void Eveniment::deserializare(std::ifstream& f)
{
	nume = Utils::deserializareString(f);

	locatie.deserializare(f);

	bilete.clear();
	int dimBilete = 0;
	f.read((char*)&dimBilete, sizeof(dimBilete));
	for (int i = 0; i < dimBilete; i++)
	{
		Bilet e;
		e.deserializare(f);
		bilete.insert(make_pair(e.getId(), e));
	}

	dataInceput.deserializare(f);
	dataSfarsit.deserializare(f);
}