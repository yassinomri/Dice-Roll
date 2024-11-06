#include "DiceController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiceController w;
    w.show();
    return a.exec();
}
