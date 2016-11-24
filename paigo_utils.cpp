#include "paigo_utils.h"
#include <QDebug>
#include <cstdlib>
#include <ctime>

namespace PaigoUtils {

quint16 crc16(const QByteArray &data) {
    quint16 xda, xdapoly;
    int i, j;
    xda = 0xFFFF;
    xdapoly = 0xA001;
    for (i = 0; i < data.size(); i++)
    {
        xda ^= (quint8)data[i];
        for (j = 0; j < 8; j++)
        {
            if(xda & 0x1)
            {
                xda = (xda>>1) ^ xdapoly;
            }
            else
            {
                xda >>= 1;
            }
        }
    }
    return xda;
}

int rand_int(int min, int max)
{
    srand(time(NULL));
    int r =  (rand() % (max + 1 - min)) + min;
    return r;
}

QByteArray human_readable_hex(const QByteArray &data)
{
    QByteArray hex_data = data.toHex();
    QByteArray hex_data_2;
    int data_size = hex_data.size();
    for(int i=0;i<data_size;i=i+1) {
        if(i > 0 && i % 2 == 0) {
            hex_data_2.append(" ");
        }
        hex_data_2.append(hex_data[i]);
    }
    return hex_data_2;
}


}
