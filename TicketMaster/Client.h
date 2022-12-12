#pragma once
#include <string>
#include "Eveniment.fwd.h"

class Client
{
private:
	const std::string email;
	std::string parola;

	std::string nume;

	int nrBileteCumparate;
	Bilet* bileteCumparate;

public:
	Client(std::string email, std::string parola);
	Client(std::string email, std::string parola, std::string nume);
	// Client(const Client& c); TODO
	// Client& operator=(const Client& c); TODO
};