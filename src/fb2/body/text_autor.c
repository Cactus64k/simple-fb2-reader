#include "../fb2_chunks.h"

int parse_text_autor(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff_end != NULL);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	parse_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_tag_mark = gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	//gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
	parse_formated_text(obj, node, text_buff_end);
	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);


	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag_by_name(text_buff, "text_author_tag", &start_tag_iter, text_buff_end);


	return 0;
}
