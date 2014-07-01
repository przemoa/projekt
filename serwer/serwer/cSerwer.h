#ifndef CSERWER_H
#define CSERWER_H

#include <winsock2.h>
#include <iostream>
#include <exception>
#include <list>
#include <QString>

class cSerwerClient
{
public:
    cSerwerClient(SOCKET _socket, int _ID);

    bool Receive(void);
    void PrepareResponse();
    void Send(void);


    static const int bufferSize = 32;
    int ID;
    bool flagNewDataRecv;
    char recvBuffer[bufferSize];
    bool flagNewDataSend;
    char sendBuffer[bufferSize];
    SOCKET socketUsed;
};



class cSerwer
{
public:
    cSerwer(void);
    void Init(int _portNumber);
    void AcceptNewClients(void);
    void ReceiveData(void);
    void PrepareResponse();
    void SendData(void);
    QString wiadomosc;
    cSerwerClient* gracz1;
    cSerwerClient* gracz2;

    SOCKET socketUsed;

    void CleanUp(const char* error);
};

































#endif // CSERWER_H
