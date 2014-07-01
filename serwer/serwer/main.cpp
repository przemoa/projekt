#include "glowneokno.h"
#include <QApplication>
#include "gra/naglowki.h"
#include "gra/cJednostka.h"

cPlansza* Plansza = 0;
int cJednostka::aktualneId = 0;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlowneOkno w;
    w.show();

    return a.exec();
}
