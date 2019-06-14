#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gui/tip_label.h"
#include "gui/virtual_keyboard_widget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _setup_virtual_keyboard_widget();

    ui->btn_page_1->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_setup_virtual_keyboard_widget() {
    VirtualKeyboardWidget * keyboard = new VirtualKeyboardWidget(ui->widget_keyboard_container);
    connect(keyboard, SIGNAL(key_typed(QString)), this, SLOT(when_keyboard_pressed(QString)));
}

void MainWindow::when_keyboard_pressed(QString key) {
    QString typed = ui->lineEdit_input->text();
    ui->lineEdit_input->setText(typed + key);
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

void MainWindow::on_btn_page_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_page_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_play_button_clicked(bool checked)
{
    if(checked) {
        QIcon pause_icon(":/icons/images/pause-button.png");
        ui->play_button->setIcon(pause_icon);
        ui->play_button->setText("Pause");
    } else {
        QIcon play_icon(":/icons/images/music-player-play.png");
        ui->play_button->setIcon(play_icon);
        ui->play_button->setText("Play");
    }
}
