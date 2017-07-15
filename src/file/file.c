/*
 * file/file.c
 * File related operations
 *
 * Erik Liodden
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "file.h"
#include "error.h"


/* open_file: open file and return pointer to the file if it exists. */
FILE *open_file(char *name, char *mode)
{
	FILE *fp;
	fp = fopen(name, mode);
	if (fp == NULL) {
		error(errno, "cant open file");
		exit(1);
	}
	return fp;
}

/* get_file_info: return struct with info about file */
struct stat *get_file_info(char *name)
{
	struct stat *stbuf = malloc(sizeof(struct stat));
	stat(name, stbuf);
	return stbuf;
}
