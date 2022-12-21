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
	Client();
	Client(std::string email, std::string parola);
	Client(std::string email, std::string parola, std::string nume);
	// Client(const Client& c);
	// Client& operator=(const Client& c);

	std::string getEmail();
	bool verificareParola(std::string parolaDeComparat);

	bool getRolAdmin();
	void setRolAdmin(bool admin);

	friend std::ostream& operator<<(std::ostream&, Client);
	friend std::istream& operator>>(std::istream&, Client&);
};