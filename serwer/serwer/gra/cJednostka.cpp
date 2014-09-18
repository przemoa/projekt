#include "cJednostka.h"


cJednostka::cJednostka(void)
{
	cJednostka::aktualneId++;
	id = cJednostka::aktualneId;

	level = 1;
	doswiadczenie = 0;
	poziomZycia = 100;
    turDoAtaku = 10;
}


cJednostka::~cJednostka(void)
{
}
