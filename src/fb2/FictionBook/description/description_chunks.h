#ifndef DESCRIPTION_CHUNKS_H_
#define DESCRIPTION_CHUNKS_H_

	#include "../FictionBook_chunks.h"

	int parse_annotation		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_book_title		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_coverpage			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_title_info		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);

#endif /* DESCRIPTION_CHUNKS_H_ */
