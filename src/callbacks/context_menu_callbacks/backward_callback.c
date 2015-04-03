#include "../callbacks_chunk.h"

void backward_itemmenu_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	g_return_if_fail(user_data != NULL);

	FB2_READER_BOOK_VIEW* book_view	= (FB2_READER_BOOK_VIEW*)user_data;
	GtkTextView* text_view			= book_view->text_view;
	GList* link_jump_list			= book_view->link_jump_list;

	if(link_jump_list != NULL)
	{
		GtkTextMark* mark = GTK_TEXT_MARK(link_jump_list->data);
		gtk_text_view_scroll_to_mark(text_view, mark, 0.0, TRUE, 0.0, 0.0);

		book_view->link_jump_list = g_list_remove(link_jump_list, mark);
	}
}
