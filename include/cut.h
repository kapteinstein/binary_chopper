#ifndef _CUT_H
#define _CUT_H

uint64_t *bytes_per_chunk(char *file_name, int parts);
int write_chunks(char *file_name, int parts);

#endif
