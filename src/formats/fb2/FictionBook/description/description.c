#include "description_chunks.h"

int parse_fb2_book_description(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	xmlNode* node				= parent_node->children;

	while(node != NULL)
	{
		if(strcmp((char*)node->name, "title-info") == 0)
		{
			parse_fb2_title_info(app, node, text_buff_end);
		}
		node = node->next;
	}
	return EXIT_SUCCESS;
}

