#ifndef BODY_CHUNKS_H_
#define BODY_CHUNKS_H_

	#include "../FictionBook_chunks.h"

	#include "section/section_chunks.h"

	int parse_fb2_body					(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_epigraph			(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_image				(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_title				(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);

#endif /* BODY_CHUNKS_H_ */
