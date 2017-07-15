#ifndef _FILE_H
#define _FILE_H

#define HEADER_SIZE 256
#define BUF_SIZE    8388608

FILE *open_file(char *name, char *mode);
struct stat *get_file_info(char *name);

#endif
