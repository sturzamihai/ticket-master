#include "GUID.h"

namespace Utils {
	std::string GUID::caractereAdmise = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int GUID::lungimeParte = 5;
	int GUID::nrParti = 3;
	std::string GUID::separator = "-";

	GUID::GUID()
	{
		cod = "";
		for (int i = 0; i < GUID::nrParti; i++)
		{
			cod += genereazaParte();
			if (i < GUID::nrParti - 1)
			{
				cod += GUID::separator;
			}
		}
	}

	void GUID::reinit(std::string cod) const
	{
		this->cod = cod;
	}

	char GUID::getCaracterRandom()
	{
		return caractereAdmise[rand() % (caractereAdmise.length() - 1)];
	}

	std::string GUID::genereazaParte()
	{
		std::string parteNoua;
		for (int i = 0; i < GUID::lungimeParte; i++)
		{
			parteNoua += getCaracterRandom();
		}

		return parteNoua;
	}

	bool GUID::operator==(const GUID& g)
	{
		return this->cod == g.cod;
	}

	GUID::operator std::string() const
	{
		return cod;
	}

	int GUID::testareColiziune(int nrGuidGenerate)
	{
		GUID* teste = new GUID[nrGuidGenerate];

		int coliziuni = 0;
		for (int i = 0; i < nrGuidGenerate - 1; i++)
		{
			for (int j = i + 1; j < nrGuidGenerate; j++)
			{
				if (teste[i] == teste[j]) coliziuni++;
			}
		}

		delete[] teste;
		return coliziuni;
	}
}