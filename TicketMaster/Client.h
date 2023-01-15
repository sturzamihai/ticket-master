#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Eveniment.fwd.h"
#include "Utils.h"

class Client : Serializabil
{
private:
	std::string email;
	std::string parola;
	std::string nume;

	bool esteAdmin;

	std::vector<Bilet*> bilete;

public:
	/* Constructori */
	Client();
	Client(std::string email, std::string parola);
	Client(std::string email, std::string parola, std::string nume);

	/* Getters */
	std::string getEmail();
	bool getRolAdmin();

	/* Setters */
	void setRolAdmin(bool admin);

	/* Metode */
	bool verificareParola(std::string parolaDeComparat);
	void adaugareBilet(Bilet* bilet);

	/* Operatori */
	friend std::ostream& operator<<(std::ostream&, Client);
	friend std::istream& operator>>(std::istream&, Client&);

	/* Serializabil */
	void serializare(std::ofstream& f);
	void deserializare(std::ifstream& f);
};