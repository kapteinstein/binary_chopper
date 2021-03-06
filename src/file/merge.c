/*
 * file/merge.c
 * Merge multiple files to one big file
 *
 * Erik Liodden
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <string.h>
#include "merge.h"
#include "file.h"
#include "error.h"


int merge_chunks(char *file_name)
{
	int id_next, n;
	FILE *fp_out = NULL;
	FILE *fp_chunk;
	uint64_t size;
	char out_file[HEADER_SIZE];
	char *buffer = malloc(BUF_SIZE);
	snprintf(buffer, BUF_SIZE, "data0.bin");

	do {
		fp_chunk = open_file(buffer, "rb");
		if (fread(buffer, 1, HEADER_SIZE, fp_chunk) != HEADER_SIZE)
			error(errno, "Could not read header");
		sscanf(buffer, "%d %llu %s", &id_next, &size, out_file);
		if (file_name != NULL && strcmp(out_file, file_name) != 0)
			strcpy(out_file, file_name);
		if (!fp_out)
			fp_out = open_file(out_file, "wb");

		/* Read to buffer and write to file.
		 * Read and write one full buffer at a time.
		 */
		while (size > BUF_SIZE) {
			n = fread(buffer, 1, BUF_SIZE, fp_chunk);
			if (fwrite(buffer, 1, BUF_SIZE, fp_out) != n)
				error(errno, "error writing to file");
			size -= BUF_SIZE;
		}
		/* read and write the rest that did not fill buffer */
		n = fread(buffer, 1, size, fp_chunk);
		if (fwrite(buffer, 1, size, fp_out) != n)
			error(errno, "error writing to file");
		fclose(fp_chunk);
		snprintf(buffer, BUF_SIZE, "data%d.bin", id_next);
	} while (id_next);

	fclose(fp_out);
	free(buffer);

	return 0;
}
