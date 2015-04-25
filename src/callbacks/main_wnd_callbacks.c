#include "callbacks_chunk.h"

gboolean main_wnd_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	reader_close_book();
	reader_close_app();
	return FALSE;
}

void file_quit_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	reader_close_book();
	reader_close_app();
	gtk_main_quit();
}

void main_wnd_size_allocate_cb (GtkWidget *widget, GdkRectangle *allocation, gpointer user_data)
{	GtkTextView* text_view = GTK_TEXT_VIEW(user_data);

	gint margin = (allocation->width * 15) / 100;

	gtk_text_view_set_right_margin(text_view, margin);
	gtk_text_view_set_left_margin(text_view, margin);
}

gboolean main_wnd_key_press_event_cb (GtkWidget* widget, GdkEventKey* event, gpointer user_data)
{
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	BOOK_TYPE book_type			= GLOBAL_FB2_READER.book_text_view.type;
	GtkClipboard* clipboard		= GLOBAL_FB2_READER.clipboard;

	GdkKeymap* default_key_map = gdk_keymap_get_default();

	GdkKeymapKey key = {.keycode	= event->hardware_keycode,
						.group		= 0,
						.level		= 0};

	guint keyval = gdk_keymap_lookup_key(default_key_map, &key);

	if(event->state & GDK_CONTROL_MASK)
	{
		if(keyval == 'n')
		{
			if(book_type != BOOK_TYPE_NONE && book_type != BOOK_TYPE_TXT)
				navigation_imagemenuitem_activate_cb(NULL, NULL);
		}
		else if(keyval == 'f')
		{
			search_imagemenuitem_activate_cb(NULL, NULL);
		}
		else if(keyval == 'e')
		{
			if(book_type == BOOK_TYPE_TXT)
				encoding_imagemenuitem_activate_cb(NULL, NULL);
		}
		else if(keyval == 't')
		{
			//color_theme_activate_cb(NULL, NULL);
		}
		else if(keyval == 'd')
		{
			forger_books_imagemenuitem_activate_cb(NULL, NULL);
		}
		else if(keyval == 'h')
		{
			about_imagemenuitem_activate_cb(NULL, NULL);
		}
		else if(keyval == 'o')
		{
			open_file_imagemenuitem_activate_cb(NULL, NULL);
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
		if(event->keyval == GDK_KEY_Left)
			backward_itemmenu_cb(NULL, NULL);
	}


	//printf("%x\n", event->keyval);

	return FALSE;
}







