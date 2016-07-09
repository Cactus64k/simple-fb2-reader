#include "callbacks_chunk.h"

G_MODULE_EXPORT gboolean main_wnd_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	APP* app	= (APP*)user_data;
	reader_scroll_save(app);
	reader_close_book(app);
	reader_close_app(app);
	return FALSE;
}

gboolean main_wnd_window_state_event_cb(GtkWidget* widget, GdkEventWindowState* event, gpointer user_data)
{
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
{	GtkTextView* text_view = GTK_TEXT_VIEW(user_data);

	gint margin = (allocation->width * 15) / 100;		// 15%

	gtk_text_view_set_right_margin(text_view, margin);
	gtk_text_view_set_left_margin(text_view, margin);
}

G_MODULE_EXPORT gboolean main_wnd_key_press_event_cb (GtkWidget* widget, GdkEventKey* event, gpointer user_data)
{
	APP* app					= (APP*)user_data;
	GtkTextBuffer* text_buff	= app->text_buff;
	BOOK_TYPE book_type			= app->book_type;
	GtkClipboard* clipboard		= app->clipboard;

	GdkKeymap* default_key_map = gdk_keymap_get_default();

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







