#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString css_text;
    QFile css_file(":/styles/default_style.css");
    if(!css_file.open(QIODevice::ReadOnly)) {
        qDebug() << "filen ot opened";
    }
    else
    {
        css_text = css_file.readAll();
    }
    css_file.close();

    a.setStyleSheet(css_text);

    MainWindow w;
    w.show();

    return a.exec();
}
