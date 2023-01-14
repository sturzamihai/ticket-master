#pragma once
#include <string>

namespace Utils
{
	class GUID
	{
	private:
		static std::string caractereAdmise;
		static int lungimeParte;
		static int nrParti;
		static std::string separator;

		mutable std::string cod;

		char getCaracterRandom();
		std::string genereazaParte();

	public:
		GUID();

		void reinit(std::string cod) const;

		bool operator==(const GUID& c);
		explicit operator std::string() const;

		static int testareColiziune(int nrGuidGenerate);
	};
}
