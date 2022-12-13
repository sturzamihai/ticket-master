#include "TicketMaster.h"

TicketMaster::TicketMaster()
{
	std::cout << "----- TICKET MASTER (v0.1.0) -----" << std::endl;
	nrEvenimente = 0;
	evenimente = nullptr;
	contextClient = nullptr;
}

void TicketMaster::setEvenimente(Eveniment* evenimente, int nrEvenimente)
{
	if (evenimente != nullptr && nrEvenimente > 0)
	{
		if (this->evenimente != nullptr)
		{
			delete[] this->evenimente;
		}
		
		this->evenimente = new Eveniment[nrEvenimente];
		this->nrEvenimente = nrEvenimente;
		for (int i = 0; i < nrEvenimente; i++)
		{
			this->evenimente[i] = evenimente[i];
		}
	}
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
	std::getline(std::cin, comanda);

	if(comanda != "1" && comanda != "2" && comanda != "3")
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
		Client context("N/A", "N/A");
		std::cin >> context;
		setContextClient(context);
		start();
	}
}

void TicketMaster::comenziAutentificat()
{
	std::cout << "1. Lista evenimente" << std::endl;
	std::cout << "2. Contul meu" << std::endl;
	std::cout << "3. Log out" << std::endl;

	std::string comanda;
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
		deleteContextClient();
		start();
	}
}

void TicketMaster::start()
{
	std::cout << "-> Meniu <-" << std::endl;

	if (contextClient == nullptr)
	{
		comenziNeautentificat();
	}
	else
	{
		comenziAutentificat();
	}
}

void TicketMaster::adaugareEveniment(Eveniment e)
{
	if (evenimente != nullptr && nrEvenimente > 0)
	{
		Eveniment* copieEvenimente = new Eveniment[nrEvenimente + 1];
		for (int i = 0; i < nrEvenimente; i++)
		{
			copieEvenimente[i] = evenimente[i];
		}
		copieEvenimente[nrEvenimente] = e;

		setEvenimente(copieEvenimente, nrEvenimente + 1);
	}
	else
	{
		Eveniment* copieEvenimente = new Eveniment[nrEvenimente];
		copieEvenimente[0] = e;

		setEvenimente(copieEvenimente, 1);
	}
}