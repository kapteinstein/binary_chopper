/*
 * file/cut.c
 * Cut a file in smaller pieces.
 *
 * Erik Liodden
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <string.h>
#include "file.h"
#include "cut.h"

/* bytes_per_chunk: return an array of number of bytes per chunk
 * TODO: This one could/should be written better.
 */
uint64_t *bytes_per_chunk(char *file_name, int parts)
{
	uint64_t fsize, base;
	int rest, i;
	uint64_t *bytes_per_chunk = malloc(parts * sizeof(uint64_t));
	
	fsize = get_file_size(file_name);
	rest = fsize % parts;
	fsize -= rest;
	base = fsize / parts;

	for (i = 0; i < parts; i++) {
		bytes_per_chunk[i] = base;	
	}
	bytes_per_chunk[parts-1] += rest;

	return bytes_per_chunk;
}

/* write_chunks: write bytes to .bin files of size given in bpc */
int write_chunks(char *file_name, int parts)
{
	int i, bytes;
	FILE *fp_out, *fp_in;
	char *buffer = malloc(BUF_SIZE);
	uint64_t *bpc;

	fp_in = open_file(file_name, "rb");
	bpc = bytes_per_chunk(file_name, parts);
	bytes = 0;

	for (i = 0; i < parts; i++) {
		snprintf(buffer, BUF_SIZE, "data%d.bin", i);
		fp_out = open_file(buffer, "wb");  /* open file to write to */

		/* clear buffer and write header to file.
		 * Possibly overkill header size.
		 */
		memset(buffer, 0, BUF_SIZE);
		snprintf(buffer, HEADER_SIZE, "%d %llu %s", (i+1) % parts,
				bpc[i], file_name);
		fwrite(buffer, 1, HEADER_SIZE, fp_out);	

		/* Read to buffer and write to chunk.
		 * Read and write one full buffer at a time.
		 */
		while (bpc[i] > BUF_SIZE) {
			bytes += fread(buffer, 1, BUF_SIZE, fp_in);
			bytes -= fwrite(buffer, 1, BUF_SIZE, fp_out);
			bpc[i] -= BUF_SIZE;
		}
		/* read and write the rest that did not fill buffer */
		bytes += fread(buffer, 1, bpc[i], fp_in);		
		bytes -= fwrite(buffer, 1, bpc[i], fp_out);
		fclose(fp_out);
	}
	fclose(fp_in);
	free(buffer);
	free(bpc);

	return bytes;
}
