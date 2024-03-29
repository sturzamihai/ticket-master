#include "Locatie.h"
#include "TicketMaster.h"

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
	if (index >= 0 && index < nrZone)
	{
		return zone[index];
	}

	throw IndexInvalidException();
}

// Returneaza zona de pe pozitia index
Zona Locatie::operator[](int index)
{
	return getZona(index);
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
	if (zone == nullptr) throw VectorNullException();

	if (zona >= 0 && zona < nrZone)
	{
		return zone[zona].vanzareLoc(nrRand, nrLoc);
	}

	throw IndexInvalidException();
}

void Locatie::setPretLocuri(int zona, float pret)
{
	if (zone == nullptr) throw VectorNullException();

	if (zona >= 0 && zona < nrZone)
	{
		zone[zona].setPret(pret);
	}
	else
	{
		throw IndexInvalidException();
	}
}

void Locatie::setPretLocuri(float pret)
{
	if (zone == nullptr || nrZone <= 0) throw VectorNullException();

	for (int i = 0; i < nrZone; i++)
	{
		setPretLocuri(i, pret);
	}
}

bool Locatie::operator==(const Locatie& l)
{
	if (strcmp(nume, l.nume) != 0 || nrZone != l.nrZone)
	{
		return false;
	}

	for (int i = 0; i < nrZone; i++)
	{
		if (l.zone[i].getNume() != zone[i].getNume())
		{
			return false;
		}
	}

	return true;
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
		out << "Locatia nu are zone create" << std::endl;
	}

	return out;
}

std::istream& operator>>(std::istream& in, Locatie& l)
{
	std::cout << "Nume locatie: ";
	in >> std::ws;
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

	TicketMaster* platforma = TicketMaster::getInstanta();
	platforma->adaugareLocatie(l);

	return in;
}

void Locatie::serializare(std::ofstream& f)
{
	Utils::serializareString(nume, f);

	f.write((char*)&nrZone, sizeof(nrZone));
	for (int i = 0; i < nrZone; i++)
	{
		zone[i].serializare(f);
	}
}

void Locatie::deserializare(std::ifstream& f)
{
	short dimNume = 0;
	f.read((char*)&dimNume, sizeof(dimNume));
	
	if (nume != nullptr)
	{
		delete[] nume;
	}

	nume = new char[dimNume + 1];
	f.read(nume, dimNume + 1);

	f.read((char*)&nrZone, sizeof(nrZone));

	if (zone != nullptr) {
		delete[] zone;
	}

	zone = new Zona[nrZone];
	for (int i = 0; i < nrZone; i++)
	{
		zone[i].deserializare(f);
	}
	
}