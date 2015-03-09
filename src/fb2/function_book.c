#include "fb2_chunks.h"

int parse_function_book(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(obj != NULL, -3);
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff	= obj->text_buff;

	xmlNode* node				= parent_node->children;

	//**************************************************************************

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "stylesheet") == 0)
			{

			}
			else if(strcmp((char*)node->name, "binary") == 0)
				parse_book_binary(obj, node);
		}

		node = node->next;
	}

	//**************************************************************************

	node = parent_node->children;

	while(node != NULL)
	{
		if((node->type == XML_ELEMENT_NODE) && (strcmp((char*)node->name, "description") == 0))
		{
			parse_book_description(obj, node, text_buff_end);
		}

		node = node->next;
	}

	//**************************************************************************

	node = parent_node->children;

	while(node != NULL)
	{
		if((node->type == XML_ELEMENT_NODE) && (strcmp((char*)node->name, "body") == 0))
		{
			if(node->properties == NULL)
			{
				GtkTextIter text_buff_start;

				obj->store_section	= TRUE;

				parse_body(obj, node, text_buff_end);

				gtk_text_buffer_get_start_iter(text_buff, &text_buff_start);
				gtk_text_buffer_apply_tag_by_name(text_buff, "default_tag", &text_buff_start, text_buff_end);
			}
			else
			{
				xmlAttr* node_properties = node->properties;

				while(node_properties != NULL)
				{
					if(strcmp((char*)node_properties->name, "name") == 0)
					{
						char* properties_value = (char*)(node_properties->children->content);
						if((strcmp(properties_value, "notes") == 0) || (strcmp(properties_value, "comments") == 0))
						{
							GtkTextIter text_buff_start;

							obj->store_section	= FALSE;

							parse_body(obj, node, text_buff_end);

							gtk_text_buffer_get_start_iter(text_buff, &text_buff_start);
							gtk_text_buffer_apply_tag_by_name(text_buff, "default_tag", &text_buff_start, text_buff_end);

						}
					}

					node_properties = node_properties->next;
				}
			}
		}

		node = node->next;
	}

	//**************************************************************************

	printf(_C("End read book\n"));



	return 0;

}
