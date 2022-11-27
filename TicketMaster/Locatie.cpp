#include "Locatie.h"

Locatie::Locatie(const char* nume)
{
	if (nume != nullptr)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
	}

	zone = nullptr;
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

std::istream& operator>>(std::istream& in, Locatie l)
{
	std::cout << "Nume locatie: ";
	std::string buffer;
	std::getline(in,buffer);
	l.setNume(buffer.c_str());

	std::cout << "Numar de zone (categorii/sali/etc.): ";
	in >> l.nrZone;
	for (int i = 0; i < l.nrZone; i++)
	{
		std::cout << "--- Zona " << i + 1 << " ---" << std::endl;
	}
}