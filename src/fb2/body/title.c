#include "../fb2_chunks.h"

int parse_title(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff_end != NULL);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	parse_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_title	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "p") == 0)
				parse_formated_text(obj, node->children, text_buff_end);
			else if(strcmp((char*)node->name, "empty-line") == 0)
				gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
		}

		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	GtkTextIter start_title_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_title_iter, start_title);
	gtk_text_buffer_delete_mark(text_buff, start_title);
	gtk_text_buffer_apply_tag_by_name(text_buff, "title_tag", &start_title_iter, text_buff_end);

	return 0;
}