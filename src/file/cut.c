/*
 * file/cut.c
 * Cut a file in smaller pieces.
 *
 * Erik Liodden
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "file.h"
#include "cut.h"
#include "error.h"

/* write_chunks: write bytes to .bin files of size given in bpc */
int write_chunks(char *file_name, int parts)
{
	int i, n;
	FILE *fp_in, *fp_out;
	uint64_t psize, tmp;
	char *buffer = malloc(BUF_SIZE);
	struct stat *stbuf = get_file_info(file_name);

	fp_in = open_file(file_name, "rb");
	psize = (stbuf->st_size - (stbuf->st_size % parts)) / (uint64_t) parts;

	for (i = 0; i < parts; i++) {
		if (parts - i == 1)
			psize += stbuf->st_size % parts;

		snprintf(buffer, BUF_SIZE, "data%d.bin", i);
		fp_out = open_file(buffer, "wb");  /* open file to write to */

		/* clear buffer and write header to file.
		 * Possibly overkill header size.
		 */
		memset(buffer, 0, BUF_SIZE);
		snprintf(buffer, HEADER_SIZE, "%d %llu %s", (i+1) % parts,
				psize, file_name);
		fwrite(buffer, 1, HEADER_SIZE, fp_out);	

		/* Read to buffer and write to chunk.
		 * Read and write one full buffer at a time.
		 */
		tmp = psize;
		while (tmp > BUF_SIZE) {
			n = fread(buffer, 1, BUF_SIZE, fp_in);
			if (fwrite(buffer, 1, BUF_SIZE, fp_out) != n)
				error(errno, "error writing file data%d.bin", i);
			tmp -= n;
		}
		/* read and write the rest that did not fill buffer */
		n = fread(buffer, 1, tmp, fp_in);
		if (fwrite(buffer, 1, n, fp_out) != n)
			error(errno, "error writing file \
					data%d.bin, tmp: %d", i, tmp);

		fclose(fp_out);
	}
	fclose(fp_in);
	free(buffer);
	free(stbuf);

	return 0;
}
