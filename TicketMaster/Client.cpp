#include "Eveniment.fwd.h"
#include "Client.h"

Client::Client(std::string email, std::string parola) : email(email)
{
	this->parola = parola; // TODO: ceva hashing function simplu - for the sake of things
	nume = "N/A";

	nrBileteCumparate = 0;
	bileteCumparate = nullptr;
}

Client::Client(std::string email, std::string parola, std::string nume) : Client(email, parola)
{
	this->nume = nume;
}