#pragma once
#include <string>
#include <iostream>
#include "Eveniment.fwd.h"
#include "Utils.h"

class Client
{
private:
	std::string email;
	std::string parola;

	std::string nume;

	bool esteAdmin;

	//int nrBileteCumparate;
	//Bilet* bileteCumparate;

public:
	Client(std::string email, std::string parola);
	Client(std::string email, std::string parola, std::string nume);
	// Client(const Client& c);
	// Client& operator=(const Client& c);

	friend std::ostream& operator<<(std::ostream&, Client);
	friend std::istream& operator>>(std::istream&, Client&);
};