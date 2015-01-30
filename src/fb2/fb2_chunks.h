/*
 * fb2_chunks.h
 *
 *  Created on: 16.01.2015
 *      Author: cactus
 */

#ifndef FB2_CHUNKS_H_
#define FB2_CHUNKS_H_

	#include "../chunks.h"

	gboolean a_tag_event_cb(GtkTextTag* tag, GObject* object, GdkEventButton* event, GtkTextIter* iter, gpointer user_data);

	int parse_fb2(char* path, GtkTextBuffer* text_buff);
	int parse_book_body(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);
	int parse_book_binary(xmlNode* node, GHashTable* binary_table);
	int parse_book_description(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);
	int parse_title_info(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);
	int parse_link(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);
	int parse_image(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);
	int parse_body_section(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end, size_t section_counter);
	int parse_p(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);
	int parse_formated_text(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);
	int print_unsupported_tag(char* tag);
	int parse_title(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end, GtkTreeIter* list_pos, GtkListStore* list_store);
	int parse_subtitle(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);
	int parse_cite(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);

#endif /* FB2_CHUNKS_H_ */
