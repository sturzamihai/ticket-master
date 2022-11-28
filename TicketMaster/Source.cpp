#include <iostream>
#include "Locatie.h"
#include "Eveniment.h"

int main()
{
	Locatie cinema = "Cinema AFI Palace Cotroceni";
	Zona salaCinema("Sala IMAX", 6, 10);

	for (int i = 0; i < 6; i++)
	{
		salaCinema.blocareLoc(i, 1);
		salaCinema.blocareLoc(i, 8);
	}

	for (int i = 3; i < 6; i++)
	{
		salaCinema.blocareLoc(i, 2);
		salaCinema.blocareLoc(i, 7);
	}
	
	std::cout << salaCinema;
	cinema.adaugareZona(salaCinema);

	std::cout << cinema;
}