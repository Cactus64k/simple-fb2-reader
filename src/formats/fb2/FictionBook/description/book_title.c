#include "description_chunks.h"

int parse_fb2_book_title(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff_end != NULL);

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
