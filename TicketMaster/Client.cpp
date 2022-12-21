#include "Eveniment.fwd.h"
#include "Client.h"

Client::Client()
{
	nume = "Anonim";
	esteAdmin = false;
}

Client::Client(std::string email, std::string parola) : Client::Client()
{
	this->email = email;
	this->parola = parola; // TODO: ceva hashing function simplu - for the sake of things

	//nrBileteCumparate = 0;
	//bileteCumparate = nullptr;
}

Client::Client(std::string email, std::string parola, std::string nume) : Client(email, parola)
{
	this->nume = nume;
}

std::string Client::getEmail()
{
	return email;
}

bool Client::verificareParola(std::string parolaDeComparat)
{
	return parola == parolaDeComparat;
}

bool Client::getRolAdmin()
{
	return esteAdmin;
}

void Client::setRolAdmin(bool admin)
{
	esteAdmin = admin;
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
	in >> std::ws;
	std::getline(in, c.nume);

	std::cout << "Adresa de email: ";
	in >> std::ws;
	std::getline(in, c.email);

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

	c.parola = parola;

	return in;
}