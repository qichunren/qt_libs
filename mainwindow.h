#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_test_tip_label_1_clicked();

    void on_btn_test_tip_label_2_clicked();

    void on_btn_page_1_clicked();

    void on_btn_page_2_clicked();

    void when_keyboard_pressed(QString key);

    void on_play_button_clicked(bool checked);

private:
    void _setup_virtual_keyboard_widget();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
