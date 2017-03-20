#include "../callbacks_chunk.h"

G_MODULE_EXPORT gboolean book_textview_scroll_event_cb(GtkTextView *text_view, GdkEventScroll *event, gpointer user_data)
{
	if((event->state & GDK_CONTROL_MASK) && event->type == GDK_SCROLL)
	{
		GtkTextBuffer* text_buff		= gtk_text_view_get_buffer(text_view);
		GtkTextTagTable* text_tag_table	= gtk_text_buffer_get_tag_table(text_buff);
		GtkTextTag* default_tag			= gtk_text_tag_table_lookup(text_tag_table, "default_tag");
		GValue value					= G_VALUE_INIT;

		g_value_init(&value, G_TYPE_DOUBLE);
		g_object_get_property(G_OBJECT(default_tag), "scale", &value);
		double text_scale = g_value_get_double(&value);

		if(event->direction == GDK_SCROLL_UP)
			text_scale = text_scale + 0.1;
		else if(event->direction == GDK_SCROLL_DOWN)
			text_scale = text_scale - 0.1;
		else if(event->direction == GDK_SCROLL_SMOOTH)
			text_scale = text_scale + event->delta_y*(-0.1);

		text_scale = MAX(text_scale, 0.5);
		text_scale = MIN(text_scale, 20.0);

		g_value_set_double(&value, text_scale);
		g_object_set_property(G_OBJECT(default_tag), "scale", &value);
		g_value_unset(&value);

		// FIXME tag-changed signal is not working
		GtkAllocation size_allocation = {.width = gtk_widget_get_allocated_width(GTK_WIDGET(text_view)),
										.height = gtk_widget_get_allocated_height(GTK_WIDGET(text_view))};
		size_allocation.width++;
		gtk_widget_size_allocate(GTK_WIDGET(text_view), &size_allocation);
		size_allocation.width--;
		gtk_widget_size_allocate(GTK_WIDGET(text_view), &size_allocation);

		return TRUE;
	}

	return FALSE;
}
