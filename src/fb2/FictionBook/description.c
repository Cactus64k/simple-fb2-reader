#include "FictionBook_chunks.h"

int parse_book_description(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	xmlNode* node				= parent_node->children;

	while(node != NULL)
	{
		if(strcmp((char*)node->name, "title-info") == 0)
		{
			parse_title_info(obj, node, text_buff_end);
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
	return 0;
}

