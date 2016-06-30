#ifndef DESCRIPTION_CHUNKS_H_
#define DESCRIPTION_CHUNKS_H_

	#include "../FictionBook_chunks.h"

	int parse_fb2_annotation		(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_book_title		(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_coverpage			(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_title_info		(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_book_description	(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);

#endif /* DESCRIPTION_CHUNKS_H_ */
