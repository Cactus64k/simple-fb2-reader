#include "../fb2_chunks.h"

int parse_subtitle(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	GtkTextTag* subtitle_tag	= GLOBAL_FB2_READER.subtitle_tag;
	GtkTextMark* start_subtitle	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, true);

	parse_p(node, text_buff, text_buff_end);

	GtkTextIter start_subtitle_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_subtitle_iter, start_subtitle);
	gtk_text_buffer_delete_mark(text_buff, start_subtitle);
	gtk_text_buffer_apply_tag(text_buff, subtitle_tag, &start_subtitle_iter, text_buff_end);

	return 0;
}
