#ifndef _FILE_H
#define _FILE_H

#define HEADER_SIZE 256
#define BUF_SIZE    8388608

uint64_t get_file_size(char *name);
FILE *open_file(char *name, char *mode);

#endif
