/*
# Copyright (c) 2018 Shanghai Novotech. All rights reserved.
# Author: Qichunren
# Email:  whyruby@gmail.com
*/

#ifndef PANELBOX_H
#define PANELBOX_H

#include <QFrame>
#include <QTimer>

class PanelBox : public QFrame
{
    Q_OBJECT
public:
    explicit PanelBox(QWidget * parent = 0);
    void set_touched_count_threshold(quint8 v);

signals:
    void touches_actived();

private slots:
    void touch_time_out();

protected:
    void mousePressEvent(QMouseEvent * event);

private:
    quint8 _touched_count;
    quint8 _touched_count_threshold;
    QTimer _timer;
};

#endif // PANELBOX_H
