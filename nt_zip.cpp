#include "nt_zip.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <archive.h>
#include <archive_entry.h>

//NtZip::NtZip(QObject *parent) :
//    QObject(parent)
//{
//}

static int copy_data(struct archive *ar, struct archive *aw) {
  int r;
  const void *buff;
  size_t size;
  off64_t offset;

  for (;;) {
    r = archive_read_data_block(ar, &buff, &size, &offset);
    if (r == ARCHIVE_EOF)
      return (ARCHIVE_OK);
    if (r < ARCHIVE_OK)
      return (r);
    r = archive_write_data_block(aw, buff, size, offset);
    if (r < ARCHIVE_OK) {
      fprintf(stderr, "archive_write_data_block failed:%s\n", archive_error_string(aw));
      return (r);
    }
  }
}

namespace NtZip {

bool extract(const char *archive_file, const QString &dest_dir) {
  struct archive *a;
  struct archive *ext;
  struct archive_entry *entry;
  int flags;
  int r;

  /* Select which attributes we want to restore. */
  flags = ARCHIVE_EXTRACT_TIME;
  flags |= ARCHIVE_EXTRACT_PERM;
  flags |= ARCHIVE_EXTRACT_ACL;
  flags |= ARCHIVE_EXTRACT_FFLAGS;

  a = archive_read_new();
  archive_read_support_format_all(a);
  archive_read_support_filter_all(a);
  ext = archive_write_disk_new();
  archive_write_disk_set_options(ext, flags);
  archive_write_disk_set_standard_lookup(ext);
  if ((r = archive_read_open_filename(a, archive_file, 10240))) {
      archive_read_close(a);
      archive_read_free(a);
      archive_write_close(ext);
      archive_write_free(ext);
      return false;
  }
  bool ret = true;
  for (;;) {
    r = archive_read_next_header(a, &entry);    
    if (r == ARCHIVE_EOF)
      break;
    if (r < ARCHIVE_OK)
      fprintf(stderr, "archive_read_next_header failed:%s\n", archive_error_string(a));
    if (r < ARCHIVE_WARN)
    {
        ret = false;
        break;
    }

    const char* currentFile = archive_entry_pathname(entry);
    QString fulloutput_path = QString("%1/%2").arg(dest_dir).arg(currentFile);
    archive_entry_set_pathname(entry, fulloutput_path.toUtf8().constData());
    r = archive_write_header(ext, entry);
    if (r < ARCHIVE_OK)
      fprintf(stderr, "archive_write_header failed:%s\n", archive_error_string(ext));
    else if (archive_entry_size(entry) > 0) {
      r = copy_data(a, ext);
      if (r < ARCHIVE_OK)
        fprintf(stderr, "copy_data failed:%s\n", archive_error_string(ext));
      if (r < ARCHIVE_WARN)
      {
          ret = false;
          break;
      }
    }
    r = archive_write_finish_entry(ext);
    if (r < ARCHIVE_OK)
      fprintf(stderr, "archive_write_finish_entry failed:%s\n", archive_error_string(ext));
    if (r < ARCHIVE_WARN)
    {
        ret = false;
        break;
    }
  }  
  archive_read_close(a);
  archive_read_free(a);
  archive_write_close(ext);
  archive_write_free(ext);
  return ret;
}

bool compress(const QString &out_archive_file, const char **inside_filename, const char **filename) {
    QByteArray arr = out_archive_file.toUtf8();
    const char * archive_file_str = arr.constData();
    return compress(archive_file_str, inside_filename, filename);
}

bool compress(const char *out_archive_file, const char **inside_filename, const char **filename)
{
  struct archive *a;
  struct archive_entry *entry;
  struct stat st;
  char buff[8192];
  int len;
  int fd;
  int r;
  a = archive_write_new();
  archive_write_set_format_zip(a);
  r = archive_write_open_filename(a, out_archive_file);
  if(r != ARCHIVE_OK) {
      fprintf(stderr, "Failed to invoke archive_write_open_filename %s\n", out_archive_file);
      return false;
  }
  while (*filename) {
    stat(*filename, &st);
    entry = archive_entry_new(); // Note 2
    archive_entry_set_pathname(entry, *inside_filename);
    archive_entry_set_size(entry, st.st_size); // Note 3
    archive_entry_set_filetype(entry, AE_IFREG);
    archive_entry_set_perm(entry, 0644);
    archive_write_header(a, entry);
    fd = open(*filename, O_RDONLY);
    len = read(fd, buff, sizeof(buff));
    while ( len > 0 ) {
        archive_write_data(a, buff, len);
        len = read(fd, buff, sizeof(buff));
    }
    close(fd);
    archive_entry_free(entry);
    filename++;
    inside_filename++;
  }
  archive_write_close(a); // Note 4
  archive_write_free(a); // Note 5
  return true;
}

const QStringList file_list(const QString &archive_file) {
    QByteArray arr = archive_file.toUtf8();
    const char * archive_file_str = arr.constData();
    return file_list(archive_file_str);
}

const QStringList file_list(const char *archive_file) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    QStringList files;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    r = archive_read_open_filename(a, archive_file, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Failed to invoke archive_read_open_filename\n");
        return QStringList("-1");
    }
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        files << QString(archive_entry_pathname(entry));
        archive_read_data_skip(a);
    }
    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Failed to invoke archive_read_free\n");
        return QStringList("-1");
    }
    return files;
}

} // end namespace
