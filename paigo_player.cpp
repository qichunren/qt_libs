#include "paigo_player.h"
#include <QFileInfo>
#include <QDebug>


gboolean PaigoPlayer::busFunc(GstBus *bus, GstMessage *msg, void *user_data)
{
    Q_UNUSED(bus);
    PaigoPlayer *player = (PaigoPlayer *)user_data;
    switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_EOS: {
        if(player->is_dplaying()) {
            player->pop_front_meta_digits();
            if(player->is_meta_digits_empty()) {
                player->set_dplay_stop();
                // finished whole dplay;
            } else {
                player->dplay_next_digit();
            }
            return TRUE;
        }


        if(player->audio_id() > 0)
            player->emit_play_finished();
        break;
    }
    case GST_MESSAGE_ERROR: {
        qDebug("case GST_MESSAGE_ERROR\n");
        GError *err;
        gst_message_parse_error(msg, &err, NULL);
        g_warning("%s", err->message);
        g_error_free(err);
        break;
    }
    default:
        //qDebug("case default message\n");
        break;
    }

    return TRUE;
}

PaigoPlayer& PaigoPlayer::instance() {
    static PaigoPlayer _instance;
    return _instance;
}

PaigoPlayer::PaigoPlayer(QObject *parent) :
    QObject(parent),
    pipeline(NULL),
    bus(NULL),
    msg(NULL),
    _is_dplaying(false),
    _repeated_(false)
{
    /* 初始化 GStreamer */
    gst_init (NULL, NULL);
    // playbin video-sink=fakesink audio-sink="audioconvert ! audioresample ! audio/x-raw, rate=48000, channels=1, format=S16LE ! alsasink"

    pipeline = gst_parse_launch("playbin video-sink=fakesink "
        "audio-sink=\"audioconvert ! audioresample ! "
        "audio/x-raw, rate=48000, channels=1, format=S16LE ! alsasink\"", NULL);

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus, busFunc, this);
}

PaigoPlayer::~PaigoPlayer() {
    if (msg != NULL)
        gst_message_unref (msg);
    if(bus != NULL)
        gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
}

void PaigoPlayer::set_volume(gdouble value) {
    if(value < 0.0 || value > 1.0)
        return;
    g_object_set(pipeline, "volume", value, NULL);
}

void PaigoPlayer::set_repeated(bool flag)
{
    _repeated_ = flag;
}

quint16 PaigoPlayer::audio_id() {
    return _audio_id_;
}

void PaigoPlayer::mute(gboolean m) {
    g_object_set(pipeline, "mute", m, NULL);
}

bool PaigoPlayer::play(const QString & file_path, quint16 audio_id) {
    if(file_path == "")
        return false;

    bool ret = true;
    QByteArray pathRaw = file_path.toUtf8();
    gchar *uri = g_filename_to_uri(pathRaw.constData(), NULL, NULL);

    QFileInfo audio_file_info(file_path);
    if(audio_file_info.exists() && audio_file_info.isReadable()) {
        gst_element_set_state (pipeline, GST_STATE_NULL);
        g_object_set(pipeline, "uri", uri, NULL);
        gst_element_set_state (pipeline, GST_STATE_PLAYING);
        _audio_id_ = audio_id;
    } else {
        qDebug() << "Unable to read audio file" << file_path;
        ret = false;
    }

    g_free(uri);
    return ret;
}

bool PaigoPlayer::is_dplaying() {
    return _is_dplaying;
}

void PaigoPlayer::pop_front_meta_digits() {
    meta_digits.pop_front();
}

bool PaigoPlayer::is_meta_digits_empty() {
    return meta_digits.isEmpty();
}

bool PaigoPlayer::dplay_next_digit() {
    return play(meta_digits.first());
}

void PaigoPlayer::set_dplay_stop() {
    _is_dplaying = false;
}

bool PaigoPlayer::dplay(quint64 digit) {    
    meta_digits.clear();
    _is_dplaying = true;
    if(digit < 11) {
        QString d_file = QString("/usr/share/paigo/audios/meta/digit_%1.wav").arg(digit);
        meta_digits.append(d_file);
    } else if(digit < 100) {
        int first_d = digit / 10;
        int last_d = digit % 10;
        QString first_d_file = QString("/usr/share/paigo/audios/meta/digit_%1.wav").arg(first_d);
        QString last_d_file = QString("/usr/share/paigo/audios/meta/digit_%1.wav").arg(last_d);
        QString unit_10_file = QString("/usr/share/paigo/audios/meta/digit_unit_shi.wav");
        meta_digits.append(first_d_file);
        meta_digits.append(unit_10_file);
        meta_digits.append(last_d_file);
    } else if(digit < 1000) {
        int d1 = digit / 100;
        int d2 = digit % 100 / 10;
        int d3 = digit % 100 % 10;
        QString d1_file = QString("/usr/share/paigo/audios/meta/digit_%1.wav").arg(d1);
        QString d2_file = QString("/usr/share/paigo/audios/meta/digit_%1.wav").arg(d2);
        QString d3_file = QString("/usr/share/paigo/audios/meta/digit_%1.wav").arg(d3);
        QString digit_0_file = QString("/usr/share/paigo/audios/meta/digit_0.wav");
        QString unit_bai_file = QString("/usr/share/paigo/audios/meta/digit_unit_bai.wav");
        QString unit_shi_file = QString("/usr/share/paigo/audios/meta/digit_unit_shi.wav");
        meta_digits.append(d1_file);
        meta_digits.append(unit_bai_file);
        if(d3 != 0) {
            if(d2 == 0) {
                    meta_digits.append(digit_0_file);
                    meta_digits.append(d3_file);
            } else {
                    meta_digits.append(d2_file);
                    meta_digits.append(unit_shi_file);
                    meta_digits.append(d3_file);
            }
        } else {
            if(d2 == 0) {

            } else {
                    meta_digits.append(d2_file);
                    meta_digits.append(unit_shi_file);

            }
        }

    }


    bool ret = true;
    QString first_file = meta_digits.first();
    QByteArray pathRaw = first_file.toUtf8();
    gchar *uri = g_filename_to_uri(pathRaw.constData(), NULL, NULL);

    QFileInfo audio_file_info(first_file);
    if(audio_file_info.exists() && audio_file_info.isReadable()) {
        gst_element_set_state (pipeline, GST_STATE_NULL);
        g_object_set(pipeline, "uri", uri, NULL);
        gst_element_set_state (pipeline, GST_STATE_PLAYING);
    } else {
        qDebug() << "Unable to read audio file" << first_file;
        _is_dplaying = false;
        ret = false;
    }

    g_free(uri);
    return ret;
}

void PaigoPlayer::pause() {
    gst_element_set_state (pipeline, GST_STATE_PAUSED);
}

void PaigoPlayer::stop() {
    gst_element_set_state (pipeline, GST_STATE_NULL);
}

void PaigoPlayer::emit_play_finished() {
    qDebug() << "Play finished." << _audio_id_;
    emit play_finished(_audio_id_);
    _audio_id_ = 0; // reset current play audio id to 0;
}
