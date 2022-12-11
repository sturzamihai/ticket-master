#include <iostream>
#include "Eveniment.h";
#include "Locatie.h";
#include "Utils.h";

int main()
{
	Locatie l;
	std::cin >> l;

	Eveniment a("Test?", l, Data(31,10,2020,18,0), Data(1,11,2020,2,0));
	std::cout << a;
}