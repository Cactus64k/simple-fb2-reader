#include "../fb2_chunks.h"

int parse_coverpage(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	xmlNode* node = parent_node->children;

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "image") == 0)
				parse_image(obj, node, text_buff_end);
		}
		node = node->next;
	}

	return 0;
}
