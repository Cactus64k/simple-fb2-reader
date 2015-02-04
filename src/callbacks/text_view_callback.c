#include "../chunks.h"

gboolean book_textview_motion_notify_event_cb(GtkWidget* widget, GdkEventMotion* event, gpointer user_data)
{
	GtkTextView* text_view		= GTK_TEXT_VIEW(widget);
	GtkTextTag* default_tag		= GLOBAL_FB2_READER.default_tag;
	GdkCursor* def_cursor		= GLOBAL_FB2_READER.def_cursor;

	gint x, y;
	gtk_text_view_window_to_buffer_coords(text_view, GTK_TEXT_WINDOW_WIDGET, event->x, event->y, &x, &y);

	GtkTextIter iter;
	gtk_text_view_get_iter_at_location(text_view, &iter, x, y);

	if(gtk_text_iter_has_tag(&iter, default_tag))
	{
		GdkWindow* text_view_window = gtk_text_view_get_window(text_view, GTK_TEXT_WINDOW_TEXT);
		gdk_window_set_cursor(text_view_window, def_cursor);
	}
	return false;
}


gboolean a_tag_event_cb(GtkTextTag* tag, GObject* object, GdkEvent* event, GtkTextIter* iter, gpointer user_data)
{
	GtkTextView* text_view	= GTK_TEXT_VIEW(object);
	GdkCursor* link_cusor	= GLOBAL_FB2_READER.link_cursor;

	if(event->type == GDK_BUTTON_RELEASE)
	{
		if(event->button.state & GDK_BUTTON1_MASK)
		{
			char* href = (char*)g_object_get_data(G_OBJECT(tag), "href");
			printf("link href=%s\n", href);

			GValue value = G_VALUE_INIT;
			g_value_init(&value, G_TYPE_STRING);
			g_value_set_string(&value, "purple");
			g_object_set_property(G_OBJECT(tag), "foreground", &value);
			g_value_unset(&value);

		}
	}
	else if(event->type == GDK_MOTION_NOTIFY)
	{
		GdkWindow* text_view_window = gtk_text_view_get_window(text_view, GTK_TEXT_WINDOW_TEXT);
		gdk_window_set_cursor(text_view_window, link_cusor);
	}

	return true;
}
