#include "FictionBook_chunks.h"

int parse_fb2_function_book(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
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
				parse_fb2_book_binary(obj, node);
		}

		node = node->next;
	}

	//**************************************************************************

	node = parent_node->children;

	while(node != NULL)
	{
		if((node->type == XML_ELEMENT_NODE) && (strcmp((char*)node->name, "description") == 0))
		{
			parse_fb2_book_description(obj, node, text_buff_end);
		}

		node = node->next;
	}

	//**************************************************************************

	node = parent_node->children;

	while(node != NULL)
	{
		if((node->type == XML_ELEMENT_NODE) && (strcmp((char*)node->name, "body") == 0))
		{
			parse_fb2_body(obj, node, text_buff_end);

			GtkTextIter text_buff_start;
			gtk_text_buffer_get_start_iter(text_buff, &text_buff_start);
			gtk_text_buffer_apply_tag_by_name(text_buff, "default_tag", &text_buff_start, text_buff_end);

		}

		node = node->next;
	}

	//**************************************************************************

	printf(_C("End read book\n"));



	return 0;

}
