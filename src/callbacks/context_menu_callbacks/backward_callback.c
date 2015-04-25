#include "../callbacks_chunk.h"

void backward_itemmenu_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	FB2_READER_BOOK_VIEW* book_view	= &(GLOBAL_FB2_READER.book_text_view);
	GtkTextView* text_view			= book_view->text_view;
	GList* link_jump_list			= book_view->link_jump_list;

	GtkAdjustment* horisontal_adj	= gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(text_view));

	if(link_jump_list != NULL)
	{
		GtkTextMark* mark = GTK_TEXT_MARK(link_jump_list->data);
		gtk_text_view_scroll_to_mark(text_view, mark, 0.0, TRUE, 0.0, 0.0);

		gtk_adjustment_set_value(horisontal_adj, 0.0);

		book_view->link_jump_list = g_list_remove(link_jump_list, mark);
	}
}
