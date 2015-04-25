#ifndef SECTION_CHUNKS_H_
#define SECTION_CHUNKS_H_

	#include "../body_chunks.h"
	#include "p/p_chunks.h"
	#include "table/table_chunks.h"

	int parse_fb2_section		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end, GtkTreeIter* tree_iter);
	int parse_fb2_a				(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_cite			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_date			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_empty_line	(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_image_inline	(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_poem			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_style			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_subtitle		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);

	int parse_fb2_text_autor	(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);

	int parse_fb2_navigation_set_chapter_by_title(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTreeIter* cur_tree_iter);

#endif /* SECTION_CHUNKS_H_ */
