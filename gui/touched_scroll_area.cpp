/*
# Copyright (c) 2018 Shanghai Novotech. All rights reserved.
# Author: Qichunren
# Email:  whyruby@gmail.com
*/

#include "touched_scroll_area.h"

#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>

TouchedScrollArea::TouchedScrollArea(QWidget *parent) : QScrollArea(parent),
  _is_drag_moving(false),
  _start_x_value(0),
  _end_x_value(0)
{
}

void TouchedScrollArea::mouseMoveEvent(QMouseEvent *event)
{
    if(!_is_drag_moving)
    {
        _is_drag_moving = true;
        _start_x_value = event->pos().x();
    }
    else
    {
        _end_x_value = event->pos().x();
        int move_value = _start_x_value - _end_x_value;
        int current_x_value = this->horizontalScrollBar()->value();
        this->horizontalScrollBar()->setValue(current_x_value + move_value);
    }
}

void TouchedScrollArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(_is_drag_moving)
    {
        _is_drag_moving = false;
    }
}

