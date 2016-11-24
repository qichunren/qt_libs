#ifndef NT_LOGGER_H
#define NT_LOGGER_H

#include <QObject>

#define NTLogger NtLogger::instance()

class NtLogger : public QObject
{
    Q_OBJECT
public:
    static NtLogger &instance();

    void log_info(const QString &message);
    void log_error(const QString &message);
    void clear_info_logs();
    void clear_error_logs();

signals:

public slots:

private:
    explicit NtLogger(QObject *parent = 0);

};

#endif // NT_LOGGER_H
