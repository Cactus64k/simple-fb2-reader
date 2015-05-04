#include "../callbacks_chunk.h"

gboolean book_textview_query_tooltip_cb(GtkWidget* widget, gint x, gint y, gboolean keyboard_mode, GtkTooltip* tooltip, gpointer user_data)
{
	if(keyboard_mode != TRUE)
	{
		GtkTextView* text_view	= GTK_TEXT_VIEW(widget);
		GtkTextIter iter;
		gint bx, by;
		gtk_text_view_window_to_buffer_coords(text_view, GTK_TEXT_WINDOW_WIDGET, x, y, &bx, &by);
		gtk_text_view_get_iter_at_location(text_view, &iter, bx, by);

		GSList* tag_list		= gtk_text_iter_get_tags(&iter);
		GSList* tag = tag_list;

		while(tag != NULL)
		{
			char* href = g_object_get_data(G_OBJECT(tag->data), "href");
			if(href != NULL)
			{
				gtk_tooltip_set_text(tooltip, href);
				g_slist_free(tag_list);

				return TRUE;
			}

			tag = tag->next;
		}

		g_slist_free(tag_list);
	}

	return FALSE;
}
