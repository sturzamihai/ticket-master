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
	this->setHartaLocuri(Zona::generareHartaLocuri(nrRanduri, nrLocuriPerRand), nrRanduri, nrLocuriPerRand);
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

// Returneaza numarul de randuri ale zonei
int Zona::getNrRanduri()
{
	return nrRanduri;
}

// Returneaza numarul de locuri ale zonei
int Zona::getNrLocuriPerRand()
{
	return nrLocuriPerRand;
}

// Returneaza capacitatea zonei
int Zona::getCapacitateMaxima()
{
	int capacitate = 0;

	if (hartaLocuri != nullptr)
	{
		for (int i = 0; i < nrRanduri; i++)
		{
			for (int j = 0; j < nrLocuriPerRand; j++)
			{
				if (!hartaLocuri[i][j].blocat)
				{
					capacitate++;
				}
			}
		}
	}
	else
	{
		capacitate = nrRanduri * nrLocuriPerRand;
	}

	return capacitate;
}

// Seteaza harta locurilor. Necesita o matrice de tip Loc (ce se poate genera prin functia statica)
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

// Functie statica pentru generarea unei harti de locuri cu nrRanduri randuri si nrLocuriPerRand coloane
Loc** Zona::generareHartaLocuri(int nrRanduri, int nrLocuriPerRand)
{
	if (nrRanduri > 0 && nrLocuriPerRand > 0)
	{
		Loc** hartaLocuri = new Loc * [nrRanduri];
		for (int i = 0; i < nrRanduri; i++)
		{
			hartaLocuri[i] = new Loc[nrLocuriPerRand]{ false, false };
		}

		return hartaLocuri;
	}

	return nullptr;
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

bool Zona::vanzareLoc(int nrRand, int nrLoc)
{
	if (hartaLocuri != nullptr && nrRand < nrRanduri && nrLoc < nrLocuriPerRand && hartaLocuri[nrRand][nrLoc].blocat == false)
	{
		hartaLocuri[nrRand][nrLoc].vandut = true;
		return true;
	}

	return false;
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

	int nrRanduri;
	int nrLocuriPerRand;
	std::cout << "Numarul de randuri: ";
	in >> nrRanduri;

	std::cout << "Numarul de locuri per rand: ";
	in >> nrLocuriPerRand;

	z.setHartaLocuri(Zona::generareHartaLocuri(nrRanduri, nrLocuriPerRand), nrRanduri, nrLocuriPerRand);
	std::cout << "Harta actuala:" << std::endl << z;

	std::cout << "Exista locuri in diagrama care nu exista in sala reala? (y/n): ";
	std::string command;
	in >> command;
	while (command != "y" && command != "n")
	{
		std::cout << "Comanda nu este valida. Te rog reincearca." << std::endl;
		std::cout << "Exista locuri in diagrama care nu exista in sala reala? (y/n): ";
		in >> command;
	}

	if (command == "y")
	{
		int nrRand;
		int nrLoc;
		std::cout << "Introdu randul (numerele din stanga diagramei) si scaunul (numerele din partea de sus a diagramei). Cand ai terminat de introdus toate locurile, scrie pentru rand si loc valorile 0." << std::endl;
		std::cout << "Rand si loc de blocat: ";
		in >> nrRand >> nrLoc;
		while (nrRand != 0 && nrLoc != 0)
		{
			z.blocareLoc(nrRand - 1, nrLoc - 1);
			std::cout << "Rand si loc de blocat: ";
			in >> nrRand >> nrLoc;
		}
	}

	return in;
}