#pragma once
#include <string>
#include "Eveniment.fwd.h"

class Client
{
private:
	static int nrClient;
	const int id;
	std::string nume;
	Bilet* bileteCumparate;

public:
	Client();
};