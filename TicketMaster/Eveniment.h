#pragma once
#include <string>

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
	Data data;

public:
	Eveniment(std::string nume, Data data);
};

