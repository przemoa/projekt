#ifndef GLOWNEOKNO_H
#define GLOWNEOKNO_H

#include <QMainWindow>
#include "cSerwer.h"
#include <QTimer>
#include "gra/cPlansza.h"


enum eETAPGRY
{
    WYBOR_WARUNKOW = 0, OCZEKIWANIE_NA_GRACZY, GOTOWE_DO_ROZPOCZECIA, GRA, UTRACONO_POLACZENIE, KONIEC_GRY, PAUZA
};






namespace Ui {
class GlowneOkno;
}

class GlowneOkno : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlowneOkno(QWidget *parent = 0);
    ~GlowneOkno();
    void keyPressEvent(QKeyEvent *key);
    eETAPGRY etapGry;
    int iloscGraczy;

public slots:
    void Dzialaj();
    void WykonajAkcje();
    void OczekujNaGraczy();
    void SprawdzGraczy();
    void ZmienionoPokretla();
    void WyslijWarunki();       // warunki poczatkowe gry (zloto)

    void PrzygotujDaneDoWyslania(int ktoryGracz);
    void PrzetworzOdebraneDane(int ktoryGracz);         //0 lub 1
    void DzialajPlansze();

private:
    Ui::GlowneOkno *ui;
    cSerwer* serwer;
    QTimer *timer;
};

#endif // GLOWNEOKNO_H
