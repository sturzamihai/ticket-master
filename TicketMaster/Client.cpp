#include "Eveniment.fwd.h"
#include "Client.h"
#include "TicketMaster.h"

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

void Client::adaugareBilet(std::string idBilet)
{
	bilete.push_back(idBilet);
}

bool Client::getRolAdmin()
{
	return esteAdmin;
}

std::string Client::getNume()
{
	return nume;
}

std::vector<std::string> Client::getIdBilete()
{
	return bilete;
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
	std::cout << "Nume client: ";
	in >> std::ws;
	std::getline(in, c.nume);

	std::cout << "Adresa de email: ";
	in >> std::ws;
	std::getline(in, c.email);

	TicketMaster* platforma = TicketMaster::getInstanta();
	while (platforma->esteClientExistent(c.email))
	{
		std::cout << "Adresa de email introdusa deja exista." << std::endl;
		std::cout << "Reintrodu adresa de email: ";
		in >> std::ws;
		std::getline(in, c.email);
	}

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

void Client::serializare(std::ofstream& f)
{
	Utils::serializareString(email, f);
	Utils::serializareString(parola, f);
	Utils::serializareString(nume, f);

	int dimBilete = bilete.size();
	f.write((char*)&dimBilete, sizeof(dimBilete));
	for (int i = 0; i < bilete.size(); i++)
	{
		Utils::serializareString(bilete[i], f);
	}

	f.write((char*)&esteAdmin, sizeof(esteAdmin));
}

void Client::deserializare(std::ifstream& f)
{
	email = Utils::deserializareString(f);
	parola = Utils::deserializareString(f);
	nume = Utils::deserializareString(f);

	int dimBilete = 0;
	bilete.clear();
	f.read((char*)&dimBilete, sizeof(dimBilete));
	for (int i = 0; i < dimBilete; i++)
	{
		std::string idBilet = Utils::deserializareString(f);
		bilete.push_back(idBilet);
	}

	f.read((char*)&esteAdmin, sizeof(esteAdmin));
}