#include "description_chunks.h"

int parse_fb2_book_title(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node 	!= NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end 	!= NULL,	EXIT_FAILURE);

	xmlNode* node = parent_node->children;

	if(node != NULL)
	{
		char* book_title = (char*)node->content;
		app->book_title = g_strdup(book_title);
	}
	else
		g_warning("No content in <book-title> tag");

	return EXIT_SUCCESS;
}
