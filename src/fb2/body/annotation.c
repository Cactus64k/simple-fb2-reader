#include "../fb2_chunks.h"

int parse_annotation(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff_end != NULL);

	GtkTextBuffer* text_buff	= obj->text_buff;
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
				gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
			else if(strcmp((char*)node->name, "table") == 0)
				parse_table(obj, node, text_buff_end);
		}

		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	return 0;
}
