#include "../fb2_chunks.h"

int parse_text_autor(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	GtkTextTag* text_autor_tag	= GLOBAL_FB2_READER.text_author_tag;

	GtkTextMark* start_tag_mark = gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, true);


	//gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
	parse_formated_text(node->children, text_buff, text_buff_end);
	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);


	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag(text_buff, text_autor_tag, &start_tag_iter, text_buff_end);


	return 0;
}
