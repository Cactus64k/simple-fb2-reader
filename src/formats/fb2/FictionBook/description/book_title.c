#include "description_chunks.h"

int parse_fb2_book_title(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node 	!= NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end 	!= NULL,	EXIT_FAILURE);

	xmlNode* node = parent_node->children;

	if(node != NULL)
	{
		GtkWidget* main_wnd = app->main_wnd;

		char* book_title = (char*)node->content;
		char* window_title = g_strdup_printf("Simple FB2 reader: %s", book_title);
		gtk_window_set_title(GTK_WINDOW(main_wnd), window_title);
		g_free(window_title);
	}
	fputs(_C("ERROR: no content in <book-title> tag\n"), stderr);

	return EXIT_SUCCESS;
}
