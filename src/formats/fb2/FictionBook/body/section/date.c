#include "section_chunks.h"

int parse_fb2_date(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GtkTextBuffer* text_buff	= app->text_buff;
	char* value_attr			= (char*)xmlGetProp(parent_node, (xmlChar*)"id");

	GtkTextMark* start_tag_mark	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	if(value_attr != NULL)
		gtk_text_buffer_insert(text_buff, text_buff_end, value_attr, -1);
	else
	{
		xmlNode* node	= parent_node->children;
		if(node != NULL)
		{
			if(node->type == XML_TEXT_NODE)
				gtk_text_buffer_insert(text_buff, text_buff_end, (char*)node->content, -1);
		}
	}

	xmlFree(value_attr);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	//g_object_unref(G_OBJECT(start_tag_mark));
	gtk_text_buffer_apply_tag_by_name(text_buff, "date_tag", &start_tag_iter, text_buff_end);

	return EXIT_SUCCESS;
}
