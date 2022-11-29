#pragma once
#include <string>
#include "Locatie.h"
#include "Bilet.h"

struct Data {
	int zi;
	int luna;
	int an;

	int ora;
	int minut;
};

class Eveniment
{
private:
	std::string nume;
	Locatie locatie;
	Bilet* bilete;

	Data dataInceput;
	Data dataSfarsit;

public:
	Eveniment(std::string nume, Data data);
};

