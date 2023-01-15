#pragma once
#include <exception>
#include "GUID.h"
#include "Data.h"

struct Loc {
	bool blocat;
	bool vandut;
};

class IndexInvalidException : public std::exception
{
public:
	IndexInvalidException();
};

class VectorNullException : public std::exception
{
public:
	VectorNullException();
};

class VanzareNereusitaException : public std::exception
{
public:
	VanzareNereusitaException();
};

namespace Utils
{
	std::string citireConsolaParola(std::istream& in);
	void serializareString(std::string str, std::ofstream& f);
	std::string deserializareString(std::ifstream& f);
}