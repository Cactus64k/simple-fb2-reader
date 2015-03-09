#include "description_chunks.h"

int parse_annotation(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	xmlNode* node				= parent_node->children;

	parse_id_attribute(obj, parent_node, text_buff_end);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "p") == 0)
				parse_p(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "poem") == 0)
				parse_poem(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "cite") == 0)
				parse_cite(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "subtitle") == 0)
				parse_subtitle(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "empty-line") == 0)
				parse_empty_line(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "table") == 0)
				parse_table(obj, node, text_buff_end);
		}

		node = node->next;
	}

	return 0;
}
