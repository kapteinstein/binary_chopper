#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "options.h"
#include <getopt.h>

struct opts *get_options(int argc, char **argv)
{
	int option_index = 0;
  	int c;
  	opterr = 0;

	struct opts *options = calloc(1, sizeof(struct opts));
	struct option long_options[] = {
		/* These options set a flag.
          	 * {"verbose", no_argument,       &verbose_flag, 1},
          	 * {"brief",   no_argument,       &verbose_flag, 0},
		 */
          	/* These options don’t set a flag.
          	   We distinguish them by their indices. */
          	{"merge",   no_argument,       0, 'm'},
          	{"file",    required_argument, 0, 'f'},
          	{"cut",     required_argument, 0, 'c'},
          	{0, 0, 0, 0}
        };


  	while((c = getopt_long(argc, argv, "mf:c:",
					long_options, &option_index)) != -1)
		switch (c) {
		case 'c':
			options->cut_flag = 1;
			options->parts = atoi(optarg);
			break;
  	    	case 'm':
			options->merge_flag = 1;
  	    		break;
		case 'f':
			options->file_name = optarg;
			break;
  	    	case '?':
			if (optopt == 'c' || optopt == 'f')
				fprintf (stderr, "Option -%c" \
						"requires an argument.\n", optopt);
  	      		else if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
  	      		else
				fprintf(stderr,
  	      		           "Unknown option character `\\x%x'.\n", optopt);
  	      		exit(EXIT_FAILURE);
		default:
			abort();
  	    }

	if (options->cut_flag && options->merge_flag) {
		fprintf(stderr, "Error: cannot merge and cut at the same time\n");
		exit(EXIT_FAILURE);
	}
	/*
  	printf("cut_flag = %d, merge_flag = %d, parts = %d, file = %s\n",
			options->cut_flag,
			options->merge_flag,
			options->parts,
			options->file_name);

  	for (option_index = optind; option_index < argc; option_index++)
		printf("Non-option argument %s\n", argv[option_index]);
	*/
  	return options;
}
