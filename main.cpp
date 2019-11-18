#include "klasaglowna.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KlasaGlowna w;
    w.show();

    return a.exec();
}
