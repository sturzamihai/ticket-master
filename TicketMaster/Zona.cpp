#include "Zona.h"
#include <iostream>
#include <iomanip>

Zona::Zona()
{
	nume = "N/A";
	nrRanduri = 0;
	nrLocuriPerRand = 0;
	hartaLocuri = 0;
}

Zona::Zona(std::string nume, int nrRanduri, int nrLocuriPerRand) : Zona::Zona()
{
	this->nume = nume;
	this->nrRanduri = nrRanduri;
	this->nrLocuriPerRand = nrLocuriPerRand;

	if (nrRanduri > 0 && nrLocuriPerRand > 0)
	{
		this->hartaLocuri = new Loc * [nrRanduri];
		for (int i = 0; i < nrRanduri; i++)
		{
			this->hartaLocuri[i] = new Loc[nrLocuriPerRand]{ false, false };
		}
	}
}

Zona::Zona(const Zona& z) : Zona::Zona(z.nume, z.nrRanduri, z.nrLocuriPerRand)
{
	setHartaLocuri(z.hartaLocuri, z.nrRanduri, z.nrLocuriPerRand);
}

Zona::~Zona()
{
	deleteHartaLocuri();
}

Zona& Zona::operator=(const Zona& z)
{
	if (this != &z)
	{
		nume = z.nume;
		setHartaLocuri(z.hartaLocuri, z.nrRanduri, z.nrLocuriPerRand);
	}
	return *this;
}

// Seteaza numele zonei
void Zona::setNume(std::string nume)
{
	this->nume = nume;
}

// Returneaza numele zonei
std::string Zona::getNume()
{
	return nume;
}

// Seteaza harta locurilor. Necesita o matrice de tip Loc
void Zona::setHartaLocuri(Loc** hartaLocuri, int nrRanduri, int nrLocuriPerRand)
{
	if (hartaLocuri != nullptr && nrRanduri > 0 && nrLocuriPerRand > 0)
	{
		if (this->hartaLocuri != nullptr)
		{
			deleteHartaLocuri();
		}

		this->nrRanduri = nrRanduri;
		this->nrLocuriPerRand = nrLocuriPerRand;
		this->hartaLocuri = new Loc*[nrRanduri];
		for (int i = 0; i < nrRanduri; i++)
		{
			this->hartaLocuri[i] = new Loc[nrLocuriPerRand] {false, false};

			for (int j = 0; j < nrLocuriPerRand; j++)
			{
				this->hartaLocuri[i][j] = hartaLocuri[i][j];
			}
		}
	}
}

// Sterge harta locurilor
void Zona::deleteHartaLocuri()
{
	if (hartaLocuri != nullptr)
	{
		for (int i = 0; i < nrRanduri; i++)
		{
			if (hartaLocuri[i] != nullptr)
			{
				delete[] hartaLocuri[i];
			}
		}

		delete[] hartaLocuri;
		hartaLocuri = nullptr;
	}
}

// Deblocheaza un singur loc (arata existenta acestui loc in realitate)
void Zona::deblocareLoc(int nrRand, int nrLoc)
{
	if (hartaLocuri != nullptr && nrRand < nrRanduri && nrLoc < nrLocuriPerRand)
	{
		hartaLocuri[nrRand][nrLoc].blocat = false;
	}
}

// Blocheaza un singur loc (arata inexistenta acestui loc in realitate)
void Zona::blocareLoc(int nrRand, int nrLoc)
{
	if (hartaLocuri != nullptr && nrRand < nrRanduri && nrLoc < nrLocuriPerRand)
	{
		hartaLocuri[nrRand][nrLoc].blocat = true;
	}
}

std::ostream& operator<<(std::ostream& out, Zona z)
{
	out << "--- " << z.nume << " ---" << std::endl;
	if (z.hartaLocuri != nullptr)
	{
		out << std::setw(3) << std::right <<  " ";
		for (int i = 0; i < z.nrLocuriPerRand; i++)
		{
			out << std::setw(3) << i + 1;
		}
		out << std::endl << std::endl;

;		for (int i = 0; i < z.nrRanduri; i++)
		{
			for (int j = 0; j < z.nrLocuriPerRand; j++)
			{
				if (j == 0)
				{
					out << std::setw(3) << i + 1;
				}

				if (z.hartaLocuri[i][j].blocat == false)
				{
					if (z.hartaLocuri[i][j].vandut == false)
					{
						out << std::setw(3) << "O";
					}
					else
					{
						out << std::setw(3) << "X";
					}
				}
				else {
					out << std::setw(3) << " ";
				}
			}
			out << std::endl;
		}
	}
	else
	{
		out << "Zona nu are locuri create." << std::endl;
	}

	return out;
}

std::istream& operator>>(std::istream& in, Zona& z)
{
	std::cout << "Nume zonei: ";
	in.ignore();
	std::getline(in, z.nume);

	std::cout << "Numarul de randuri: ";
	in >> z.nrRanduri;

	std::cout << "Numarul de locuri per rand: ";
	in >> z.nrLocuriPerRand;

	return in;
}