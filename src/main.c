#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include "file.h"
#include "cut.h"
#include "merge.h"
#include "options.h"


int main(int argc, char *argv[])
{
	struct opts *options;
	options = get_options(argc, argv);

	if (options->cut_flag)
		write_chunks(options->file_name, options->parts);
	else if (options->merge_flag)
		merge_chunks(options->file_name);
	else
		return 1;

	free(options);
	return 0;
}
