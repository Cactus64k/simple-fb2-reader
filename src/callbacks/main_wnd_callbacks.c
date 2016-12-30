#include "callbacks_chunk.h"

G_MODULE_EXPORT gboolean main_wnd_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	g_return_val_if_fail(user_data != NULL,	EXIT_FAILURE);
	APP* app	= (APP*)user_data;

	reader_close_book(app);
	reader_close_app(app);
	return FALSE;
}

gboolean main_wnd_window_state_event_cb(GtkWidget* widget, GdkEventWindowState* event, gpointer user_data)
{
	g_return_val_if_fail(user_data != NULL,	EXIT_FAILURE);
	APP* app	= (APP*)user_data;

	if((event->new_window_state & GDK_WINDOW_STATE_ICONIFIED)
			||
		(event->new_window_state & GDK_WINDOW_STATE_WITHDRAWN)
			||
		(event->new_window_state & GDK_WINDOW_STATE_BELOW))
	{
		app->auto_scroll = FALSE;
	}

	return TRUE;
}

G_MODULE_EXPORT void main_wnd_size_allocate_cb (GtkWidget *widget, GdkRectangle *allocation, gpointer user_data)
{
	g_return_if_fail(user_data != NULL);
	GtkTextView* text_view = GTK_TEXT_VIEW(user_data);

	gint margin = (allocation->width * 15) / 100;		// 15%

	gtk_text_view_set_right_margin(text_view, margin);
	gtk_text_view_set_left_margin(text_view, margin);
}

G_MODULE_EXPORT gboolean main_wnd_key_press_event_cb (GtkWidget* widget, GdkEventKey* event, gpointer user_data)
{
	g_return_val_if_fail(user_data != NULL,	EXIT_FAILURE);

	APP* app						= (APP*)user_data;
	GtkTextBuffer* text_buff		= app->text_buff;
	GtkTextView* text_view			= app->text_view;
	BOOK_TYPE book_type				= app->book_type;
	GtkClipboard* clipboard			= app->clipboard;
	GdkKeymap* default_key_map		= gdk_keymap_get_default();

	GdkKeymapKey key = {.keycode	= event->hardware_keycode,
						.group		= 0,
						.level		= 0};

	guint keyval = gdk_keymap_lookup_key(default_key_map, &key);

	if(event->state & GDK_CONTROL_MASK)
	{
		if(keyval == 'n')
		{
			if(book_type != BOOK_TYPE_NONE)
				navigation_menuitem_activate_cb(NULL, app);
		}
		else if(keyval == 'f')
		{
			if(book_type != BOOK_TYPE_NONE)
				search_menuitem_activate_cb(NULL, app);
		}
		else if(keyval == 't')
		{
			color_theme_activate_cb(NULL, app);
		}
		else if(keyval == 'h')
		{
			about_menuitem_activate_cb(NULL, app);
		}
		else if(keyval == 'o')
		{
			open_file_menuitem_activate_cb(NULL, app);
		}
		else if((keyval == '0') || (keyval == GDK_KEY_KP_Insert))
		{
			GtkTextTagTable* text_tag_table	= gtk_text_buffer_get_tag_table(text_buff);
			GtkTextTag* default_tag			= gtk_text_tag_table_lookup(text_tag_table, "default_tag");
			GValue value					= G_VALUE_INIT;

			g_value_init(&value, G_TYPE_DOUBLE);
			g_value_set_double(&value, 1.0);
			g_object_set_property(G_OBJECT(default_tag), "scale", &value);
			g_value_unset(&value);

			GtkAllocation size_allocation = {.width = gtk_widget_get_allocated_width(GTK_WIDGET(text_view)),
											.height = gtk_widget_get_allocated_height(GTK_WIDGET(text_view))};

			size_allocation.width++;
			gtk_widget_size_allocate(GTK_WIDGET(text_view), &size_allocation);
			size_allocation.width--;
			gtk_widget_size_allocate(GTK_WIDGET(text_view), &size_allocation);
		}
		else if(keyval == 'q')
		{
			gtk_main_quit();
		}
		else if(keyval == 'c')
		{
			if(gtk_text_buffer_get_has_selection(text_buff) == TRUE)
				gtk_text_buffer_copy_clipboard(text_buff, clipboard);
		}
	}
	else
	{
		if((event->keyval == GDK_KEY_Left) && (book_type != BOOK_TYPE_NONE))
			backward_itemmenu_cb(NULL, app);
	}


	//printf("%x\n", event->keyval);

	return FALSE;
}







