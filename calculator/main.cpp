#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("Expression evaluator");
    w.setGeometry(600,400,600,400);
    w.show();
    
    return a.exec();
}
