#ifndef BODY_CHUNKS_H_
#define BODY_CHUNKS_H_

	#include "../FictionBook_chunks.h"

	#include "section/section_chunks.h"

	int parse_epigraph			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_image				(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
<<<<<<< HEAD
	int parse_section			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end, GtkTreeIter* tree_iter);
=======
	int parse_section			(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end, GtkTreeIter* tree_iter, gboolean store_section);
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
	int parse_title				(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);

#endif /* BODY_CHUNKS_H_ */
