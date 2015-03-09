#include "../chunks.h"

gboolean main_wnd_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	GtkMessageDialog* save_dialog = GLOBAL_FB2_READER.save_dialog;
	int res = gtk_dialog_run(GTK_DIALOG(save_dialog));
	if(res == 0)		// cancel
	{
		gtk_widget_hide(GTK_WIDGET(save_dialog));
		return TRUE;
	}
	else if(res == 1)	// no
	{

	}
	else if(res == 2)	// yes
		reader_close_book();

	gtk_widget_hide(GTK_WIDGET(save_dialog));
	reader_close_app();

	return FALSE;
}

void file_quit_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkMessageDialog* save_dialog = GLOBAL_FB2_READER.save_dialog;
	int res = gtk_dialog_run(GTK_DIALOG(save_dialog));
	if(res == 0)		// cancel
	{
		gtk_widget_hide(GTK_WIDGET(save_dialog));
		return;
	}
	else if(res == 1)	// no
	{

	}
	else if(res == 2)	// yes
		reader_close_book();

	reader_close_app();
	gtk_main_quit();
}

void main_wnd_destroy_cb(GtkWidget *object, gpointer user_data)
{
	reader_close_book();
	gtk_main_quit();
}

void main_wnd_size_allocate_cb (GtkWidget *widget, GdkRectangle *allocation, gpointer user_data)
{	GtkTextView* text_view = GTK_TEXT_VIEW(user_data);

	gint margin = allocation->width * 0.15;

	gtk_text_view_set_right_margin(text_view, margin);
	gtk_text_view_set_left_margin(text_view, margin);
}

gboolean main_wnd_key_press_event_cb (GtkWidget* widget, GdkEventKey* event, gpointer user_data)
{
	GtkWidget* search_window	= GLOBAL_SEARCH_WND.search_wnd;
	GtkEntry* search_entry		= GLOBAL_SEARCH_WND.search_query_entry;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	BOOK_TYPE book_type			= GLOBAL_FB2_READER.book_text_view.type;
	GtkClipboard* clipboard		= GLOBAL_FB2_READER.clipboard;

	GdkKeymap* default_key_map = gdk_keymap_get_default();

	GdkKeymapKey key = {.keycode	= event->hardware_keycode,
						.group		= 0,
						.level		= 0};

	guint keyval = gdk_keymap_lookup_key(default_key_map, &key);

	if(keyval == 'f')
	{
		if(event->state & GDK_CONTROL_MASK)
		{
			if(book_type != BOOK_TYPE_NONE)
			{
				gtk_widget_show(search_window);
				gtk_widget_grab_focus(GTK_WIDGET(search_entry));
			}
		}
	}
	else if(keyval == 'c')
	{
		if(event->state & GDK_CONTROL_MASK)
		{
			if(gtk_text_buffer_get_has_selection(text_buff) == TRUE)
				gtk_text_buffer_copy_clipboard(text_buff, clipboard);
		}
	}

	return TRUE;
}







