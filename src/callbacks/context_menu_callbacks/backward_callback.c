#include "../callbacks_chunk.h"

G_MODULE_EXPORT void backward_itemmenu_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GtkTextView* text_view			= app->text_view;
	GList* book_jump_list			= app->book_jump_list;

	GtkAdjustment* horisontal_adj	= gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(text_view));

	if(book_jump_list != NULL)
	{
		GtkTextMark* mark = GTK_TEXT_MARK(book_jump_list->data);
		gtk_text_view_scroll_to_mark(text_view, mark, 0.0, TRUE, 0.0, 0.0);

		gtk_adjustment_set_value(horisontal_adj, 0.0);

		app->book_jump_list = g_list_remove(book_jump_list, mark);
	}
}
