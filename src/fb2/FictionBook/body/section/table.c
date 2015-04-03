#include "section_chunks.h"

int parse_table(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	parse_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_tag_mark		= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	//table_get_column_size(parent_node, 0);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "tr") == 0)
			{
				xmlNode* td_node = node->children;

				while(td_node != NULL)
				{
					if(td_node->type == XML_ELEMENT_NODE)
					{
						if(strcmp((char*)td_node->name, "td") == 0)
						{
							if(td_node->children != NULL)
							{
								parse_formated_text(obj, td_node->children, text_buff_end);

							}
						}

						gtk_text_buffer_insert(text_buff, text_buff_end, "\t\t", -1);
					}

					td_node = td_node->next;
				}
				gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
			}
		}
		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag_by_name(text_buff, "table_tag", &start_tag_iter, text_buff_end);

	return 0;
}










