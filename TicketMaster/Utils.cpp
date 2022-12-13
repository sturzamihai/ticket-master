#include "Utils.h"
#include <Windows.h>

IndexInvalidException::IndexInvalidException() : std::exception("Indexul cautat nu este valid") {}
VectorNullException::VectorNullException() : std::exception("Vectorul accesat este null") {}

namespace Utils
{
	std::string citireConsolaParola(std::istream& in)
	{
		HANDLE intrareStd = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mod = 0;

		GetConsoleMode(intrareStd, &mod);

		SetConsoleMode(intrareStd, mod & (~ENABLE_ECHO_INPUT));

		std::string date;
		std::getline(in, date);
		std::cout << std::endl;

		SetConsoleMode(intrareStd, mod);

		return date;
	}
}