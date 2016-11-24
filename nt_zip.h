#ifndef NT_ZIP_H
#define NT_ZIP_H
#include <QStringList>

namespace NtZip {
    bool compress(const QString &out_archive_file, const char **inside_filename, const char **filename);
    bool compress(const char *out_archive_file, const char **inside_filename, const char **filename);
    const QStringList file_list(const char *archive_file);
    const QStringList file_list(const QString &archive_file);
    bool extract(const char *archive_file, const QString &dest_dir);
}

#endif // NT_ZIP_H
