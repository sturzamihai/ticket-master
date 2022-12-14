#pragma once
#include <exception>
#include "GUID.h"
#include "Data.h"

struct Loc {
	bool blocat;
	bool vandut;
	bool checkIn;
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

namespace Utils
{
	std::string citireConsolaParola(std::istream& in);
}