/*
# Copyright (c) 2018 Shanghai Novotech. All rights reserved.
# Author: Qichunren
# Email:  whyruby@gmail.com
*/

#include "focus_line_edit.h"

FocusLineEdit::FocusLineEdit(QWidget *parent) : QLineEdit(parent)
{

}

void FocusLineEdit::set_focus_status(bool flag) {
    if(flag) {
        setStyleSheet("border: 3px solid yellow;color: #000");
    } else {
        setStyleSheet("border: 3px solid #BDBDBD;color: #BDBDBD");
    }
}

void FocusLineEdit::focusInEvent(QFocusEvent *e)
{
  QLineEdit::focusInEvent(e);
  emit(focussed(true));
}

void FocusLineEdit::focusOutEvent(QFocusEvent *e)
{
  QLineEdit::focusOutEvent(e);
  emit(focussed(false));
}
