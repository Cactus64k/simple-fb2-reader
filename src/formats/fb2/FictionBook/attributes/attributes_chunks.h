#ifndef FB2_FICTIONBOOK_ATTRIBUTES_CHUNKS_H_
#define FB2_FICTIONBOOK_ATTRIBUTES_CHUNKS_H_

	#include "../FictionBook_chunks.h"

	int parse_fb2_attribute			(APP* app, xmlNode* parent_node, const char* attribute_name, const char** value);
	int parse_fb2_id_attribute		(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);


#endif /* FB2_FICTIONBOOK_ATTRIBUTES_CHUNKS_H_ */
