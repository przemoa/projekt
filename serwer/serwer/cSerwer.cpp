

#include "cSerwer.h"


cSerwerClient::cSerwerClient(SOCKET _socket, int _ID)
{
    this->socketUsed = _socket;
    this->ID = _ID;

    this->bajtyOdebrane = 0;
    this->bajtyDoWyslania = 0;

    memset(this->buforOdbioru, 0, ROZMIAR_BUFORA_ODBIORU);
    memset(this->buforWysylania, 0, ROZMIAR_BUFORA_WYSYLANIA);
}



void cSerwerClient::DodajBajty(char pierwszy, char drugi , char trzeci, char czwarty, char piaty)
{

    buforWysylania[bajtyDoWyslania] = pierwszy;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = drugi;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = trzeci;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = czwarty;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = piaty;
    bajtyDoWyslania++;
}

void cSerwerClient::DodajBajty(char pierwszy, char drugi , char trzeci, char czwarty)
{

    buforWysylania[bajtyDoWyslania] = pierwszy;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = drugi;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = trzeci;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = czwarty;
    bajtyDoWyslania++;
}

void cSerwerClient::DodajBajty(char pierwszy, char drugi , char trzeci)
{

    buforWysylania[bajtyDoWyslania] = pierwszy;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = drugi;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = trzeci;
    bajtyDoWyslania++;
}

void cSerwerClient::DodajBajty(char pierwszy, char drugi)
{

    buforWysylania[bajtyDoWyslania] = pierwszy;
    bajtyDoWyslania++;

    buforWysylania[bajtyDoWyslania] = drugi;
    bajtyDoWyslania++;
}

void cSerwerClient::DodajBajty(char pierwszy)
{

    buforWysylania[bajtyDoWyslania] = pierwszy;
    bajtyDoWyslania++;
}


void cSerwerClient::DodajInt(int dodaj)
{
    memcpy(buforWysylania+bajtyDoWyslania, &dodaj, 4);
    bajtyDoWyslania += 4;
}

void cSerwerClient::DodajFloat(float dodaj)
{
    memcpy(buforWysylania+bajtyDoWyslania, &dodaj, 4);
    bajtyDoWyslania += 4;
}





bool cSerwerClient::Odbierz(void)
{
    bool flagClientConnected = true;

    int bytesRecv = recv(this->socketUsed, this->buforOdbioru, ROZMIAR_BUFORA_ODBIORU, 0);
    int nError = WSAGetLastError();
    if (nError != WSAEWOULDBLOCK && nError != WSAENOTSOCK && nError != 0)
    {
        //std::cout << "Winsock error code: " << nError << std::endl;
        if (nError == WSAECONNRESET)
        {
            //std::cout << "Client disconnected!" << std::endl;

            // Shutdown our socket
            shutdown(this->socketUsed, SD_SEND);

            // Close our socket entirely
            closesocket(this->socketUsed);

            flagClientConnected = false;
        }
    }
    else
    {
        if (bytesRecv > 0)
        {
            bajtyOdebrane = bytesRecv;
        }
        else
        {
            bajtyOdebrane = 0;
        }
    }

    return flagClientConnected;
}

//void cSerwerClient::PrepareResponse()
//{
//    if (this->flagNewDataRecv)
//    {
//        strcpy_s(this->sendBuffer, this->bufferSize, "nom");

//        memset(this->recvBuffer, 0, this->bufferSize);
//        this->flagNewDataRecv = false;
//        this->flagNewDataSend = true;
//    }
//}

void cSerwerClient::Wyslij(void)
{
    if (bajtyDoWyslania)
    {
        send(this->socketUsed, this->buforWysylania, bajtyDoWyslania, 0);
        memset(this->buforWysylania, 0, ROZMIAR_BUFORA_WYSYLANIA);
        bajtyDoWyslania = 0;
    }
}


cSerwer::cSerwer(void)
{
    this->socketUsed = 0;
    gracz1 = NULL;
    gracz2 = NULL;
    wiadomosc = "";
}

void cSerwer::Init(int _portNumber)
{
    // initialize Windows Sockets API
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
        this->CleanUp("Error at WSAStartup().");
    }

    // create a socket
    this->socketUsed = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketUsed == INVALID_SOCKET)
    {
        this->CleanUp("Error at the socket() function.");
    }

    // change the server socket to a non-blocking state
    u_long NonBlock = 1;
    if (ioctlsocket(this->socketUsed, FIONBIO, &NonBlock) == SOCKET_ERROR)
    {
        this->CleanUp("Setting non blocking mode failed.");
    }

    // bind the socket
    sockaddr_in server_service;
    server_service.sin_family = AF_INET;
    server_service.sin_addr.s_addr = INADDR_ANY;
    server_service.sin_port = htons(_portNumber);
    if (bind(this->socketUsed, (SOCKADDR*)&server_service, sizeof(server_service)) == SOCKET_ERROR)
    {
        this->CleanUp("Error during the bind() operation.");
    }

    // listen on the socket
    if (listen(this->socketUsed, 10) == SOCKET_ERROR)
    {
        this->CleanUp("Error listening on the socket.");
    }
}

void cSerwer::AcceptNewClients(void)
{
    if (gracz1 == NULL || gracz2 == NULL)
    {
        sockaddr sockAddrClient;
        int size = sizeof(sockaddr);
        SOCKET newClientSocket = accept(this->socketUsed, &sockAddrClient, &size);
        if (newClientSocket != SOCKET_ERROR)
        {


            if (gracz1 == NULL)
            {
                gracz1 = new cSerwerClient(newClientSocket, 1);
                wiadomosc += "gracz1 polaczony ";
            }
            else
            {
                gracz2 = new cSerwerClient(newClientSocket, 2);
                wiadomosc += "gracz2 polaczony ";
            }
        }
    }
}

void cSerwer::ReceiveData(void)
{

    // for all available clients receive the data, in case of disconnection remove client from the list

    if (gracz1)
    {
        gracz1->bajtyOdebrane = 0;
        while(!gracz1->bajtyOdebrane)
        {
            bool flagClientConnected = (*gracz1).Odbierz();
            if (!flagClientConnected)
            {
                wiadomosc += "Gracz1 rozlaczony";
                gracz1 = NULL;
                return;
            }
        }
    }


    if (gracz2)
    {
        while(!gracz2->bajtyOdebrane)
        {
            gracz2->bajtyOdebrane = 0;
            bool flagClientConnected = (*gracz2).Odbierz();
            if (!flagClientConnected)
            {
                wiadomosc += "Gracz2 rozlaczony";
                gracz2 = NULL;
                return;
            }
        }

    }


}


//void cSerwer::PrepareResponse()
//{
//    if(gracz1)
//    {
//        (*gracz1).PrepareResponse();
//    }

//    if(gracz2)
//    {
//        (*gracz2).PrepareResponse();
//    }
//}

void cSerwer::SendData(void)
{
    // for all available clients send the prepared data
    if(gracz1)
    {
        gracz1->Wyslij();
    }

    if(gracz2)
    {
        gracz2->Wyslij();
    }
}



void cSerwer::CleanUp(const char* error)
{
    std::cout << error << " Error number: " << WSAGetLastError() << std::endl;

    if (this->socketUsed != 0)
    {
        closesocket(this->socketUsed);
    }
    WSACleanup();

    //std::exception e(error);
    //throw e;
}
