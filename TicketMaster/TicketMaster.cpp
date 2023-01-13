#include "TicketMaster.h"
#include "Eveniment.h"

TicketMaster* TicketMaster::tm_ = nullptr;

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
	std::cout << "----- TICKET MASTER (v0.1.2) -----" << std::endl;
	contextClient = nullptr;

	Client contAdmin;
	std::cin >> contAdmin;
	contAdmin.setRolAdmin(true);
	clienti.insert({ contAdmin.getEmail(),contAdmin });

	Locatie a("TEST!!!");
	locatii.push_back(a);
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
		std::cout << "Functie in curs de implementare..." << std::endl;
		start();
	}

	if (comanda == "2")
	{
		std::string emailClient;
		std::string parolaClient;

		std::cout << "Email: ";
		std::cin >> std::ws;
		std::cin >> emailClient;

		std::cout << "Parola: ";
		std::cin >> std::ws;
		std::cin >> parolaClient;

		try {
			Client viitorContext = clienti.at(emailClient);

			if (viitorContext.verificareParola(parolaClient))
			{
				setContextClient(viitorContext);
				start();
			}
			else {
				throw std::exception("Invalid email/pass");
			}
		}
		catch (std::exception e)
		{
			std::cout << "Parola sau email-ul introdus nu este corect. Te rugam reincearca.";
			start();
		}
	}
	
	if (comanda == "3")
	{
		Client context;
		std::cin >> context;
		clienti.insert({ context.getEmail(), context });
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
		deleteContextClient();
		start();
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
	}

	if (comanda == "4")
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

std::vector<Locatie> TicketMaster::getLocatii()
{
	return locatii;
}