#include "../callbacks_chunk.h"

G_MODULE_EXPORT gboolean a_tag_event_cb(GtkTextTag* tag, GObject* object, GdkEvent* event, GtkTextIter* iter, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GtkTextView* text_view			= GTK_TEXT_VIEW(object);
	GtkTextBuffer* text_buff		= app->text_buff;
	GdkCursor* cursor_link			= app->cursor_link;
	GHashTable* book_id_table		= app->book_id_table;
	GList* book_jump_list			= app->book_jump_list;

	if(event->type == GDK_BUTTON_RELEASE)
	{
		if(event->button.state & GDK_BUTTON1_MASK)
		{
			GValue value = G_VALUE_INIT;
			g_value_init(&value, G_TYPE_STRING);
			g_value_set_string(&value, "purple");
			g_object_set_property(G_OBJECT(tag), "foreground", &value);
			g_value_unset(&value);

			char* href = g_object_get_data(G_OBJECT(tag), "href");

			if(*href == '#')
			{
				href++;

				GtkTextMark* mark = gtk_text_buffer_create_mark(text_buff, NULL, iter, TRUE);
				app->book_jump_list = g_list_prepend(book_jump_list, mark);

				gint link_line_num	= GPOINTER_TO_INT(g_hash_table_lookup(book_id_table, href));

				reader_scroll_to_line_offset(app, link_line_num, 0);
			}
			else if(strncmp("file://", href, sizeof("file://") -1) == 0)
			{
				if(reader_get_book_type(href) != BOOK_TYPE_NONE)
				{
					reader_close_book(app);
					reader_open_book(app, href + sizeof("file://") - 1);
				}
			}
			else
			{
				GError* error = NULL;
				if(gtk_show_uri_on_window(NULL, href, GDK_CURRENT_TIME, NULL) == FALSE)
					g_log(NULL, G_LOG_LEVEL_WARNING, "%s: %s",error->message,  href);
			}
		}
	}
	else if(event->type == GDK_MOTION_NOTIFY)
	{
		GdkWindow* text_view_window = gtk_text_view_get_window(text_view, GTK_TEXT_WINDOW_TEXT);
		gdk_window_set_cursor(text_view_window, cursor_link);
	}

	return TRUE;
}

