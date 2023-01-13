#include <iostream>
#include "TicketMaster.h"

int main()
{
	TicketMaster* platforma = TicketMaster::getInstanta();
	platforma->start();
}