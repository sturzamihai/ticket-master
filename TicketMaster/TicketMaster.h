#pragma once
#include "Eveniment.h"
#include "Client.h"
#include <map>

class TicketMaster
{
private:
	int nrEvenimente;
	Eveniment* evenimente;
	void setEvenimente(Eveniment* evenimente, int nrEvenimente);

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
	TicketMaster();

	void start();
	void adaugareEveniment(Eveniment e);
};

