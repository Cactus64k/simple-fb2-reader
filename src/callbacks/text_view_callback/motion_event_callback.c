#include "../../chunks.h"

gboolean book_textview_motion_notify_event_cb(GtkWidget* widget, GdkEventMotion* event, gpointer user_data)
{
	GtkTextView* text_view		= GTK_TEXT_VIEW(widget);

	GdkWindow* text_view_window = gtk_text_view_get_window(text_view, GTK_TEXT_WINDOW_TEXT);
	gdk_window_set_cursor(text_view_window, NULL);


	return FALSE;
}
