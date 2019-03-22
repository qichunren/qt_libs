/*
# Copyright (c) 2018 Shanghai Novotech. All rights reserved.
# Author: Qichunren
# Email:  whyruby@gmail.com
*/

#ifndef VIRTUAL_KEYBOARD_WIDGET_H
#define VIRTUAL_KEYBOARD_WIDGET_H

#include <QWidget>

namespace Ui {
class VirtualKeyboardWidget;
}

class VirtualKeyboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VirtualKeyboardWidget(QWidget *parent = 0);
    ~VirtualKeyboardWidget();

signals:
    void key_typed(const QString & key_value);
    void reset_pressed();
    void ok_pressed();
    void cacel_pressed();

private slots:
    void on_btn_key1_clicked();

    void on_btn_key2_clicked();

    void on_btn_key3_clicked();

    void on_btn_key4_clicked();

    void on_btn_key5_clicked();

    void on_btn_key6_clicked();

    void on_btn_key7_clicked();

    void on_btn_key8_clicked();

    void on_btn_key9_clicked();

    void on_btn_key0_clicked();

    void on_btn_reset_clicked();

    void on_btn_ok_clicked();

    void on_btn_back_clicked();

    void on_btn_keyq_clicked();

    void on_btn_keyw_clicked();

    void on_btn_keye_clicked();

    void on_btn_keyr_clicked();

    void on_btn_keyt_clicked();

    void on_btn_keyy_clicked();

    void on_btn_keyu_clicked();

    void on_btn_keyi_clicked();

    void on_btn_keyo_clicked();

    void on_btn_keyp_clicked();

    void on_btn_keya_clicked();

    void on_btn_keys_clicked();

    void on_btn_keyd_clicked();

    void on_btn_keyf_clicked();

    void on_btn_keyg_clicked();

    void on_btn_keyh_clicked();

    void on_btn_keyj_clicked();

    void on_btn_keyk_clicked();

    void on_btn_keyl_clicked();

    void on_btn_keyz_clicked();

    void on_btn_keyx_clicked();

    void on_btn_keyc_clicked();

    void on_btn_keyv_clicked();

    void on_btn_keyb_clicked();

    void on_btn_keyn_clicked();

    void on_btn_keym_clicked();

private:
    Ui::VirtualKeyboardWidget *ui;
};

#endif // VIRTUAL_KEYBOARD_WIDGET_H
