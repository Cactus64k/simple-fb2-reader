#include "../fb2_chunks.h"

int parse_book_title(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	xmlNode* node = parent_node->children;

	GtkWidget* main_wnd = GLOBAL_FB2_READER.main_wnd;

	char* book_title = (char*)node->content;
	char* window_title = g_strdup_printf("Simple FB2 reader: %s", book_title);
	gtk_window_set_title(GTK_WINDOW(main_wnd), window_title);
	g_free(window_title);


	return 0;
}
