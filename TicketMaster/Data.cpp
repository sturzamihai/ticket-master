#include "Data.h"

Data::Data()
{
	zi = 1;
	luna = 1;
	an = 2000;

	ora = 0;
	minut = 0;
}

Data::Data(unsigned int zi, unsigned int unsigned luna, unsigned int an) : Data()
{
	if ((zi > 0 && zi <= 31) && (luna > 0 && luna <= 12) && (an >= 1900))
	{
		this->zi = zi;
		this->luna = luna;
		this->an = an;
	} 
	else
	{
		throw DataInvalidaException();
	}
}

Data::Data(unsigned int zi, unsigned int unsigned luna, unsigned int an, unsigned ora, unsigned minut = 0) : Data(zi, luna, an)
{
	if ((ora >= 0 && ora <= 24) && (minut >= 0 && minut <= 60))
	{
		this->ora = ora;
		this->minut = minut;
	}
	else
	{
		throw DataInvalidaException();
	}
}

std::ostream& operator<<(std::ostream& out, Data d)
{
	out << d.zi << "." << d.luna << "." << d.an << " ";
	out << (d.ora < 10 ? "0" : "") << d.ora << ":" << (d.minut < 10 ? "0" : "") << d.minut;

	return out;
}

DataInvalidaException::DataInvalidaException() : std::exception("Data introdusa nu este valida") {}
DataInvalidaException::DataInvalidaException(std::string mesaj) : std::exception(mesaj.c_str()) {}