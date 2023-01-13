#pragma once
#include <iostream>

class Serializabil
{
public:
	virtual void serializare() = 0;
	virtual void deserializare() = 0;
};