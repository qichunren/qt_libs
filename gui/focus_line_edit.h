/*
# Copyright (c) 2018 Shanghai Novotech. All rights reserved.
# Author: Qichunren
# Email:  whyruby@gmail.com
*/

#ifndef FOCUSLINEEDIT_H
#define FOCUSLINEEDIT_H

#include <QLineEdit>

class FocusLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit FocusLineEdit(QWidget *parent = 0);

    void set_focus_status(bool flag);

signals:
  void focussed(bool hasFocus);

public slots:

protected:
  virtual void focusInEvent(QFocusEvent *e);
  virtual void focusOutEvent(QFocusEvent *e);
};

#endif // FOCUSLINEEDIT_H
