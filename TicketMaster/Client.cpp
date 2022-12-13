#include "Eveniment.fwd.h"
#include "Client.h"

Client::Client(std::string email, std::string parola)
{
	this->email = email;
	this->parola = parola; // TODO: ceva hashing function simplu - for the sake of things
	nume = "N/A";
	esteAdmin = false;

	//nrBileteCumparate = 0;
	//bileteCumparate = nullptr;
}

Client::Client(std::string email, std::string parola, std::string nume) : Client(email, parola)
{
	this->nume = nume;
}

std::ostream& operator<<(std::ostream& out, Client c)
{
	out << "Nume client: " << c.nume;
	return out;
}

std::istream& operator>>(std::istream& in, Client& c)
{
	std::cout << "--- CREARE CONT ---" << std::endl;

	std::cout << "Nume client: ";
	std::string numeClient;
	in >> std::ws;
	std::getline(in, numeClient);

	std::cout << "Adresa de email: ";
	std::string adresaEmail;
	in >> std::ws;
	std::getline(in, adresaEmail);

	std::cout << "Parola: ";
	std::string parola = Utils::citireConsolaParola(in);
	std::cout << "Repetare parola: ";
	std::string repetaParola = Utils::citireConsolaParola(in);

	while (parola != repetaParola)
	{
		std::cout << "Parolele introduse nu coincid. Reincearca." << std::endl;
		std::cout << "Parola: ";
		parola = Utils::citireConsolaParola(in);
		std::cout << "Repetare parola: ";
		repetaParola = Utils::citireConsolaParola(in);
	}

	return in;
}