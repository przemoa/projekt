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

	string adresIP;

	adresIP = "192.168.0.101";
	//cout << " Podaj IPv4 serwera: ";
	//cin >> adresIP;



	clientService.sin_addr.s_addr = inet_addr(adresIP.c_str());
	clientService.sin_port = htons( 27015 );//htons( 27015 );
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
		case 0x72:
			licznik++;
			drugiBajt = daneOdebrane[licznik];
			licznik++;
			{
				unsigned char nrStworka = daneOdebrane[licznik];
				tabGraczy[drugiBajt]->tabStworkow.erase(tabGraczy[drugiBajt]->tabStworkow.begin()+nrStworka);
			}
			break;

		case 0x63:
			{
				licznik++;
				int _gracz = daneOdebrane[licznik];
				licznik ++;
				int _nrWiezy = daneOdebrane[licznik];

				
				Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].level++;
				switch (Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].typWiezy)
				{
				case TEKSTURA_WIEZA1:		// luk, srednioszybka, male obrazenia, sredni zasieg
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].obrazenia += 4;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].zasieg += 20;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].szybkoscAtaku += 6;
					break;
				case TEKSTURA_WIEZA2:		// kamien, malas szybkosc, srednie obrazenia, maly zasieg
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].obrazenia += 6;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].zasieg += 12;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].szybkoscAtaku += 4;
					break;
				case TEKSTURA_WIEZA3:		// pocisk, srednia szybkosc, srednie obrazenia, sredni zasieg
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].obrazenia += 6;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].zasieg += 25;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].szybkoscAtaku += 6;
					break;
				case TEKSTURA_WIEZA4:		// laser, malas szybkosc, duze obrazenia, duzy zasieg
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].obrazenia += 15;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].zasieg += 35;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].szybkoscAtaku += 2;
					break;
				case TEKSTURA_WIEZA5:		// ogien, mala szybkosc, duze obrazenia, maly zasieg
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].obrazenia += 6;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].zasieg += 10;
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].szybkoscAtaku += 5;
					break;
				case TEKSTURA_WIEZA6:		// produkuje zloto
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].obrazenia += 2;
					break;
				case TEKSTURA_WIEZA7:		// leczy zamek
					Plansza->tabGraczy[_gracz]->zamek->tabWiez[_nrWiezy].obrazenia += 2;
					break;
				}
			}
			break;

		case 0x64:
			{
				licznik++;
				int _gracz = daneOdebrane[licznik];
				licznik ++;
				int _nrWiezy = daneOdebrane[licznik];
				Plansza->tabGraczy[_gracz]->zamek->tabWiez.erase(Plansza->tabGraczy[_gracz]->zamek->tabWiez.begin() + _nrWiezy);
			}
			break;
			

		case 0x62:
			{
				
				licznik++;
				int _gracz = daneOdebrane[licznik];
				licznik ++;
				int _typWiezy = daneOdebrane[licznik];
				licznik ++;
				int pozycja = daneOdebrane[licznik] * 100;
				licznik ++;
				pozycja += daneOdebrane[licznik];

				sWIEZA nowaWieza;
				nowaWieza.pozycja = pozycja;
				nowaWieza.typWiezy = _typWiezy;
				nowaWieza.level = 1;
				nowaWieza.czyAtakuje = true;
				switch (_typWiezy)
				{
				case TEKSTURA_WIEZA1:		// luk, srednioszybka, male obrazenia, sredni zasieg
					nowaWieza.obrazenia = 15;
					nowaWieza.zasieg = 150;
					nowaWieza.szybkoscAtaku = 35;
					break;
				case TEKSTURA_WIEZA2:		// kamien, malas szybkosc, srednie obrazenia, maly zasieg
					nowaWieza.obrazenia = 25;
					nowaWieza.zasieg = 100;
					nowaWieza.szybkoscAtaku = 20;
					break;
				case TEKSTURA_WIEZA3:		// pocisk, srednia szybkosc, srednie obrazenia, sredni zasieg
					nowaWieza.obrazenia = 35;
					nowaWieza.zasieg = 250;
					nowaWieza.szybkoscAtaku = 35;
					break;
				case TEKSTURA_WIEZA4:		// laser, malas szybkosc, duze obrazenia, duzy zasieg
					nowaWieza.obrazenia = 95;
					nowaWieza.zasieg = 350;
					nowaWieza.szybkoscAtaku = 10;
					break;
				case TEKSTURA_WIEZA5:		// ogien, mala szybkosc, duze obrazenia, maly zasieg
					nowaWieza.obrazenia = 40;
					nowaWieza.zasieg = 80;
					nowaWieza.szybkoscAtaku = 20;
					break;
				case TEKSTURA_WIEZA6:		// produkuje zloto
					nowaWieza.obrazenia = 5;
					nowaWieza.czyAtakuje = false;
					break;
				case TEKSTURA_WIEZA7:		// leczy zamek
					nowaWieza.obrazenia = 10;
					nowaWieza.czyAtakuje = false;
					break;
				}

				Plansza->tabGraczy[_gracz]->zamek->tabWiez.insert(Plansza->tabGraczy[_gracz]->zamek->tabWiez.begin(), nowaWieza);
			}
			break;
		case 0x34:
			{
				int _level = 0;
				int _doswiadczenie = 0;
				int _wydobycie = 0;
				float _poziomZycia = 0;
				float _mnoznikZycia = 0;

				memcpy(&_level, daneOdebrane+licznik+1, 4);
				licznik += 4;
				memcpy(&_doswiadczenie, daneOdebrane+licznik+1, 4);
				licznik += 4;
				memcpy(&_wydobycie, daneOdebrane+licznik+1, 4);
				licznik += 4;
				memcpy(&_poziomZycia, daneOdebrane+licznik+1, 4);
				licznik += 4;
				memcpy(&_mnoznikZycia, daneOdebrane+licznik+1, 4);
				licznik += 4;

				tabGraczy[0]->zamek->level = _level;
				tabGraczy[0]->zamek->doswiadczenie = _doswiadczenie;
				tabGraczy[0]->zamek->wydobycie = _wydobycie;
				tabGraczy[0]->zamek->poziomZycia = _poziomZycia;
				tabGraczy[0]->zamek->mnoznikZycia = _mnoznikZycia;
			}
			break;

		case 0x35:
			{
				int _level = 0;
				int _doswiadczenie = 0;
				int _wydobycie = 0;
				float _poziomZycia = 0;
				float _mnoznikZycia = 0;

				memcpy(&_level, daneOdebrane+licznik+1, 4);
				licznik += 4;
				memcpy(&_doswiadczenie, daneOdebrane+licznik+1, 4);
				licznik += 4;
				memcpy(&_wydobycie, daneOdebrane+licznik+1, 4);
				licznik += 4;
				memcpy(&_poziomZycia, daneOdebrane+licznik+1, 4);
				licznik += 4;
				memcpy(&_mnoznikZycia, daneOdebrane+licznik+1, 4);
				licznik += 4;

				tabGraczy[1]->zamek->level = _level;
				tabGraczy[1]->zamek->doswiadczenie = _doswiadczenie;
				tabGraczy[1]->zamek->wydobycie = _wydobycie;
				tabGraczy[1]->zamek->poziomZycia = _poziomZycia;
				tabGraczy[1]->zamek->mnoznikZycia = _mnoznikZycia;
			}
			break;

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

				if (tabGraczy[drugiBajt]->tabBohaterow[trzeciBajt-1] != NULL)
					tabGraczy[drugiBajt]->tabBohaterow[trzeciBajt-1]->zywy = true;
				else
				{

					int _wlasciciel = tabGraczy[drugiBajt]->wlasciciel;
					float _x = tabGraczy[drugiBajt]->x;
					float _y = tabGraczy[drugiBajt]->y;
					if (trzeciBajt == 1) tabGraczy[drugiBajt]->tabBohaterow[trzeciBajt-1] = new cBohater1(_x+60*_wlasciciel, _y, _wlasciciel);
					if (trzeciBajt == 2) tabGraczy[drugiBajt]->tabBohaterow[trzeciBajt-1] = new cBohater2(_x+60*_wlasciciel, _y, _wlasciciel);
				}
			}
			break;

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
							if (i == 1)
							{
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
								float _mnoznik = 0;
						
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
								memcpy(&_mnoznik, daneOdebrane+licznik+1, 4);
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
								tabGraczy[0]->tabBohaterow[i]->szybkoscAtaku = _mnoznik;
							}
							if (i == 0)
							{
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
								float _mnoznik = 0;
								float _kat = 0;
						
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
								memcpy(&_mnoznik, daneOdebrane+licznik+1, 4);
								licznik += 4;
								memcpy(&_kat, daneOdebrane+licznik+1, 4);
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
								tabGraczy[0]->tabBohaterow[i]->szybkoscAtaku = _mnoznik;
								tabGraczy[0]->tabBohaterow[i]->kat = _kat;
							}
						}
					}
				}
			}
			break;


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
							if (i == 1)
							{
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
							float _mnoznik = 0;

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
							memcpy(&_mnoznik, daneOdebrane+licznik+1, 4);
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
							tabGraczy[1]->tabBohaterow[i]->szybkoscAtaku = _mnoznik;
							}

							if (i == 0)
							{
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
								float _mnoznik = 0;
								float _kat = 0;
						
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
								memcpy(&_mnoznik, daneOdebrane+licznik+1, 4);
								licznik += 4;
								memcpy(&_kat, daneOdebrane+licznik+1, 4);
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
								tabGraczy[1]->tabBohaterow[i]->szybkoscAtaku = _mnoznik;
								tabGraczy[1]->tabBohaterow[i]->kat = _kat;
							}
						}
					}
				}
			}
			break;

			case 0x65:
			{

				licznik++;
				drugiBajt = daneOdebrane[licznik];
				licznik ++;
				trzeciBajt = daneOdebrane[licznik];

				float x1 = Plansza->tabPunktStab[drugiBajt]->x;
				float x2 = Plansza->tabPunktStab[trzeciBajt]->x;
				float y1 = Plansza->tabPunktStab[drugiBajt]->y;
				float y2 = Plansza->tabPunktStab[trzeciBajt]->y;

				cBelka *nowa = new cBelka(x1, y1, x2, y2, false);
				tabElementow.push_back(nowa);

			}
			break;

			case 0x66:
			{
				licznik++;
				drugiBajt = daneOdebrane[licznik];

				float xp = Plansza->tabElementow[drugiBajt]->x_poczatku;
				float yp = Plansza->tabElementow[drugiBajt]->y_poczatku;

				float xk = Plansza->tabElementow[drugiBajt]->x_konca;
				float yk = Plansza->tabElementow[drugiBajt]->y_konca;

				float xs = 0.5 * (xp + xk)+40;
				float ys = 0.5 * (yp + yk)+40;

				tabElementow.erase(drugiBajt + tabElementow.begin());

				cBelka *nowa = new cBelka(xp, yp, xs, ys, true);
				cBelka *nowa2 = new cBelka(xk, yk, xs, ys, true);
				tabElementow.push_back(nowa);
				tabElementow.push_back(nowa2);

			}
			break;


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