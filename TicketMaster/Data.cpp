#include "Data.h"

Data::Data()
{
	zi = 1;
	luna = 1;
	an = 2000;

	ora = 0;
	minut = 0;
}

Data::Data(unsigned int zi, unsigned int luna, unsigned int an) : Data()
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

Data::Data(unsigned int zi, unsigned int luna, unsigned int an, unsigned ora, unsigned minut = 0) : Data(zi, luna, an)
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

bool Data::operator==(const Data& d)
{
	return this->an == d.an && this->luna == d.luna && this->zi == d.zi && this->ora == d.ora && this->minut == d.minut;
}

bool Data::operator<(const Data& d)
{
	if (this->an != d.an) return this->an < d.an;
	if (this->luna != d.luna) return this->luna < d.luna;
	if (this->zi != d.zi) return this->zi < d.zi;
	if (this->ora != d.ora) return this->ora < d.ora;
	if (this->minut != d.minut) return this->minut < d.minut;

	return false;
}

bool Data::operator>(const Data& d)
{
	if (this->an != d.an) return this->an > d.an;
	if (this->luna != d.luna) return this->luna > d.luna;
	if (this->zi != d.zi) return this->zi > d.zi;
	if (this->ora != d.ora) return this->ora > d.ora;
	if (this->minut != d.minut) return this->minut > d.minut;

	return false;
}

std::ostream& operator<<(std::ostream& out, Data d)
{
	out << d.zi << "." << d.luna << "." << d.an << " ";
	out << (d.ora < 10 ? "0" : "") << d.ora << ":" << (d.minut < 10 ? "0" : "") << d.minut;

	return out;
}

std::istream& operator>>(std::istream& in, Data& d)
{
	int zi;
	std::cout << "Zi: ";
	in >> zi;
	while (zi <= 0 || zi > 31)
	{
		std::cout << "Zilele lunii sunt cuprinse intre 1 si 31." << std::endl << "Introdu o valoare din intervalul dat: ";
		in >> zi;
	}
	d.zi = zi;

	int luna;
	std::cout << "Luna: ";
	in >> luna;
	while (luna <= 0 || luna > 12)
	{
		std::cout << "Lunile anului sunt cuprinse intre 1 si 12." << std::endl << "Introdu o valoare din intervalul dat: ";
		in >> luna;
	}
	d.luna = luna;

	int an;
	std::cout << "An: ";
	in >> an;
	while (an <= 1900)
	{
		std::cout << "Te rugam introdu un an dupa 1900: ";
		in >> an;
	}
	d.an = an;

	int ora;
	std::cout << "Ora: ";
	in >> ora;
	while (ora < 0 || ora > 24)
	{
		std::cout << "Ora poate sa fie cuprinsa intre 0 si 24." << std::endl << "Introdu o valoare din intervalul dat: ";
		in >> ora;
	}
	d.ora = ora;

	int minut;
	std::cout << "Minutul: ";
	in >> minut;
	while (minut < 0 || minut > 60)
	{
		std::cout << "Minutele pot sa fie cuprinse intre 0 si 60." << std::endl << "Introdu o valoare din intervalul dat: ";
		in >> minut;
	}
	d.minut = minut;

	return in;
}


void Data::serializare(std::ofstream& f)
{
	f.write((char*)&zi, sizeof(zi));
	f.write((char*)&luna, sizeof(luna));
	f.write((char*)&an, sizeof(an));

	f.write((char*)&ora, sizeof(minut));
	f.write((char*)&ora, sizeof(minut));
}

void Data::deserializare(std::ifstream& f)
{
	f.read((char*)&zi, sizeof(zi));
	f.read((char*)&luna, sizeof(luna));
	f.read((char*)&an, sizeof(an));

	f.read((char*)&ora, sizeof(minut));
	f.read((char*)&ora, sizeof(minut));
}

DataInvalidaException::DataInvalidaException() : std::exception("Data introdusa nu este valida") {}
DataInvalidaException::DataInvalidaException(std::string mesaj) : std::exception(mesaj.c_str()) {}