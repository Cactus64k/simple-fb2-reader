#ifndef FICTIONBOOK_CHUNKS_H_
#define FICTIONBOOK_CHUNKS_H_
	#include "../fb2_chunks.h"

	#include "body/body_chunks.h"
	#include "description/description_chunks.h"
	#include "attributes/attributes_chunks.h"

	int parse_fb2_file					(char* path);
	int parse_fb2_function_book			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_book_binary			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node);

#endif /* FICTIONBOOK_CHUNKS_H_ */
