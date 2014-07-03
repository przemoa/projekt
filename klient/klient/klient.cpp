#include "cPlansza.h"
#include "cBohater1.h"
#include "cBohater2.h"

bool cPlansza::PolaczZSerwerem()
{
		// Initialize Winsock.
	WSADATA wsaData;
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );//initialize Windows Sockets API
	if ( iResult != NO_ERROR )
		printf("Error at WSAStartup()\n");	


		//tworzone jest gniazdo dla rodziny adresów (AdresFamily) sieci internet dla trybu
	//strumieniowego przesy³ania danych), do obs³ugi tego trybu w seci internet s³u¿y protokó³
	//TCP/IP (IPPROTO_TCP)
	m_socket = socket( AF_INET, SOCK_STREAM, 0 ); // tworzony jest socket
	if ( m_socket == INVALID_SOCKET ) { // obs³uga b³êdu
		printf( "Error at socket(): %ld\n", WSAGetLastError() );
		WSACleanup();
		return false;
	}



		//inicjowana jest struktura zawieraj¹ce adres serwera i numer gniazda na którym nas³uchuje
	//(27015) do w³asnych celów nale¿y wykozystywaæ gniazda o numerze >1024. Adres IP
	//127.0.0.1 odpowiada lokalnemu komputerowi (localhost)
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr( "192.168.0.100");
	clientService.sin_port = htons( 3000 );//htons( 27015 );
	if ( connect( m_socket, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) {
		printf( ":: Polaczenie nieudane\n" );
		WSACleanup();
		return false;
	}	

	etapGry = OCZEKIWANIE_NA_WARUNKI;
	cout << ":: Polaczono z serwerem" << endl;

	u_long NonBlock = 1;
    ioctlsocket(m_socket, FIONBIO, &NonBlock);
	return true;
}

void cPlansza::OdbierzDane()
{
		//Odebrane dane s¹ zapisywane do bufora recbuf, którego maksymalny rozmiar jet okreoelony
	//w wywo³aniu funkcji recv. Ilooeæ danych odczytanych jest zwracana do zmiennej bytesRecv

	bajtyOdebrane = SOCKET_ERROR;
	while (bajtyOdebrane == SOCKET_ERROR )
	{
		bajtyOdebrane = recv( m_socket, daneOdebrane, 4096, 0 );

		if ( bajtyOdebrane == 0 || bajtyOdebrane == WSAECONNRESET )
		{
			printf( "::Polaczenie zepsute.\n");
			break;
		}
		if (bajtyOdebrane < 0)
			return;
	}


}

void cPlansza::PrzetworzDane()
{

	for (int licznik = 0; licznik < bajtyOdebrane; licznik++)
	{
		char drugiBajt = 0;
        char trzeciBajt = 0;
		switch(daneOdebrane[licznik])
		{
		case 0x70:
			licznik++;
			drugiBajt = daneOdebrane[licznik];
			tabGraczy[drugiBajt]->levelStworkow++;
			break;
		case 0x01:
			{
				int zloto = 0;
				memcpy(&zloto, daneOdebrane+licznik+1, 4);
				licznik += 4;
				tabGraczy[wybranyGracz]->zloto = zloto;

			}
			break;
		case 0x60:
			{
				licznik++;
				drugiBajt = daneOdebrane[licznik];
				licznik ++;
				trzeciBajt = daneOdebrane[licznik];

				int _wlasciciel = tabGraczy[drugiBajt]->wlasciciel;
				int _x = tabGraczy[drugiBajt]->x;
				cStworek* nowyStworek = new cStworek(_x+40*_wlasciciel, -0.5, trzeciBajt, _wlasciciel, tabGraczy[drugiBajt]->levelStworkow);
				tabGraczy[drugiBajt]->tabStworkow.push_back(nowyStworek);
			}
			break;
		case 0x30:
			{
				int ile=0;
				memcpy(&ile, daneOdebrane+licznik+1, 4);
				licznik += 4;
				for (int i = 0; i < ile; i++)
				{
					float _x=0;
					float _y=0;
					float _hp=0;
					memcpy(&_x, daneOdebrane+licznik+1, 4);
					licznik += 4;
					memcpy(&_y, daneOdebrane+licznik+1, 4);
					licznik += 4;
					memcpy(&_hp, daneOdebrane+licznik+1, 4);
					licznik += 4;

					tabGraczy[0]->tabStworkow[i]->x = _x;
					tabGraczy[0]->tabStworkow[i]->y = _y;
					tabGraczy[0]->tabStworkow[i]->poziomZycia = _hp;
				}
			}
			break;

		case 0x31:
			{
				int ile=0;
				memcpy(&ile, daneOdebrane+licznik+1, 4);
				licznik += 4;
				for (int i = 0; i < ile; i++)
				{
					float _x=0;
					float _y=0;
					float _hp=0;
					memcpy(&_x, daneOdebrane+licznik+1, 4);
					licznik += 4;
					memcpy(&_y, daneOdebrane+licznik+1, 4);
					licznik += 4;
					memcpy(&_hp, daneOdebrane+licznik+1, 4);
					licznik += 4;

					tabGraczy[1]->tabStworkow[i]->x = _x;
					tabGraczy[1]->tabStworkow[i]->y = _y;
					tabGraczy[1]->tabStworkow[i]->poziomZycia = _hp;
				}
			}
			break;
		case 0x61:
			{
				licznik++;
				drugiBajt = daneOdebrane[licznik];
				licznik ++;
				trzeciBajt = daneOdebrane[licznik];

				if (tabGraczy[drugiBajt]->tabBohaterow[trzeciBajt] != NULL)
					tabGraczy[drugiBajt]->tabBohaterow[trzeciBajt]->zywy = true;
				else
				{

					int _wlasciciel = tabGraczy[drugiBajt]->wlasciciel;
					float _x = tabGraczy[drugiBajt]->x;
					float _y = tabGraczy[drugiBajt]->y;
					if (trzeciBajt == 1) tabGraczy[drugiBajt]->tabBohaterow[trzeciBajt-1] = new cBohater1(_x+60*_wlasciciel, _y, _wlasciciel);
					if (trzeciBajt == 2) tabGraczy[drugiBajt]->tabBohaterow[trzeciBajt-1] = new cBohater2(_x+60*_wlasciciel, _y, _wlasciciel);
				}
			}

		case 0x32:
			{
				for (int i = 0; i < 3; i++)
				{
					licznik++;
					if (tabGraczy[0]->tabBohaterow[i])
					{
						if (!daneOdebrane[licznik]) tabGraczy[0]->tabBohaterow[i]->zywy = 0;
						else
						{
							tabGraczy[0]->tabBohaterow[i]->zywy = 1;
							float _x = 0;
							float _y = 0;
							float _hp = 0;
							float _obrazenia = 0;
							float _zasieg = 0;
							float _mocSilnika = 0;
							float _energia = 0;
							int _level = 0;
							int _doswiadczenie = 0;
							int _szybkosc = 0;
						
							memcpy(&_x, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_y, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_hp, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_obrazenia, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_zasieg, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_mocSilnika, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_energia, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_level, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_doswiadczenie, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_szybkosc, daneOdebrane+licznik+1, 4);
							licznik += 4;


						
							tabGraczy[0]->tabBohaterow[i]->x = _x;
							tabGraczy[0]->tabBohaterow[i]->y = _y;
							tabGraczy[0]->tabBohaterow[i]->poziomZycia = _hp;
							tabGraczy[0]->tabBohaterow[i]->obrazenia = _obrazenia;
							tabGraczy[0]->tabBohaterow[i]->zasieg = _zasieg;
							tabGraczy[0]->tabBohaterow[i]->mocSilnika = _mocSilnika;
							tabGraczy[0]->tabBohaterow[i]->energia = _energia;
							tabGraczy[0]->tabBohaterow[i]->level = _level;
							tabGraczy[0]->tabBohaterow[i]->doswiadczenie = _doswiadczenie;
							tabGraczy[0]->tabBohaterow[i]->szybkoscAtaku = _szybkosc;

						}
					}

				}
			}



			case 0x33:
			{
				
				for (int i = 0; i < 3; i++)
				{
					licznik++;
					if (tabGraczy[1]->tabBohaterow[i])
					{
						if (!daneOdebrane[licznik]) tabGraczy[1]->tabBohaterow[i]->zywy = 0;
						else
						{
							tabGraczy[1]->tabBohaterow[i]->zywy = 1;
							float _x = 0;
							float _y = 0;
							float _hp = 0;
							float _obrazenia = 0;
							float _zasieg = 0;
							float _mocSilnika = 0;
							float _energia = 0;
							float _level = 0;
							float _doswiadczenie = 0;
							float _szybkosc = 0;

							memcpy(&_x, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_y, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_hp, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_obrazenia, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_zasieg, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_mocSilnika, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_energia, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_level, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_doswiadczenie, daneOdebrane+licznik+1, 4);
							licznik += 4;
							memcpy(&_szybkosc, daneOdebrane+licznik+1, 4);
							licznik += 4;


							tabGraczy[1]->tabBohaterow[i]->x = _x;
							tabGraczy[1]->tabBohaterow[i]->y = _y;
							tabGraczy[1]->tabBohaterow[i]->poziomZycia = _hp;
							tabGraczy[1]->tabBohaterow[i]->obrazenia = _obrazenia;
							tabGraczy[1]->tabBohaterow[i]->zasieg = _zasieg;
							tabGraczy[1]->tabBohaterow[i]->mocSilnika = _mocSilnika;
							tabGraczy[1]->tabBohaterow[i]->energia = _energia;
							tabGraczy[1]->tabBohaterow[i]->level = _level;
							tabGraczy[1]->tabBohaterow[i]->doswiadczenie = _doswiadczenie;
							tabGraczy[1]->tabBohaterow[i]->szybkoscAtaku = _szybkosc;
						}
					}
				}
			}





		}
	}
}

void cPlansza::CzekajNaRozpoczenie()
{
	if (bajtyOdebrane > 0)
	{

		if (daneOdebrane[0] != 0x01) return;
		int zloto = 0;
		memcpy(&zloto, daneOdebrane+1, 4);

		tabGraczy[0]->zloto = zloto;
		wybranyGracz = daneOdebrane[5];

		if (wybranyGracz == 1)
		{
			kamera.xCel = 900;
			tabGraczy[1]->zloto = zloto;
		}

		bajtyOdebrane = 5;
		etapGry = OCZEKIWANIE_NA_ROZPOCZECIE;
		cout << ":: Oczekiwanie na rozpoczecie gry" << endl;
	}
}

void cPlansza::WyslijDane()
{
	daneDoWyslania[bajtyDoWyslania] = NULL;
	bajtyDoWyslania++;

	send( m_socket, daneDoWyslania, bajtyDoWyslania, 0 );
	bajtyDoWyslania = 0;
}


//void cPlansza::DodajAkcjeDoWyslania()
//{
//
//}

//void cPlansza::DodajWiadomoscDoWyslania()
//{
//
//}

void cPlansza::DodajAkcje(char pierwszy, char drugi , char trzeci )
{

	daneDoWyslania[bajtyDoWyslania] = pierwszy;
	bajtyDoWyslania++;

	if (drugi)
	{
		daneDoWyslania[bajtyDoWyslania] = drugi;
		bajtyDoWyslania++;
	}

	if (trzeci)
	{
		daneDoWyslania[bajtyDoWyslania] = trzeci;
		bajtyDoWyslania++;
	}

}