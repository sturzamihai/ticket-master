#pragma once
#include <string>

class GUID
{
private:
	static std::string caractereAdmise;
	static int lungimeParte;
	static int nrParti;
	static std::string separator;

	std::string cod;

	char getCaracterRandom();
	std::string genereazaParte();

public:
	GUID();

	bool operator==(const GUID& c);
	explicit operator std::string();

	static int testareColiziune(int nrGuidGenerate);
};

