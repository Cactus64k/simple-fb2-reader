#include "fb2_chunks.h"

int parse_body(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node		!= NULL);
	assert(text_buff_end	!= NULL);

	xmlNode* node				= parent_node->children;

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "section") == 0)
				parse_section(obj, node, text_buff_end, NULL);
			else if(strcmp((char*)node->name, "title") == 0)
				parse_title(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_epigraph(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "image") == 0)
				parse_image(obj, node, text_buff_end);
		}

		node = node->next;
	}
	return 0;
}
