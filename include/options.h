#ifndef _OPTIONS_H
#define _OPTIONS_H

struct opts {
	int cut_flag;
  	int merge_flag;
	int parts;
  	char *file_name;
};
struct opts *get_options(int argc, char **argv);

#endif
