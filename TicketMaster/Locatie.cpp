#include "Locatie.h"
#include <iostream>

Locatie::Locatie()
{
	nume = new char[strlen("N/A") + 1];
	strcpy_s(nume, strlen("N/A") + 1, "N/A");

	nrZone = 0;
	zone = nullptr;
}

Locatie::Locatie(const char* nume) : Locatie::Locatie()
{
	if (nume != nullptr)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
	}
}

Locatie::Locatie(const char* nume, int nrZone, Zona* zone) : Locatie::Locatie(nume)
{	
	if (zone != nullptr && nrZone > 0)
	{
		this->nrZone = nrZone;
		this->zone = new Zona[nrZone];
		for (int i = 0; i < nrZone; i++)
		{
			this->zone[i] = zone[i];
		}
	}
}

Locatie::Locatie(const Locatie& l) : Locatie::Locatie(l.nume, l.nrZone, l.zone)
{
	// Silence is golden...
}

Locatie& Locatie::operator=(const Locatie& l)
{
	if (this != &l)
	{
		this->setNume(l.nume);
		this->setZone(l.zone, l.nrZone);
	}

	return *this;
}

Locatie::~Locatie()
{
	if (nume != nullptr)
	{
		delete[] nume;
		nume = nullptr;
	}

	if (zone != nullptr) {
		delete[] zone;
		zone = nullptr;
	}
}

// Returneaza numele locatie
char* Locatie::getNume()
{
	if (nume != nullptr)
	{
		char* copieNume = new char[strlen(nume) + 1];
		strcpy_s(copieNume, strlen(nume) + 1, nume);

		return copieNume;
	}

	return nullptr;
}

// Returneaza numele locatiei ca si string
std::string Locatie::getNumeString()
{
	if (nume != nullptr)
	{
		std::string numeString = nume;
		return numeString;
	}

	return "";
}

// Seteaza numele locatiei
void Locatie::setNume(const char* nume)
{
	if (nume != nullptr) {
		if (this->nume != nullptr)
		{
			delete[] this->nume;
		}

		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
	}
}

// Returneaza numarul de zone
int Locatie::getNrZone()
{
	return nrZone;
}

// Returneaza capacitatea maxima a locatiei
int Locatie::getCapacitateMaxima()
{
	int capacitate = 0;
	if (zone != nullptr)
	{
		for (int i = 0; i < nrZone; i++)
		{
			capacitate += zone[i].getCapacitateMaxima();
		}
	}

	return capacitate;
}

// Returneaza zona de pe pozitia index
Zona Locatie::getZona(int index)
{
	return zone[index];
}

// Returneaza zona de pe pozitia index
Zona Locatie::operator[](int index)
{
	return zone[index];
}

// Seteaza zonele locatiei
void Locatie::setZone(Zona* zone, int nrZone)
{
	if (zone != nullptr && nrZone > 0)
	{
		if (this->zone != nullptr)
		{
			delete[] this->zone;
		}

		this->zone = new Zona[nrZone];
		this->nrZone = nrZone;
		for (int i = 0; i < nrZone; i++)
		{
			this->zone[i] = zone[i];
		}
	}
}

// Adauga o zona noua la capatul vectorului de zone
void Locatie::adaugareZona(const Zona& z)
{
	if (zone != nullptr)
	{
		Zona* copieZone = new Zona[nrZone + 1];
		for (int i = 0; i < nrZone; i++)
			copieZone[i] = zone[i];
		copieZone[nrZone] = z;

		setZone(copieZone, nrZone + 1);
	}
	else {
		Zona* zoneNoi = new Zona[1];
		zoneNoi[0] = z;
		setZone(zoneNoi, 1);
	}
}

bool Locatie::vanzareLoc(int zona, int nrRand, int nrLoc)
{
	if (zona < nrZone)
	{
		return zone[zona].vanzareLoc(nrRand, nrLoc);
	}

	return false;
}

std::ostream& operator<<(std::ostream& out, Locatie l)
{
	out << "Nume locatie:" << l.nume << std::endl;
	if (l.zone != nullptr && l.nrZone > 0)
	{
		out << "Numar zone: " << l.nrZone << std::endl;
		for (int i = 0; i < l.nrZone; i++)
		{
			out << l.zone[i] << std::endl;
		}
	}
	else
	{
		out << "Locatia nu are zone create";
	}

	return out;
}

std::istream& operator>>(std::istream& in, Locatie& l)
{
	std::cout << "Nume locatie: ";
	std::string buffer;
	std::getline(in,buffer);
	l.setNume(buffer.c_str());

	std::cout << "Numar de zone (categorii/sali/etc.): ";
	in >> l.nrZone;

	if (l.zone != nullptr)
	{
		delete[] l.zone;
	}

	l.zone = new Zona[l.nrZone];

	for (int i = 0; i < l.nrZone; i++)
	{
		std::cout << "--- Zona " << i + 1 << " ---" << std::endl;
		in >> l.zone[i];
	}

	return in;
}