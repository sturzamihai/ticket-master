#include "TicketMaster.h"
#include "Eveniment.h"
#include "Bilet.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

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

void TicketMaster::vizualizareCont()
{
	system("CLS");

	std::cout << "================" << std::endl;
	std::cout << "-> Contul meu <-" << std::endl;
	std::cout << "================" << std::endl;

	if (contextClient->getNume() != "N/A")
	{
		std::cout << "Bine ai venit, " << contextClient->getNume() << std::endl;
	}

	std::cout << "Biletele tale la evenimente sunt: " << std::endl;

	std::vector<std::string> bileteClient = contextClient->getIdBilete();
	for (int i = 0; i < bileteClient.size(); i++)
	{
		try
		{
			Bilet b = cautareBilet(bileteClient[i]);
			std::cout << i + 1 << ". \tBilet la: " << b.getEveniment().getNume() << std::endl;
			std::cout << "\tData: " << b.getEveniment().getDataInceput() << " - " << b.getEveniment().getDataSfarsit() << std::endl;
			std::cout << "\tZona: " << b.getEveniment().getLocatie().getZona(b.getNrZona()).getNume() << std::endl;
			std::cout << "\tRandul: " << b.getNrRand() << ", Loc: " << b.getNrLoc() << std::endl;
		}
		catch (IndexInvalidException err)
		{
			std::cout << i + 1 << ". A aparut o eroare la incarcarea datelor despre eveniment" << std::endl;
		}
	}

	int selectie;
	std::cout << "Introdu numarul din dreptul biletului dorit pentru Check-In sau 0 pentru reintoarcerea la meniu: ";
	std::cin >> selectie;

	while ((selectie == 0 || (selectie - 1) < bileteClient.size()) == false)
	{
		std::cout << "Comanda introdusa nu este corecta." << std::endl;
		std::cout << "Reintrodu comanda: ";
		std::cin >> selectie;
	}

	if (selectie != 0)
	{
		system("CLS");
		try {
			Bilet b = cautareBilet(bileteClient[selectie - 1]);
			std::cout << "==== COD BILET ====" << std::endl;
			std::cout << b.getId() << std::endl;
		}
		catch (IndexInvalidException err)
		{
			std::cout << "A aparut o eroare la afisarea codului biletului. Te rugam reincearca.";
		}
	}

	system("PAUSE");
	start();
}

void TicketMaster::afisareEvenimente()
{
	system("CLS");

	std::cout << "================" << std::endl;
	std::cout << "-> Evenimente <-" << std::endl;
	std::cout << "================" << std::endl;

	if (evenimente.empty())
	{
		std::cout << "Nu exista evenimente create." << std::endl;
	}
	else
	{
		for (int i = 0; i < evenimente.size(); i++)
		{
			std::cout << i + 1 << ". ";
			std::cout << "\t" << evenimente[i].getNume() << std::endl;

			std::cout << "\tLocatie: " << evenimente[i].getLocatie().getNumeString() << std::endl;
			std::cout << "\tData: "
				<< evenimente[i].getDataInceput() << " - " << evenimente[i].getDataSfarsit()
				<< std::endl;
		}

		int selectie;
		std::cout << "Introdu numarul din dreptul evenimentului dorit sau 0 pentru reintoarcerea la meniu: ";
		std::cin >> selectie;

		while ((selectie == 0 || (selectie-1) < evenimente.size()) == false)
		{
			std::cout << "Comanda introdusa nu este corecta." << std::endl;
			std::cout << "Reintrodu comanda: ";
			std::cin >> selectie;
		}

		if (selectie != 0)
		{
			afisareEveniment(selectie-1);
		}
	}

	system("PAUSE");
	start();
}

void TicketMaster::afisareEveniment(int pozEveniment)
{
	system("CLS");

	if (pozEveniment >= 0 && pozEveniment < evenimente.size())
	{
		std::cout << evenimente[pozEveniment] << std::endl;

		if (contextClient)
		{
			std::cout << "Comenzi disponibile: " << std::endl;
			std::cout << "1. Cumparare bilet" << std::endl;
			if (contextClient->getRolAdmin())
			{
				std::cout << "2. Vezi vanzari eveniment" << std::endl;
			}

			int selectie;
			std::cout << "Introdu comanda dorita sau 0 pentru reintoarcerea la meniu: ";
			std::cin >> selectie;

			if (selectie == 1)
			{
				cumparareBiletEveniment(pozEveniment);
			}
			else if (selectie == 2 && contextClient->getRolAdmin())
			{
				statisticiEveniment(pozEveniment);
			}
			else if (selectie == 0)
			{
				afisareEvenimente();
			}
			else
			{
				std::cout << "Comanda selectata este invalida. Te rugam reincearca." << std::endl;
				afisareEveniment(pozEveniment);
			}
		}
		else {
			std::cout << "Pentru a cumpara un bilet te rugam sa te autentifici." << std::endl;
		}
	}

	system("PAUSE");
	afisareEvenimente();
}

void TicketMaster::cumparareBiletEveniment(int pozEveniment)
{
	if (pozEveniment >= 0 && pozEveniment < evenimente.size())
	{
		std::cout << std::endl << "--- Cumparare bilet ---" << std::endl;
		std::cout << "Zone disponibile: " << std::endl;

		int nrZone = evenimente[pozEveniment].getLocatie().getNrZone();
		for (int i = 0; i < nrZone; i++)
		{
			std::cout << i + 1 << ". " << evenimente[pozEveniment].getLocatie().getZona(i).getNume()
				<< " (Pret: " << evenimente[pozEveniment].getLocatie().getZona(i).getPret() << " LEI)" << std::endl;
		}

		std::cout << "Introdu zona dorita: ";
		int zona;
		std::cin >> zona;
		while (zona <= 0 && zona >= nrZone)
		{
			std::cout << "Zona nu exista." << std::endl;
			std::cout << "Introdu zona dorita: ";
			std::cin >> zona;
		}

		Zona zonaSelectata = evenimente[pozEveniment].getLocatie().getZona(zona - 1);
		std::cout << zonaSelectata;

		int nrRanduri = zonaSelectata.getNrRanduri();
		int nrLocuriMax = zonaSelectata.getNrLocuriPerRand();

		int nrRand, nrLoc;
		std::cout << "Introdu numarul randului (axa din stanga): ";
		std::cin >> nrRand;
		std::cout << "Introdu numarul locului (axa de deasupra): ";
		std::cin >> nrLoc;
		while (zonaSelectata.verificareLocDisponibil(nrRand - 1, nrLoc - 1) == false)
		{
			std::cout << "Locul selectat nu este disponibil" << std::endl;
			std::cout << "Introdu numarul randului (axa din stanga): ";
			std::cin >> nrRand;
			std::cout << "Introdu numarul locului (axa de deasupra): ";
			std::cin >> nrLoc;
		}

		try {
			contextClient->adaugareBilet(evenimente[pozEveniment].vanzareBilet(zona - 1, nrRand - 1, nrLoc - 1));
			salvarePlatforma();
		}
		catch (VanzareNereusitaException err)
		{
			std::cout << "A aparut o eroare. Te rugam reincearca." << std::endl;
			system("PAUSE");
		}
	}
}

void TicketMaster::statisticiEveniment(int pozEveniment)
{
	if (pozEveniment >= 0 && pozEveniment < evenimente.size() && contextClient->getRolAdmin())
	{
		std::cout << "-- Statistici eveniment --" << std::endl;
		std::cout << "Bilete vandute: " << evenimente[pozEveniment].getNrBileteVandute() << std::endl;
		std::cout << "Sume incasate: " << evenimente[pozEveniment].getSumaBileteVandute() << std::endl;
	}
}

void TicketMaster::creareEveniment()
{
	system("CLS");

	std::cout << "======================" << std::endl;
	std::cout << "-> Creare eveniment <-" << std::endl;
	std::cout << "======================" << std::endl;

	Eveniment e;
	std::cin >> e;
	adaugareEveniment(e);

	std::cout << "Eveniment creat cu succes." << std::endl;
	system("PAUSE");
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

		if (std::find(locatii.begin(), locatii.end(), e.getLocatie()) == locatii.end())
		{
			locatii.push_back(e.getLocatie());
		}
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

void TicketMaster::comenziNeautentificat()
{
	std::cout << "1. Lista evenimente" << std::endl;
	std::cout << "2. Autentificare" << std::endl;
	std::cout << "3. Inregistrare" << std::endl;

	std::cout << "Introduceti numarul pentru navigare: ";
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
		afisareEvenimente();
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

	std::cout << "Introduceti numarul pentru navigare: ";
	std::string comanda;
	std::cin >> std::ws;
	std::getline(std::cin, comanda);

	if (comanda != "1" && comanda != "2" && comanda != "3")
	{
		std::cout << "Comanda este invalida. Te rugam sa reincerci." << std::endl;
		start();
	}

	if (comanda == "1")
	{
		afisareEvenimente();
	}

	if(comanda == "2")
	{
		vizualizareCont();
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

	std::cout << "Introduceti numarul pentru navigare: ";
	std::string comanda;
	std::cin >> std::ws;
	std::getline(std::cin, comanda);

	if (comanda != "1" && comanda != "2" && comanda != "3" && comanda != "4")
	{
		std::cout << "Comanda este invalida. Te rugam sa reincerci." << std::endl;
		start();
	}

	if (comanda == "1")
	{
		afisareEvenimente();
	}

	if (comanda == "2")
	{
		creareEveniment();
	}

	if (comanda == "3")
	{
		vizualizareCont();
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

void TicketMaster::cli(std::string numeFisier)
{
	std::ifstream fBilete(numeFisier);

	if (!fBilete.good())
	{
		std::cout << "Fisierul tastat nu este unul valid. Reincercati cu un fisier valid.";
		return;
	}

	int bileteValide = 0;
	while (!fBilete.eof())
	{
		std::string biletDeCautat;
		std::getline(fBilete, biletDeCautat);
		try {
			Bilet b = cautareBilet(biletDeCautat);
			HRESULT hr = URLDownloadToFile(0, L"http://ipinfo.io/json", L"test.json", 0, NULL);
			if (hr == S_OK)
			{
				std::cout << "OK!" << std::endl;
			}
			std::cout << "Biletul " << biletDeCautat << " este valid." << std::endl;
		}
		catch (IndexInvalidException err)
		{
			std::cout << "Biletul " << biletDeCautat << " NU este valid." << std::endl;
		}
	}

	fBilete.close();
}

void TicketMaster::adaugareEveniment(Eveniment e)
{
	evenimente.push_back(e);
	salvarePlatforma();
}

void TicketMaster::adaugareLocatie(Locatie e)
{
	locatii.push_back(e);
}

bool TicketMaster::esteClientExistent(std::string email)
{
	return clienti.find(email) != clienti.end();
}

Bilet TicketMaster::cautareBilet(std::string idBilet)
{
	for (int i = 0; i < evenimente.size(); i++)
	{
		try
		{
			return evenimente[i].getBilet(idBilet);
		}
		catch (IndexInvalidException e)
		{
			continue;
		}
	}

	throw IndexInvalidException();
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
