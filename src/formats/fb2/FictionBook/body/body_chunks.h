#ifndef BODY_CHUNKS_H_
#define BODY_CHUNKS_H_

	#include "../FictionBook_chunks.h"

	#include "section/section_chunks.h"

	int parse_fb2_body				(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_epigraph			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_image				(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_title				(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);

#endif /* BODY_CHUNKS_H_ */
