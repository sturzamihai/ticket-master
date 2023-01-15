#include "TicketMaster.h"
#include "Eveniment.h"
#include <iostream>
#include <fstream>
#include <iomanip>

TicketMaster* TicketMaster::tm_ = nullptr;

void TicketMaster::logare()
{
	system("CLS");

	std::cout << "===================" << std::endl;
	std::cout << "-> Autentificare <-" << std::endl;
	std::cout << "===================" << std::endl;

	std::string emailClient;
	std::cout << "Adresa de email: ";
	std::cin >> std::ws;
	std::getline(std::cin, emailClient);

	std::cout << "Parola: ";
	std::string parolaClient = Utils::citireConsolaParola(std::cin);

	std::map<std::string, Client>::iterator it = clienti.find(emailClient);

	if (it != clienti.end() && (*it).second.verificareParola(parolaClient))
	{
		contextClient = &((*it).second);
		std::cout << "Autentificare cu succes." << std::endl;
	}
	else
	{
		std::cout << "Adresa de email sau parola introdusa nu este corecta." << std::endl;
	}

	system("pause");
	start();
}

void TicketMaster::delogare()
{
	contextClient = nullptr;
}

void TicketMaster::creareCont(bool esteAdmin = false)
{
	system("CLS");

	if (esteAdmin)
	{
		std::cout << "===============================" << std::endl;
		std::cout << "-> Creare cont administrator <-" << std::endl;
		std::cout << "===============================" << std::endl;
	}
	else
	{
		std::cout << "=================" << std::endl;
		std::cout << "-> Creare cont <-" << std::endl;
		std::cout << "=================" << std::endl;
	}

	Client contNou;
	std::cin >> contNou;
	contNou.setRolAdmin(esteAdmin);
	clienti.insert({ contNou.getEmail(), contNou});
	salvarePlatforma();
	
	std::cout << "Cont creat cu success." << std::endl;
	system("pause");

	start();
}

void TicketMaster::salvarePlatforma()
{
	std::ofstream fClienti("clienti.bin", std::ios::binary);
	int dimClienti = clienti.size();
	fClienti.write((char*)&dimClienti, sizeof(dimClienti));
	for (std::map<std::string, Client>::iterator it = clienti.begin(); it != clienti.end(); it++)
	{
		(*it).second.serializare(fClienti);
	}
	fClienti.close();

	std::ofstream fEvenimente("evenimente.bin", std::ios::binary);
	int dimEvenimente = evenimente.size();
	fEvenimente.write((char*)&dimEvenimente, sizeof(dimEvenimente));
	for (int i = 0; i < dimEvenimente; i++)
	{
		evenimente[i].serializare(fEvenimente);
	}
	fEvenimente.close();
}

void TicketMaster::restaurarePlatforma()
{
	std::ifstream fClienti("clienti.bin", std::ios::binary);
	int dimClienti = 0;
	fClienti.read((char*)&dimClienti, sizeof(dimClienti));
	for (int i = 0; i < dimClienti; i++)
	{
		Client c;
		c.deserializare(fClienti);
		clienti.insert(make_pair(c.getEmail(), c));
	}
	fClienti.close();

	std::ifstream fEvenimente("evenimente.bin", std::ios::binary);
	int dimEvenimente = 0;
	fEvenimente.read((char*)&dimEvenimente, sizeof(dimEvenimente));
	for (int i = 0; i < dimEvenimente; i++)
	{
		Eveniment e;
		e.deserializare(fEvenimente);
		evenimente.push_back(e);
	}
	fEvenimente.close();
}

TicketMaster* TicketMaster::getInstanta()
{
	if (tm_ == nullptr)
	{
		tm_ = new TicketMaster();
	}

	return tm_;
}

TicketMaster::TicketMaster()
{
	std::cout << "TICKET MASTER (v0.1.2)" << std::endl;
	contextClient = nullptr;
	restaurarePlatforma();
}

void TicketMaster::setEvenimente(std::vector<Eveniment> evenimente)
{
	this->evenimente = evenimente;
}

void TicketMaster::setLocatii(std::vector<Locatie> locatii)
{
	this->locatii = locatii;
}

void TicketMaster::setContextClient(const Client& c)
{
	contextClient = new Client(c);
}

void TicketMaster::deleteContextClient()
{
	delete contextClient;
	contextClient = nullptr;
}

void TicketMaster::comenziNeautentificat()
{
	std::cout << "1. Lista evenimente" << std::endl;
	std::cout << "2. Autentificare" << std::endl;
	std::cout << "3. Inregistrare" << std::endl;

	std::string comanda;
	std::cin >> std::ws;
	std::getline(std::cin, comanda);

	if(comanda != "1" && comanda != "2" && comanda != "3")
	{
		std::cout << "Comanda este invalida. Te rugam sa reincerci." << std::endl;
		start();
	}

	if (comanda == "1")
	{
		std::cout << "--- Evenimente ---" << std::endl;
		if (evenimente.empty())
		{
			std::cout << "Nu exista evenimente create." << std::endl;
		}

		for (int i = 0; i < evenimente.size(); i++)
		{
			std::cout << std::setw(3) << i + 1 << ". ";
			std::cout << evenimente[i].getNume() << std::endl;

			std::cout << std::setw(3) << "";
			std::cout << "Locatie: " << evenimente[i].getLocatie().getNumeString() << std::endl;
		}
		start();
	}

	if (comanda == "2")
	{
		logare();
	}
	
	if (comanda == "3")
	{
		creareCont();
	}
}

void TicketMaster::comenziAutentificat()
{
	std::cout << "1. Lista evenimente" << std::endl;
	std::cout << "2. Contul meu" << std::endl;
	std::cout << "3. Log out" << std::endl;

	std::string comanda;
	std::cin >> std::ws;
	std::getline(std::cin, comanda);

	if (comanda != "1" && comanda != "2" && comanda != "3")
	{
		std::cout << "Comanda este invalida. Te rugam sa reincerci." << std::endl;
		start();
	}

	if (comanda == "1" || comanda == "2")
	{
		std::cout << "Functie in curs de implementare..." << std::endl;
		start();
	}

	if (comanda == "3")
	{
		delogare();
	}
}

void TicketMaster::comenziAdmin()
{
	std::cout << "1. Lista evenimente" << std::endl;
	std::cout << "2. Adaugare eveniment" << std::endl;
	std::cout << "3. Contul meu" << std::endl;
	std::cout << "4. Log out" << std::endl;

	std::string comanda;
	std::cin >> std::ws;
	std::getline(std::cin, comanda);

	if (comanda != "1" && comanda != "2" && comanda != "3" && comanda != "4")
	{
		std::cout << "Comanda este invalida. Te rugam sa reincerci." << std::endl;
		start();
	}

	if (comanda == "1" || comanda == "3")
	{
		std::cout << "Functie in curs de implementare..." << std::endl;
		start();
	}

	if (comanda == "2")
	{
		Eveniment e;
		std::cin >> e;
		adaugareEveniment(e);
		start();
	}

	if (comanda == "4")
	{
		delogare();
	}
}

void TicketMaster::start()
{
	if (clienti.empty())
	{
		creareCont(true);
	}

	system("CLS");

	std::cout << "===========" << std::endl;
	std::cout << "-> Meniu <-" << std::endl;
	std::cout << "===========" << std::endl;

	if (contextClient == nullptr)
	{
		comenziNeautentificat();
	}
	else
	{
		if (contextClient->getRolAdmin()) comenziAdmin();
		else comenziAutentificat();
	}
}

void TicketMaster::adaugareEveniment(Eveniment e)
{
	evenimente.push_back(e);
}

void TicketMaster::adaugareLocatie(Locatie e)
{
	locatii.push_back(e);
}

bool TicketMaster::esteClientExistent(std::string email)
{
	return clienti.find(email) != clienti.end();
}

std::vector<Locatie> TicketMaster::getLocatii()
{
	return locatii;
}

Client TicketMaster::getClient(std::string email)
{
	if (esteClientExistent(email))
	{
		return clienti.at(email);
	}

	throw IndexInvalidException();
}
