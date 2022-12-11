#pragma once
#include <exception>
#include <string>
#include <iostream>

class Data
{
private:
	unsigned int zi;
	unsigned int luna;
	unsigned int an;

	unsigned int ora;
	unsigned int minut;
public:
	Data();
	Data(unsigned int zi, unsigned int unsigned luna, unsigned int an);
	Data(unsigned int zi, unsigned int unsigned luna, unsigned int an, unsigned ora, unsigned minut);

	friend std::ostream& operator<<(std::ostream&, Data);
};

class DataInvalidaException : public std::exception {
public:
	DataInvalidaException();
	DataInvalidaException(std::string mesaj);
};