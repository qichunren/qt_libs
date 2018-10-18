#ifndef TIP_LABEL_H
#define TIP_LABEL_H

#include <QLabel>
#include <QTimer>

class TipLabel : public QLabel
{
    Q_OBJECT
public:
    /**
     *  TipLabel * tiplabel = new TipLabel(this);
     *  tiplabel->setFontSize(30);
     *  tiplabel->displayFailedMessage("Operation failed!", 1000)->center();
     *
     *  TipLabel * tiplabel = new TipLabel(this);
     *  tiplabel->setFontSize(30);
     *  tiplabel->displaySuccessMessage("Operation success!", 1000)->center();
     *
     */
    static void hide_current_label();

    explicit TipLabel(QWidget *parent = 0);
    void setFontSize(int fontsize);
    TipLabel * displaySuccessMessage(const QString &text, int displayInterval);
    TipLabel * displayFailedMessage(const QString &text, int displayInterval);

    TipLabel * center();
    void set_size(int width, int height);

private:
    void displayMessage(const QString &text, int displayInterval);

signals:
    void timeout();
    void clicked();

public slots:
    void hide();
    void slotClicked();

protected:
    void mousePressEvent ( QMouseEvent * event ) ;

private:
    QTimer * timer;
    int _width;
    int _height;
    int _fontsize;

};

#endif // TIP_LABEL_H
