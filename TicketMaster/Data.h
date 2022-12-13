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
	Data(unsigned int zi, unsigned int luna, unsigned int an);
	Data(unsigned int zi, unsigned int luna, unsigned int an, unsigned ora, unsigned minut);

	bool operator==(const Data& d);
	bool operator<(const Data& d);
	bool operator>(const Data& d);

	friend std::ostream& operator<<(std::ostream&, Data);
	friend std::istream& operator>>(std::istream&, Data&);
};

class DataInvalidaException : public std::exception {
public:
	DataInvalidaException();
	DataInvalidaException(std::string mesaj);
};