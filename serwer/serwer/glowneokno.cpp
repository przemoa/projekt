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

    if (etapGry == WYBOR_WARUNKOW)
        return;

    if (etapGry == OCZEKIWANIE_NA_GRACZY)
        OczekujNaGraczy();

    SprawdzGraczy();


    serwer->ReceiveData();
  //  serwer->PrepareResponse();
   // serwer->SendData();






   if(!serwer->wiadomosc.isEmpty())
   {
       ui->textBrowser->append("<b> serwer:</b>   " + serwer->wiadomosc);
       serwer->wiadomosc = "";
   }


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
        break;

    case GOTOWE_DO_ROZPOCZECIA:
        etapGry = GRA;
        ui->commandLinkButton_akcja->setText("Zatrzymaj ...");
        break;
    }


}

void GlowneOkno::OczekujNaGraczy()
{
    serwer->AcceptNewClients();

    if ((iloscGraczy == 1 && serwer->gracz1) || (iloscGraczy == 2 && serwer->gracz1 && serwer->gracz2))
    {
        etapGry = GOTOWE_DO_ROZPOCZECIA;
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

void GlowneOkno::ZmienionoPokretla()
{
    ui->lcdNumber_szybkoscGry->display(ui->dial_szybkoscGry->value());
    ui->lcdNumber_zlotoPoczatkowe->display(ui->dial_zlotoPoczatkowe->value());
}

void GlowneOkno::keyPressEvent(QKeyEvent *key)
{
    strcpy_s(serwer->gracz1->sendBuffer, serwer->gracz1->bufferSize, "nom");
    serwer->gracz1->flagNewDataSend = true;

}
