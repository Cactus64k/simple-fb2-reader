#include "section_chunks.h"

int parse_fb2_text_autor(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GtkTextBuffer* text_buff	= app->text_buff;
	xmlNode* node				= parent_node;//parent_node->children;

	parse_fb2_id_attribute(app, parent_node, text_buff_end);

	GtkTextMark* start_tag_mark = gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	//gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
	parse_fb2_p__(app, node, text_buff_end);


	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag_by_name(text_buff, "text_author_tag", &start_tag_iter, text_buff_end);


	return EXIT_SUCCESS;
}
