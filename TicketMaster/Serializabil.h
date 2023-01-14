#pragma once
#include <fstream>

class Serializabil
{
public:
	virtual void serializare(std::ofstream&) = 0;
	virtual void deserializare(std::ifstream&) = 0;
};