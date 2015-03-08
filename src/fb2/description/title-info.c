#include "../fb2_chunks.h"

int parse_title_info(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	xmlNode* node				= parent_node->children;
	GtkTextBuffer* text_buff	= obj->text_buff;

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n\n\n\n", -1);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "coverpage") == 0)
			{
				parse_coverpage(obj, node, text_buff_end);
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
				parse_book_title(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "annotation") == 0)
				parse_annotation(obj, node, text_buff_end);
		}
		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n\n\n\n", -1);

	return 0;
}
