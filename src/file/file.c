/*
 * file/file.c
 * File related operations
 *
 * Erik Liodden
 */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "file.h"

/* get_file_size: return size of file with filename 'name' */
uint64_t get_file_size(char *name)
{
	uint64_t size;
	struct stat st;
	stat(name, &st);
	size = st.st_size;
	return size;
}

/* open_file: open file and return pointer to the file if it exists. */
FILE *open_file(char *name, char *mode)
{
	FILE *fp;
	fp = fopen(name, mode);
	if (fp == NULL) {
		perror("cant open file");
		exit(1);
	}
	return fp;
}
