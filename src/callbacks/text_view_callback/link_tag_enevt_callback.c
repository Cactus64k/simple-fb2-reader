#include "../../chunks.h"

gboolean a_tag_event_cb(GtkTextTag* tag, GObject* object, GdkEvent* event, GtkTextIter* iter, gpointer user_data)
{
	GtkTextView* text_view			= GTK_TEXT_VIEW(object);
	GtkTextBuffer* text_buff		= gtk_text_view_get_buffer(text_view);
	GdkCursor* link_cusor			= GLOBAL_FB2_READER.link_cursor;
	GHashTable* links_hash_table	= GLOBAL_FB2_READER.book_text_view.links_hash_table;
	GKeyFile* book_config			= GLOBAL_FB2_READER.book_text_view.config;

	if(event->type == GDK_BUTTON_RELEASE)
	{
		if(event->button.state & GDK_BUTTON1_MASK)
		{
			GValue value = G_VALUE_INIT;
			g_value_init(&value, G_TYPE_STRING);
			g_value_set_string(&value, "purple");
			g_object_set_property(G_OBJECT(tag), "foreground", &value);
			g_value_unset(&value);

			char* href = (char*)g_object_get_data(G_OBJECT(tag), "href");

			if(*href == '#')
			{
				href++;
				gint read_line			= 0;
				gint read_line_offset	= 0;

				get_scroll_line_offset(text_view, &read_line, &read_line_offset);

				g_key_file_set_int64(book_config, "book", "read_line", read_line);
				g_key_file_set_int64(book_config, "book", "read_line_offset", read_line_offset);


				gint link_line_num			= GPOINTER_TO_INT(g_hash_table_lookup(links_hash_table, href));
				GtkTextIter line_iter;

				gtk_text_buffer_get_iter_at_line(text_buff, &line_iter, link_line_num);

				gtk_text_view_scroll_to_iter(text_view, &line_iter, 0.f, TRUE, 0.f, 0.f);
			}
			else
			{
				if(gtk_show_uri(NULL, href, GDK_CURRENT_TIME, NULL) == FALSE)
				{
					fprintf(stderr, _C("ERROR: failed to open URI %s\n"), href);
				}
			}
		}
	}
	else if(event->type == GDK_MOTION_NOTIFY)
	{
		GdkWindow* text_view_window = gtk_text_view_get_window(text_view, GTK_TEXT_WINDOW_TEXT);
		gdk_window_set_cursor(text_view_window, link_cusor);
	}

	return TRUE;
}
