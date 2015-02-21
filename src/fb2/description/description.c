#include "../fb2_chunks.h"

int parse_book_description(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff_end != NULL);

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


int parse_title_info(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff_end != NULL);

	xmlNode* node = parent_node->children;

	GtkWidget* main_wnd = GLOBAL_FB2_READER.main_wnd;

	while(node != NULL)
	{
		if(strcmp((char*)node->name, "book-title") == 0)
		{
			//print_unsupported_tag("title-info");
			char* book_title = (char*)node->children->content;
			char* window_title = g_strdup_printf("Simple FB2 reader: %s", book_title);
			gtk_window_set_title(GTK_WINDOW(main_wnd), window_title);
			g_free(window_title);
		}
		node = node->next;
	}

	return 0;
}
