#include "glowneokno.h"
#include "ui_glowneokno.h"
#include "gra/naglowki.h"

GlowneOkno::GlowneOkno(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlowneOkno)
{
    ui->setupUi(this);

    serwer = new cSerwer();
    serwer->Init(3000);

    etapGry = WYBOR_WARUNKOW;

    timer = new QTimer(this);
    timer->start(30);

    connect(ui->commandLinkButton_akcja, SIGNAL(clicked()), this, SLOT(WykonajAkcje()));
    connect(timer, SIGNAL(timeout()), this, SLOT(Dzialaj()));
    connect(ui->dial_szybkoscGry, SIGNAL(valueChanged(int)), this, SLOT(ZmienionoPokretla()));
    connect(ui->dial_zlotoPoczatkowe, SIGNAL(valueChanged(int)), this, SLOT(ZmienionoPokretla()));

    ui->label_gracz1->setStyleSheet("QLabel { background-color : red; color : blue; }");
    ui->label_gracz2->setStyleSheet("QLabel { background-color : red; color : blue; }");

}

GlowneOkno::~GlowneOkno()
{
    delete serwer;
    delete ui;
}



void GlowneOkno::Dzialaj()
{

    if(!serwer->wiadomosc.isEmpty())
    {
        ui->textBrowser->append("<b> serwer:</b>   " + serwer->wiadomosc);
        serwer->wiadomosc = "";
    }




    if (etapGry == WYBOR_WARUNKOW)
    {
        return;
    }

    SprawdzGraczy();

    if (etapGry == GOTOWE_DO_ROZPOCZECIA)
    {
        return;
    }



    if (etapGry == OCZEKIWANIE_NA_GRACZY)
    {
        OczekujNaGraczy();
        return;
    }



    serwer->SendData();

    if(serwer->gracz1)   serwer->gracz1->bajtyDoWyslania = 0;
    if(serwer->gracz2)   serwer->gracz2->bajtyDoWyslania = 0;

    Plansza->bajtyBuforuDodan = 0;

//    while(serwer->gracz1->bajtyDoWyslania && serwer->gracz2->bajtyDoWyslania)
//    {
//        serwer->ReceiveData();
//    }

    serwer->ReceiveData();


    if(serwer->gracz1)    PrzetworzOdebraneDane(0);
    if(serwer->gracz2)    PrzetworzOdebraneDane(1);

    DzialajPlansze();

    if(serwer->gracz1)    PrzygotujDaneDoWyslania(0);
    if(serwer->gracz2)    PrzygotujDaneDoWyslania(1);





}

void GlowneOkno::WykonajAkcje()
{

    switch(etapGry)
    {
    case WYBOR_WARUNKOW:
        etapGry = OCZEKIWANIE_NA_GRACZY;
        ui->dial_zlotoPoczatkowe->hide();
        ui->dial_szybkoscGry->hide();
        ui->radioButton_1gracz->setEnabled(false);
        ui->radioButton_2graczy->setEnabled(false);
        ui->label_StanGry->setText("Oczekiwanie na graczy");
        ui->commandLinkButton_akcja->hide();

        iloscGraczy = 1 + ui->radioButton_2graczy->isChecked();
        Plansza = new cPlansza();
        Plansza->tabGraczy[0]->zloto = Plansza->tabGraczy[1]->zloto = ui->dial_zlotoPoczatkowe->value();
        break;

    case GOTOWE_DO_ROZPOCZECIA:
        etapGry = GRA;
        ui->commandLinkButton_akcja->setText("Zatrzymaj ...");
        break;

    default:
        break;
    }


}

void GlowneOkno::OczekujNaGraczy()
{
    serwer->AcceptNewClients();

    if ((iloscGraczy == 1 && serwer->gracz1) || (iloscGraczy == 2 && serwer->gracz1 && serwer->gracz2))
    {
        etapGry = GOTOWE_DO_ROZPOCZECIA;
        WyslijWarunki();
        ui->label_StanGry->setText("Gotowe do ropoczecia");
        ui->commandLinkButton_akcja->show();
        ui->commandLinkButton_akcja->setText("Rozpocznij gre");
    }
}

void GlowneOkno::SprawdzGraczy()
{

    if (serwer->gracz1)
        ui->label_gracz1->setStyleSheet("QLabel { background-color : lightGreen; color : blue; }");
    else
        ui->label_gracz1->setStyleSheet("QLabel { background-color : red; color : blue; }");


    if (iloscGraczy == 2)
    {
        if (serwer->gracz2)
            ui->label_gracz2->setStyleSheet("QLabel { background-color : lightGreen; color : blue; }");
        else
            ui->label_gracz2->setStyleSheet("QLabel { background-color : red; color : blue; }");
    }
    else
    {
        ui->label_gracz2->setStyleSheet("QLabel { background-color : lightGreen; color : blue; }");
    }

}

void GlowneOkno::WyslijWarunki()
{ 

    if (serwer->gracz1)
    {
        int ile = 8;
        serwer->gracz1->bajtyDoWyslania = ile;
        serwer->gracz1->buforWysylania[0] = 0x01;
        memcpy(serwer->gracz1->buforWysylania+1, &(Plansza->tabGraczy[0]->zloto), 4);
        serwer->gracz1->buforWysylania[5] = 0x00;       // gracz 1 jest graczem 1;
        serwer->gracz1->buforWysylania[6] = 0x00;
        serwer->gracz1->buforWysylania[7] = 0x00;
    }

    if (serwer->gracz2)
    {
        int ile = 8;
        serwer->gracz2->bajtyDoWyslania = ile;
        serwer->gracz2->buforWysylania[0] = 0x01;
        memcpy(serwer->gracz2->buforWysylania+1, &(Plansza->tabGraczy[1]->zloto), 4);
        serwer->gracz2->buforWysylania[5] = 0x01;       // gracz 2 jest graczem 2;
        serwer->gracz2->buforWysylania[6] = 0x00;
        serwer->gracz2->buforWysylania[7] = 0x00;
    }
}

void GlowneOkno::PrzygotujDaneDoWyslania(int ktoryGracz)
{
    cSerwerClient* klient;
    if (ktoryGracz == 0) klient = serwer->gracz1;
    if (ktoryGracz == 1) klient = serwer->gracz2;

    if (klient)
    {
        klient->bajtyDoWyslania = Plansza->bajtyBuforuDodan;
        memcpy(klient->buforWysylania, Plansza->buforDodan, Plansza->bajtyBuforuDodan);
    }

    cGracz* kto = Plansza->tabGraczy[ktoryGracz];
    cGracz* kto1 = Plansza->tabGraczy[0];
    cGracz* kto2 = Plansza->tabGraczy[1];

    klient->DodajBajty(0x01);
    klient->DodajInt(kto->zloto);


    klient->DodajBajty(0x30);
    klient->DodajInt((int) kto1->tabStworkow.size());
    for (int i = 0; i < kto1->tabStworkow.size(); i++)
    {
        klient->DodajFloat(kto1->tabStworkow[i]->x);
        klient->DodajFloat(kto1->tabStworkow[i]->y);
        klient->DodajFloat(kto1->tabStworkow[i]->poziomZycia);
    }


    klient->DodajBajty(0x31);
    klient->DodajInt((int) kto2->tabStworkow.size());
    for (int i = 0; i < kto2->tabStworkow.size(); i++)
    {
        klient->DodajFloat(kto2->tabStworkow[i]->x);
        klient->DodajFloat(kto2->tabStworkow[i]->y);
        klient->DodajFloat(kto2->tabStworkow[i]->poziomZycia);
    }

    klient->DodajBajty(0x32);
    for (int i = 0; i < 3; i++)
    {
        if (!kto1->tabBohaterow[i]) klient->DodajBajty(0);
        else
        {
            if (!kto1->tabBohaterow[i]->zywy) klient->DodajBajty(0);
            else
            {
                klient->DodajBajty(1);
                klient->DodajFloat(kto1->tabBohaterow[i]->x);
                klient->DodajFloat(kto1->tabBohaterow[i]->y);
                klient->DodajFloat(kto1->tabBohaterow[i]->poziomZycia);
                klient->DodajFloat(kto1->tabBohaterow[i]->obrazenia);
                klient->DodajFloat(kto1->tabBohaterow[i]->zasieg);
                klient->DodajFloat(kto1->tabBohaterow[i]->mocSilnika);
                klient->DodajFloat(kto1->tabBohaterow[i]->energia);
                klient->DodajInt(kto1->tabBohaterow[i]->level);
                klient->DodajInt(kto1->tabBohaterow[i]->doswiadczenie);
                klient->DodajInt(kto1->tabBohaterow[i]->szybkoscAtaku);
                klient->DodajFloat(kto1->tabBohaterow[i]->mnoznikZycia);
            }
        }
    }


    klient->DodajBajty(0x33);
    for (int i = 0; i < 3; i++)
    {
        if (!kto2->tabBohaterow[i]) klient->DodajBajty(0);
        else
        {
            if (!kto2->tabBohaterow[i]->zywy) klient->DodajBajty(0);
            else
            {
                klient->DodajBajty(1);
                klient->DodajFloat(kto2->tabBohaterow[i]->x);
                klient->DodajFloat(kto2->tabBohaterow[i]->y);
                klient->DodajFloat(kto2->tabBohaterow[i]->poziomZycia);
                klient->DodajFloat(kto2->tabBohaterow[i]->obrazenia);
                klient->DodajFloat(kto2->tabBohaterow[i]->zasieg);
                klient->DodajFloat(kto2->tabBohaterow[i]->mocSilnika);
                klient->DodajFloat(kto2->tabBohaterow[i]->energia);
                klient->DodajInt(kto2->tabBohaterow[i]->level);
                klient->DodajInt(kto2->tabBohaterow[i]->doswiadczenie);
                klient->DodajInt(kto2->tabBohaterow[i]->szybkoscAtaku);
                klient->DodajFloat(kto2->tabBohaterow[i]->mnoznikZycia);

            }
        }
    }


    klient->DodajBajty(0x34);
    klient->DodajInt(kto1->zamek->level);
    klient->DodajInt(kto1->zamek->doswiadczenie);
    klient->DodajInt(kto1->zamek->wydobycie);
    klient->DodajFloat(kto1->zamek->poziomZycia);
    klient->DodajFloat(kto1->zamek->mnoznikZycia);


    klient->DodajBajty(0x35);
    klient->DodajInt(kto2->zamek->level);
    klient->DodajInt(kto2->zamek->doswiadczenie);
    klient->DodajInt(kto2->zamek->wydobycie);
    klient->DodajFloat(kto2->zamek->poziomZycia);
    klient->DodajFloat(kto2->zamek->mnoznikZycia);













    klient->DodajBajty(0, 0);
}

void GlowneOkno::PrzetworzOdebraneDane(int ktoryGracz)
{

    cSerwerClient* klient;
    if (ktoryGracz == 0) klient = serwer->gracz1;
    if (ktoryGracz == 1) klient = serwer->gracz2;


    if (klient)
    {
        int cenyWiez[8] = {300, 200, 450, 1200, 250, 800, 600, 0};
        char drugiBajt = 0;
        char trzeciBajt = 0;
        cGracz* kto = Plansza->tabGraczy[ktoryGracz];

        for (int licznik = 1; licznik <= klient->bajtyOdebrane; licznik++)
        {
            switch (klient->buforOdbioru[licznik])
            {
            case 0x04:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];
                kto->DodajBohatera(drugiBajt);
                break;
            case 0x07:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];
                kto->DodajStworka(drugiBajt);
                break;
            case  0x0B:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];
                if (kto->ZaplacZlotem(200)) kto->tabBohaterow[drugiBajt]->Awansuj();
                break;
            case  0x0C:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];
                if (kto->ZaplacZlotem(150)) kto->tabBohaterow[drugiBajt]->ZwiekszMoc();
                break;
            case  0x0D:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];
                if (kto->ZaplacZlotem(30)) kto->tabBohaterow[drugiBajt]->Teleportuj();
                break;

            case 0x14:
                kto->AwansujStworki();
                break;
            case 0x15:
                if (kto->ZaplacZlotem(500)) kto->zamek->Awansuj();
                break;

            case 0x20:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];
                kto->tabBohaterow[drugiBajt]->Przyspieszaj(-KROK_PRZYSPIESZANIA_BOHATERA, 0);
                break;
            case 0x21:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];
                kto->tabBohaterow[drugiBajt]->Przyspieszaj(KROK_PRZYSPIESZANIA_BOHATERA, 0);
                break;

            case 0x1D:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];

                if (kto->ZaplacZlotem((int) (cenyWiez[kto->zamek->tabWiez[drugiBajt].typWiezy-11]/2.0)))
                {
                    kto->zamek->AwansujWieze(drugiBajt);
                }
                break;
            case 0x1E:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];
                kto->ZaplacZlotem(-80*kto->zamek->tabWiez[drugiBajt].level);
                kto->zamek->SprzedajWieze(drugiBajt);
                break;
            case 0x16:
                licznik++;
                drugiBajt = klient->buforOdbioru[licznik];
                licznik++;
                trzeciBajt = klient->buforOdbioru[licznik];
                if (kto->ZaplacZlotem(cenyWiez[drugiBajt-11])) kto->zamek->DodajWieze(drugiBajt, trzeciBajt*100);
                break;
            case 0x00:
                return;
                break;
            }
        }


    }
}


void GlowneOkno::DzialajPlansze()
{
    Plansza->tabGraczy[0]->Dzialaj();
    Plansza->tabGraczy[1]->Dzialaj();

}





void GlowneOkno::ZmienionoPokretla()
{
    ui->lcdNumber_szybkoscGry->display(ui->dial_szybkoscGry->value());
    ui->lcdNumber_zlotoPoczatkowe->display(ui->dial_zlotoPoczatkowe->value());
}

void GlowneOkno::keyPressEvent(QKeyEvent *key)
{
  //  strcpy_s(serwer->gracz1->buforWysylania, 10, "yooo siaa");
  //  serwer->gracz1->bajtyDoWyslania = 10;


}
