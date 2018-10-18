#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gui/tip_label.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_test_tip_label_1_clicked()
{
    TipLabel * tiplabel = new TipLabel(this);
    tiplabel->setFontSize(30);
    tiplabel->displayFailedMessage("Operation failed!", 3000)->center();
}

void MainWindow::on_btn_test_tip_label_2_clicked()
{
    TipLabel * tiplabel = new TipLabel(this);
    tiplabel->setFontSize(30);
    tiplabel->displaySuccessMessage("Operation success!", 3000)->center();
}
