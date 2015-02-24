#ifndef TXT_PARSER_H_
#define TXT_PARSER_H_

	#include "../chunks.h"
	#include <iconv.h>

	int parse_txt(char* path, char* encode);
	int fill_encode_treestore(GtkTreeStore* tree_store);
	int fill_encode_test_buffer(ENCODE_DIALOG* obj, char* file_path);
	char* encode_dialog_get_encode_name(ENCODE_DIALOG* obj);


#endif /* TXT_PARSER_H_ */
