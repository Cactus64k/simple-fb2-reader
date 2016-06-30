#ifndef SECTION_CHUNKS_H_
#define SECTION_CHUNKS_H_

	#include "../body_chunks.h"
	#include "p/p_chunks.h"
	#include "table/table_chunks.h"

	int parse_fb2_section		(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end, GtkTreeIter* tree_iter);
	int parse_fb2_a				(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_cite			(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_date			(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_empty_line	(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_image_inline	(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_poem			(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_style			(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_subtitle		(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);

	int parse_fb2_text_autor	(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);

	int parse_fb2_navigation_set_chapter_by_title(APP* app, xmlNode* parent_node, GtkTreeIter* cur_tree_iter);

#endif /* SECTION_CHUNKS_H_ */
