#include "firstWin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FirstWin f(nullptr);
    f.setWindowTitle(QString("Convolution and Correlation"));
    f.show();
    return a.exec();
}
