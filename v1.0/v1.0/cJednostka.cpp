#include "cJednostka.h"


cJednostka::cJednostka(void)
{
	cJednostka::aktualneId++;
	id = cJednostka::aktualneId;
}


cJednostka::~cJednostka(void)
{
}

int cJednostka::GetId()
{
	return id;
}