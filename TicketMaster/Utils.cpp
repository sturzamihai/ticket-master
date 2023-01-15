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

	void serializareString(std::string str, std::ofstream& f)
	{
		short dimStr = str.length();
		f.write((char*)&dimStr, sizeof(dimStr));
		f.write(str.c_str(), dimStr + 1);
	}

	std::string deserializareString(std::ifstream& f)
	{
		short dimStr = 0;
		f.read((char*)&dimStr, sizeof(dimStr));

		char* s = new char[dimStr + 1];
		f.read(s, dimStr + 1);
		std::string str = s;
		delete[] s;

		return str;
	}
}