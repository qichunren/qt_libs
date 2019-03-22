/*
# Copyright (c) 2018 Shanghai Novotech. All rights reserved.
# Author: Qichunren
# Email:  whyruby@gmail.com
*/

#ifndef TOUCHEDSCROLLAREA_H
#define TOUCHEDSCROLLAREA_H

#include <QScrollArea>

class TouchedScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit TouchedScrollArea(QWidget *parent = 0);

signals:

public slots:

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool _is_drag_moving;
    int _start_x_value;
    int _end_x_value;
};

#endif // TOUCHEDSCROLLAREA_H
