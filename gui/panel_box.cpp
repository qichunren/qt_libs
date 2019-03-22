/*
# Copyright (c) 2018 Shanghai Novotech. All rights reserved.
# Author: Qichunren
# Email:  whyruby@gmail.com
*/

#include "panel_box.h"

#include <QDebug>

PanelBox::PanelBox(QWidget *parent) :
    QFrame(parent),
    _touched_count(0),
    _touched_count_threshold(10)
{
    setStyleSheet("PanelBox{background-color: #2a2a2a; border-left: 2px solid #616161;border-bottom: 2px solid #616161; border-top: 0px solid #000;border-right: 2px solid #616161;}");
    _timer.setSingleShot(true);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(touch_time_out()));
}

void PanelBox::set_touched_count_threshold(quint8 v) {
    _touched_count_threshold = v;
}

void PanelBox::mousePressEvent(QMouseEvent * event) {
    _touched_count++;

    if(_touched_count >= _touched_count_threshold) {
        _touched_count = 0;
        emit touches_actived();
    } else {
        _timer.start(1000);
    }
}

void PanelBox::touch_time_out() {
    _touched_count = 0;
}
