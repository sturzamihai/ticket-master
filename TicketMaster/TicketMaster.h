#pragma once
#include "Eveniment.fwd.h"
#include "Client.h"
#include "Locatie.h"
#include <map>
#include <vector>

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
	void setContextClient(const Client& c);
	void deleteContextClient();

	void comenziNeautentificat();
	void comenziAutentificat();
	void comenziAdmin();

	void prelucrareComenziNeautentificat(std::string comanda);
	void prelucrareComenziAutentificat(std::string comanda);
	void prelucrareComenziAdmin(std::string comanda);
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
	void adaugareEveniment(Eveniment e);
	void adaugareLocatie(Locatie e);
	bool esteClientExistent(std::string email);

};

