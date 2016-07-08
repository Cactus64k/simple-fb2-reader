#include "description_chunks.h"

int parse_fb2_title_info(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node	!= NULL, EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end	!= NULL, EXIT_FAILURE);

	xmlNode* node				= parent_node->children;
	if(node != NULL)
	{
		GtkTextBuffer* text_buff	= app->text_buff;

		gtk_text_buffer_insert(text_buff, text_buff_end, "\n\n\n\n", -1);

		while(node != NULL)
		{
			if(node->type == XML_ELEMENT_NODE)
			{
				if(strcmp((char*)node->name, "coverpage") == 0)
				{
					parse_fb2_coverpage(app, node, text_buff_end);
					break;
				}
			}
			node = node->next;
		}

		node = parent_node->children;

		while(node != NULL)
		{
			if(node->type == XML_ELEMENT_NODE)
			{
				if(strcmp((char*)node->name, "book-title") == 0)
					parse_fb2_book_title(app, node, text_buff_end);
				else if(strcmp((char*)node->name, "annotation") == 0)
					parse_fb2_annotation(app, node, text_buff_end);
			}
			node = node->next;
		}

		gtk_text_buffer_insert(text_buff, text_buff_end, "\n\n\n\n", -1);
	}
	else
		g_warning("No content in <title-info> tag");


	return EXIT_SUCCESS;
}
