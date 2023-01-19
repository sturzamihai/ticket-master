#pragma once
#include "Eveniment.fwd.h"
#include "Client.h"
#include "Locatie.h"
#include <map>
#include <vector>
#include <functional>

class TicketMaster
{
private:

	static TicketMaster* tm_;
	TicketMaster();

	std::vector<Eveniment> evenimente;
	void setEvenimente(std::vector<Eveniment> evenimente);

	std::vector<Locatie> locatii;
	void setLocatii(std::vector<Locatie> locatii);

	std::map<std::string, Client> clienti;

	Client* contextClient;

	void comenziNeautentificat();
	void comenziAutentificat();
	void comenziAdmin();

	/* Auth commands */
	void logare();
	void delogare();
	void creareCont(bool esteAdmin);
	void vizualizareCont();

	/* Comenzi evenimente */
	void afisareEvenimente();
	void afisareEveniment(int pozEveniment);
	void cumparareBiletEveniment(int pozEveniment);
	void statisticiEveniment(int pozEveniment);
	void creareEveniment();

	/* Salvare si restaurare platforma */
	void salvarePlatforma();
	void restaurarePlatforma();
public:
	/* Singleton */
	TicketMaster(const TicketMaster& tm) = delete;
	void operator=(const TicketMaster&) = delete;
	static TicketMaster* getInstanta();

	/* Getters */
	std::vector<Locatie> getLocatii();
	Client getClient(std::string email);

	/* Metode */
	void start();
	void cli(std::string numeFisier, bool generarePdf);
	void adaugareEveniment(Eveniment e);
	void adaugareLocatie(Locatie e);
	bool esteClientExistent(std::string email);
	Bilet cautareBilet(std::string idBilet);
};

