#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Linux命令工具二哥专用版");
    w.setFixedSize(600,600);
    w.show();

    return a.exec();
}
