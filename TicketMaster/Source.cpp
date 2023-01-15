#include <iostream>
#include "TicketMaster.h"

int main(char argc, char** argv)
{
	TicketMaster* platforma = TicketMaster::getInstanta();

	if (argc > 1)
	{
		std::string command = argv[0];
		
		if (command == "-h" || command == "--help")
		{
			std::cout << "Comenzi disponibile:" << std::endl;
			std::cout << argv[0] << " -f " << "[numefisier.extensie] (Verificare daca codurile de bilet dintr-un fisier sunt valide)" << std::endl;
			std::cout << argv[0] << " -b " << "[codbilet] (Verificare daca codul de bilet este valid)";
		}

		if (command == "-f")
		{
			// TODO
		}

		if (command == "-b")
		{
			// TODO
		}
	}
	else {
		platforma->start();
	}
}