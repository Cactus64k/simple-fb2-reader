#ifndef TXT_PARSER_H_
#define TXT_PARSER_H_

	#include "../formats_chunks.h"
	#include <iconv.h>

	int parse_txt_file(char* path, char* encode);

#endif /* TXT_PARSER_H_ */
