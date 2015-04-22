#ifndef DESCRIPTION_CHUNKS_H_
#define DESCRIPTION_CHUNKS_H_

	#include "../FictionBook_chunks.h"

	int parse_fb2_annotation		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_book_title		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_coverpage			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_title_info		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_book_description	(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);

#endif /* DESCRIPTION_CHUNKS_H_ */
