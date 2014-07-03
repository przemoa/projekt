#ifndef CSERWER_H
#define CSERWER_H

#include <winsock2.h>
#include <iostream>
#include <exception>
#include <list>
#include <QString>

#define ROZMIAR_BUFORA_ODBIORU 256
#define ROZMIAR_BUFORA_WYSYLANIA 2048

class cSerwerClient
{
public:
    cSerwerClient(SOCKET _socket, int _ID);

    bool Odbierz(void);
    void Wyslij(void);

    int ID;
    int bajtyOdebrane;
    char buforOdbioru[ROZMIAR_BUFORA_ODBIORU];

    int bajtyDoWyslania;
    char buforWysylania[ROZMIAR_BUFORA_WYSYLANIA];

    SOCKET socketUsed;
    void DodajBajty(char pierwszy, char drugi, char trzeci, char czwarty, char piaty);
    void DodajBajty(char pierwszy, char drugi, char trzeci, char czwarty);
    void DodajBajty(char pierwszy, char drugi, char trzeci);
    void DodajBajty(char pierwszy, char drugi);
    void DodajBajty(char pierwszy);

    void DodajInt(int dodaj);
    void DodajFloat(float dodaj);
};



class cSerwer
{
public:
    cSerwer(void);
    void Init(int _portNumber);
    void AcceptNewClients(void);
    void ReceiveData(void);
    void SendData(void);
    QString wiadomosc;
    cSerwerClient* gracz1;
    cSerwerClient* gracz2;

    SOCKET socketUsed;

    void CleanUp(const char* error);
};

































#endif // CSERWER_H
