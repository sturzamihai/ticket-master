#include "Utils.h";

IndexInvalidException::IndexInvalidException() : std::exception("Indexul cautat nu este valid") {}