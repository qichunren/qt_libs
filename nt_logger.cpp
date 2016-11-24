#include "nt_logger.h"
#include "paigo_header.h"
#include <QFile>
#include <QDateTime>
#include <QDebug>

NtLogger& NtLogger::instance() {
    static NtLogger _instance;
    return _instance;
}

NtLogger::NtLogger(QObject *parent) :
    QObject(parent)
{
}

void NtLogger::log_info(const QString &message) {    
    QFile file(INFO_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        puts("Unable to write info log to file.");
        return;
    }

    QByteArray message_array;
    QString datetime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss # "));
    message_array.append(datetime);
    message_array.append(message);
    file.write(message_array);
    qDebug() << message_array;
    file.write("\n");
    file.close();
}

void NtLogger::log_error(const QString &message) {
    QFile file(ERROR_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        puts("Unable to write error log to file.");
        return;
    }

    QByteArray message_array;    
    QString datetime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss # "));
    message_array.append(datetime);
    message_array.append(message);
    file.write(message_array);
    file.write("\n");
    file.close();
}

void NtLogger::clear_info_logs() {
    QFile file(INFO_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        puts("Unable to write info log to file.");
        return;
    }

    QByteArray message_array;
    message_array.append("");
    file.write(message_array);
    file.close();
}

void NtLogger::clear_error_logs() {
    QFile file(ERROR_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        puts("Unable to write error log to file.");
        return;
    }

    QByteArray message_array;
    message_array.append("");
    file.write(message_array);
    file.close();
}
