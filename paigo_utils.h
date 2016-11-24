#ifndef PAIGO_UTILS_H
#define PAIGO_UTILS_H

#include <QByteArray>

namespace PaigoUtils {
    quint16 crc16(const QByteArray &data);
    int rand_int(int min, int max);
    QByteArray human_readable_hex(const QByteArray &data);
}

#endif // PAIGO_UTILS_H
