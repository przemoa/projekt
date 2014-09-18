#include "glowneokno.h"
#include <QApplication>
#include "gra/naglowki.h"
#include "gra/cJednostka.h"

cPlansza* Plansza = 0;
int cJednostka::aktualneId = 0;


int main(int argc, char *argv[])
{
    srand(432);
    QApplication a(argc, argv);
    GlowneOkno w;
    w.show();

    return a.exec();
}

// PAMIETAC O LOKALIZACJI MAPY!
// IP i PORT!
// usunac sleep!!!
// czas timerow
