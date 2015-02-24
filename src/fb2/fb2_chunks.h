
#ifndef FB2_CHUNKS_H_
#define FB2_CHUNKS_H_

	#include "../chunks.h"

	gboolean a_tag_event_cb(GtkTextTag* tag, GObject* object, GdkEvent* event, GtkTextIter* iter, gpointer user_data);

	int parse_fb2				(char* path);
	int parse_function_book		(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_book_binary		(FB2_READER_TEXT_VIEW* obj, xmlNode* node);
	int parse_body				(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_book_description	(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_title_info		(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_link				(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_image				(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_image_inline		(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_section			(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end, GtkTreeIter* tree_iter);
	int parse_p					(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_formated_text		(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_date				(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_poem				(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_style				(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_text_autor		(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_epigraph			(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_title				(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_subtitle			(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_cite				(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_table				(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);
	int parse_annotation		(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);

	int parse_id_attribute		(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);

#endif /* FB2_CHUNKS_H_ */
