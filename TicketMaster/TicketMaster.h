#pragma once
#include "Eveniment.h"
#include "Client.h"

class TicketMaster
{
private:
	int nrEvenimente;
	Eveniment* evenimente;
	void setEvenimente(Eveniment* evenimente, int nrEvenimente);

	Client* contextClient;
	void setContextClient(const Client& c);
	void deleteContextClient();

	void comenziNeautentificat();
	void comenziAutentificat();
	void comenziAdmin();
public:
	TicketMaster();

	void start();
	void adaugareEveniment(Eveniment e);
};

