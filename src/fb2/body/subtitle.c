#include "../fb2_chunks.h"

int parse_subtitle(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node;

	parse_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_subtitle	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	parse_p(obj, node, text_buff_end);

	GtkTextIter start_subtitle_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_subtitle_iter, start_subtitle);
	gtk_text_buffer_delete_mark(text_buff, start_subtitle);
	gtk_text_buffer_apply_tag_by_name(text_buff, "subtitle_tag", &start_subtitle_iter, text_buff_end);

	return 0;
}
