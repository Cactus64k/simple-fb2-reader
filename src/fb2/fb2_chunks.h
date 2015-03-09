
#ifndef FB2_CHUNKS_H_
#define FB2_CHUNKS_H_

	#include "../chunks.h"
	#include "body/body_chunks.h"
	#include "description/description_chunks.h"

	gboolean a_tag_event_cb(GtkTextTag* tag, GObject* object, GdkEvent* event, GtkTextIter* iter, gpointer user_data);

	int parse_fb2				(char* path);
	int parse_function_book		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_book_binary		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node);
	int parse_body				(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_id_attribute		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_book_description	(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);

#endif /* FB2_CHUNKS_H_ */
