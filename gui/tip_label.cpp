#include "tip_label.h"
#include <QDebug>

static TipLabel * current_tip_label = NULL;

void TipLabel::hide_current_label()
{
    qDebug() << "hide_current_label" << current_tip_label;
    if(current_tip_label != NULL)
    {
        current_tip_label->hide();
    }
}

TipLabel::TipLabel(QWidget *parent) :
    QLabel(parent),
    timer(new QTimer(this)),
    _width(480),
    _height(80),
    _fontsize(14)
{
    connect(timer, SIGNAL(timeout()), SLOT(hide()));
    connect(this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );

    if(current_tip_label != NULL)
    {
        current_tip_label->hide();
    }
    current_tip_label = this;
}

void TipLabel::mousePressEvent ( QMouseEvent * )
{
    emit clicked();
}

void TipLabel::slotClicked()
{
    setVisible(false);
}

void TipLabel::setFontSize(int fontsize)
{
    _fontsize = fontsize;
}

void TipLabel::displayMessage(const QString &text, int displayInterval)
{
    setText(text);
    setVisible(true);
    timer->stop();
    timer->start(displayInterval);
}

TipLabel * TipLabel::displaySuccessMessage(const QString &text, int displayInterval)
{
    setStyleSheet(QString("color: #004085;border: 2px solid #b8daff;background-color: #cce5ff;font-size: %1px").arg(_fontsize));
    displayMessage(text, displayInterval);
    return this;
}

TipLabel * TipLabel::displayFailedMessage(const QString &text, int displayInterval)
{
    setStyleSheet(QString("color: #721c24;border: 2px solid #f5c6cb;background-color: #f8d7da; font-size: %1px").arg(_fontsize));
    displayMessage(text, displayInterval);
    return this;
}

TipLabel * TipLabel::center()
{
    QWidget *p;
    p = dynamic_cast<QWidget *>(parent());
    setGeometry(p->width()/2 - _width/2, p->height()/2 - _height/2, _width, _height);
    setAlignment(Qt::AlignCenter);
    return this;
}

void TipLabel::set_size(int width, int height)
{
    _width = width;
    _height = height;
}

void TipLabel::hide()
{
    if(current_tip_label != NULL)
    {
        current_tip_label = NULL;
    }
    timer->stop();
    clear();
    setVisible(false);
    emit timeout();
    delete this;

}
