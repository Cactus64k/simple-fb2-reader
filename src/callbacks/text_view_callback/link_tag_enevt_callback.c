#include "../callbacks_chunk.h"

gboolean a_tag_event_cb(GtkTextTag* tag, GObject* object, GdkEvent* event, GtkTextIter* iter, gpointer user_data)
{
	GtkTextView* text_view			= GTK_TEXT_VIEW(object);
	FB2_READER_BOOK_VIEW* book_view	= &(GLOBAL_FB2_READER.book_text_view);
	GtkTextBuffer* text_buff		= GLOBAL_FB2_READER.book_text_view.text_buff;
	GdkCursor* cursor_link			= GLOBAL_FB2_READER.cursor_link;
	GHashTable* links_hash_table	= GLOBAL_FB2_READER.book_text_view.links_hash_table;
	GList* link_jump_list			= GLOBAL_FB2_READER.book_text_view.link_jump_list;

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
				GLOBAL_FB2_READER.book_text_view.link_jump_list = g_list_prepend(link_jump_list, mark);

				gint link_line_num	= GPOINTER_TO_INT(g_hash_table_lookup(links_hash_table, href));
				GtkTextIter line_iter;

				reader_scroll_at_line_offset(book_view, link_line_num, 0);
			}
			else
			{
				if(gtk_show_uri(NULL, href, GDK_CURRENT_TIME, NULL) == FALSE)
					fprintf(stderr, _C("ERROR: failed to open URI %s\n"), href);
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

