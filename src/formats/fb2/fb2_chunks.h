
#ifndef FB2_CHUNKS_H_
#define FB2_CHUNKS_H_

	#include "../formats_chunks.h"

	#include "FictionBook/body/body_chunks.h"
	#include "FictionBook/description/description_chunks.h"

	int parse_fb2_file				(char* path);
	int parse_fb2_function_book		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_book_binary		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node);
	int parse_fb2_id_attribute		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);

#endif /* FB2_CHUNKS_H_ */
