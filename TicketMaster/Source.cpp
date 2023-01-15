#include <iostream>
#include "TicketMaster.h"

int main(char argc, char** argv)
{
	TicketMaster* platforma = TicketMaster::getInstanta();

	if (argc > 1)
	{
		std::string command = argv[1];
		
		if (command == "-h" || command == "--help")
		{
			std::cout << "Comenzi disponibile:" << std::endl;
			std::cout << argv[0] << " (Rulare clasica, prin consola)" << std::endl;
			std::cout << argv[0] << " -f " << "[numefisier.txt] (Verificare daca codurile de bilet dintr-un fisier sunt valide)" << std::endl;
		}
		else if (command == "-f")
		{
			std::string fisierCoduri = argv[2];
			platforma->cli(fisierCoduri);
		}
		else {
			std::cout << "Parametrul introdus este necunoscut. Te rugam ruleaza -h sau --help pentru mai mule informatii.";
		}
	}
	else {
		platforma->start();
	}
}