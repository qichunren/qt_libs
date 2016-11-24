#!/bin/sh

PATH=/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/sbin:/usr/local/bin:$PATH

trap process_user_sig SIGUSR1

process_user_sig()
{
    echo "paigo-watchdog is still alive!"
}

echo 'Waiting for paigo-qt startup....'
sleep 30
echo 'Watchdog starting....'
DROP_CACHE_COUNT=0

while :
do
    LEVEL=`runlevel | cut -f2 -d ' '`
    if [ "$LEVEL" = "6" -o "$LEVEL" = "0" -o "$LEVEL" = "1" ] ; then
        break
    fi

    PAIGOQT_PID=`pidof -s paigo-qt`
    RESTARTED="0"

    if [ -z "$PAIGOQT_PID" ] ; then
        echo `date`" # paigo-qt is dead, restarting...." >> /var/log/paigo.log
        killall -9 paigo-qt
        /usr/bin/paigo-qt -d -platform linuxfb
        RESTARTED="1"
    fi

    if [ "$RESTARTED" = "1" ] ; then
        sleep 30
        continue
    fi
done
