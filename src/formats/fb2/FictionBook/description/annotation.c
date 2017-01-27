#include "description_chunks.h"

int parse_fb2_annotation(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	xmlNode* node				= parent_node->children;

	parse_fb2_id_attribute(app, parent_node, text_buff_end);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "p") == 0)
				parse_fb2_p_common(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "poem") == 0)
				parse_fb2_poem(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "cite") == 0)
				parse_fb2_cite(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "subtitle") == 0)
				parse_fb2_subtitle(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "empty-line") == 0)
				parse_fb2_empty_line(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "table") == 0)
				parse_fb2_table(app, node, text_buff_end);
		}

		node = node->next;
	}

	return EXIT_SUCCESS;
}
