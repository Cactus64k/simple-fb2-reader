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
		else if(strcmp((char*)node->name, "src-title-info") == 0)
		{
			//print_unsupported_tag("src-title-info");
		}
		else if(strcmp((char*)node->name, "document-info") == 0)
		{
			//print_unsupported_tag("document-info");
		}
		else if(strcmp((char*)node->name, "publish-info") == 0)
		{
			//print_unsupported_tag("publish-info");
		}
		else if(strcmp((char*)node->name, "custom-info") == 0)
		{
			//print_unsupported_tag("custom-info");
		}
		else if(strcmp((char*)node->name, "output") == 0)
		{
			//print_unsupported_tag("output");
		}


		node = node->next;
	}
	return EXIT_SUCCESS;
}

