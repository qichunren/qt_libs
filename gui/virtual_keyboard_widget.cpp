/*
# Copyright (c) 2018 Shanghai Novotech. All rights reserved.
# Author: Qichunren
# Email:  whyruby@gmail.com
*/

#include "virtual_keyboard_widget.h"
#include "ui_virtualkeyboardwidget.h"

VirtualKeyboardWidget::VirtualKeyboardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VirtualKeyboardWidget)
{
    ui->setupUi(this);
    ui->btn_back->setStyleSheet("QPushButton{background-color: #718ea4;color:#FFF;}");
}

VirtualKeyboardWidget::~VirtualKeyboardWidget()
{
    delete ui;
}

void VirtualKeyboardWidget::on_btn_key1_clicked()
{
    emit key_typed("1");
}

void VirtualKeyboardWidget::on_btn_key2_clicked()
{
    emit key_typed("2");
}

void VirtualKeyboardWidget::on_btn_key3_clicked()
{
    emit key_typed("3");
}

void VirtualKeyboardWidget::on_btn_key4_clicked()
{
    emit key_typed("4");
}

void VirtualKeyboardWidget::on_btn_key5_clicked()
{
    emit key_typed("5");
}

void VirtualKeyboardWidget::on_btn_key6_clicked()
{
    emit key_typed("6");
}

void VirtualKeyboardWidget::on_btn_key7_clicked()
{
    emit key_typed("7");
}

void VirtualKeyboardWidget::on_btn_key8_clicked()
{
    emit key_typed("8");
}

void VirtualKeyboardWidget::on_btn_key9_clicked()
{
    emit key_typed("9");
}

void VirtualKeyboardWidget::on_btn_key0_clicked()
{
    emit key_typed("0");
}

void VirtualKeyboardWidget::on_btn_reset_clicked()
{
    emit reset_pressed();
}

void VirtualKeyboardWidget::on_btn_ok_clicked()
{
    emit ok_pressed();
}

void VirtualKeyboardWidget::on_btn_back_clicked()
{
    emit cacel_pressed();
}

void VirtualKeyboardWidget::on_btn_keyq_clicked()
{
    emit key_typed("Q");
}

void VirtualKeyboardWidget::on_btn_keyw_clicked()
{
    emit key_typed("W");
}

void VirtualKeyboardWidget::on_btn_keye_clicked()
{
    emit key_typed("E");
}

void VirtualKeyboardWidget::on_btn_keyr_clicked()
{
    emit key_typed("R");
}

void VirtualKeyboardWidget::on_btn_keyt_clicked()
{
    emit key_typed("T");
}

void VirtualKeyboardWidget::on_btn_keyy_clicked()
{
    emit key_typed("Y");
}

void VirtualKeyboardWidget::on_btn_keyu_clicked()
{
    emit key_typed("U");
}

void VirtualKeyboardWidget::on_btn_keyi_clicked()
{
    emit key_typed("I");
}

void VirtualKeyboardWidget::on_btn_keyo_clicked()
{
    emit key_typed("O");
}

void VirtualKeyboardWidget::on_btn_keyp_clicked()
{
    emit key_typed("P");
}

void VirtualKeyboardWidget::on_btn_keya_clicked()
{
    emit key_typed("A");
}

void VirtualKeyboardWidget::on_btn_keys_clicked()
{
    emit key_typed("S");
}

void VirtualKeyboardWidget::on_btn_keyd_clicked()
{
    emit key_typed("D");
}

void VirtualKeyboardWidget::on_btn_keyf_clicked()
{
    emit key_typed("F");
}

void VirtualKeyboardWidget::on_btn_keyg_clicked()
{
    emit key_typed("G");
}

void VirtualKeyboardWidget::on_btn_keyh_clicked()
{
    emit key_typed("H");
}

void VirtualKeyboardWidget::on_btn_keyj_clicked()
{
    emit key_typed("J");
}

void VirtualKeyboardWidget::on_btn_keyk_clicked()
{
    emit key_typed("K");
}

void VirtualKeyboardWidget::on_btn_keyl_clicked()
{
    emit key_typed("L");
}

void VirtualKeyboardWidget::on_btn_keyz_clicked()
{
    emit key_typed("Z");
}

void VirtualKeyboardWidget::on_btn_keyx_clicked()
{
    emit key_typed("X");
}

void VirtualKeyboardWidget::on_btn_keyc_clicked()
{
    emit key_typed("C");
}

void VirtualKeyboardWidget::on_btn_keyv_clicked()
{
    emit key_typed("V");
}

void VirtualKeyboardWidget::on_btn_keyb_clicked()
{
    emit key_typed("B");
}

void VirtualKeyboardWidget::on_btn_keyn_clicked()
{
    emit key_typed("N");
}

void VirtualKeyboardWidget::on_btn_keym_clicked()
{
    emit key_typed("M");
}
