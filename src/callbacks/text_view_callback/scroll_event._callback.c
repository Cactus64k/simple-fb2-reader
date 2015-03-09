#include "../../chunks.h"

gboolean book_textview_scroll_event_cb(GtkTextView *text_view, GdkEventScroll *event, gpointer user_data)
{
	if(event->state & GDK_CONTROL_MASK)
	{
		GtkTextBuffer* text_buff		= gtk_text_view_get_buffer(text_view);
		GtkTextTagTable* text_tag_table	= gtk_text_buffer_get_tag_table(text_buff);
		GtkTextTag* default_tag			= gtk_text_tag_table_lookup(text_tag_table, "default_tag");

		GValue value = G_VALUE_INIT;
		g_value_init(&value, G_TYPE_DOUBLE);

		g_object_get_property(G_OBJECT(default_tag), "scale", &value);

		if(event->direction == GDK_SCROLL_SMOOTH)
		{
			double text_scale = g_value_get_double(&value)+event->delta_y*0.1;

			text_scale = (text_scale<0)? 0: text_scale;
			text_scale = (text_scale>10)? 10: text_scale;

			g_value_set_double(&value, text_scale);
			g_object_set_property(G_OBJECT(default_tag), "scale", &value);
			g_value_unset(&value);
		}

		//gtk_widget_queue_draw(GTK_WIDGET(text_view));

		return TRUE;
	}

	//gtk_widget_queue_draw(GTK_WIDGET(text_view));

	return FALSE;
}


