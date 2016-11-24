#ifndef PAIGO_PLAYER_H
#define PAIGO_PLAYER_H

#include <QObject>
#include <gst/gst.h>
#include <QStringList>

#define PAIGOPlayer PaigoPlayer::instance()

class PaigoPlayer : public QObject
{
    Q_OBJECT
public:
    static gboolean busFunc(GstBus *bus, GstMessage *msg, void *user_data);
    static PaigoPlayer &instance();
    explicit PaigoPlayer(QObject *parent = 0);
    ~PaigoPlayer();
    void set_volume(gdouble value);
    void set_repeated(bool flag);
    quint16 audio_id();
    void mute(gboolean m);    

    bool play(const QString & file_path, quint16 audio_id = 0);
    bool dplay(quint64 digit);
    bool is_dplaying();
    void pop_front_meta_digits();
    bool is_meta_digits_empty();
    bool dplay_next_digit();
    void set_dplay_stop();

    void pause();
    void stop();
    void emit_play_finished();

signals:
    void play_finished(quint16 audio_id);

public slots:

private:
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;
    quint16 _audio_id_;

    QStringList meta_digits;
    bool _is_dplaying;
    bool _repeated_;

};

#endif // PAIGO_PLAYER_H
