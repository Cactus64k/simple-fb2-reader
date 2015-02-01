#include "../chunks.h"

void file_open_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkFileChooserDialog* file_open_dialog	= GLOBAL_FB2_READER.filechooserdialog;

	if(gtk_dialog_run(GTK_DIALOG(file_open_dialog)) == 2)
	{
		gtk_widget_hide(GTK_WIDGET(file_open_dialog));

		char* file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_open_dialog));
		open_book(file_path);

		g_free(file_path);
	}

	gtk_widget_hide(GTK_WIDGET(file_open_dialog));
}


void file_search_imagemenuitem_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	GtkWidget* search_window	= GLOBAL_SEARCH_WND.search_wnd;
	GtkEntry* search_entry		= GLOBAL_SEARCH_WND.search_query_entry;
	gtk_widget_show(search_window);
	gtk_widget_grab_focus(GTK_WIDGET(search_entry));
}



void file_navigation_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	/*GtkDialog* dialog = GLOBAL_FB2_READER.navigation_dialog;

	if(gtk_dialog_run(dialog) == 2)
	{
		gtk_widget_hide(GTK_WIDGET(dialog));
	}

	gtk_widget_hide(GTK_WIDGET(dialog));*/
}



gboolean main_wnd_configure_event_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	GtkTextView* text_view = GTK_TEXT_VIEW(user_data);
	GtkAllocation allocated_size;

	gtk_widget_get_allocation(GTK_WIDGET(text_view), &allocated_size);

	size_t margin = allocated_size.width * 0.15;

	gtk_text_view_set_right_margin(text_view, margin);
	gtk_text_view_set_left_margin(text_view, margin);

	//******************************************************************************************************

	GtkTextTag* epigraph_tag	= GLOBAL_FB2_READER.epigraph_tag;

	GValue value = G_VALUE_INIT;
	g_value_init(&value, G_TYPE_INT);

	g_value_set_int(&value, (allocated_size.width + margin) * EPIGRAPH_TAG_MARGIN);
	g_object_set_property(G_OBJECT(epigraph_tag), "left-margin", &value);
	g_object_set_property(G_OBJECT(epigraph_tag), "right-margin", &value);

	g_value_unset(&value);


	/*GdkRectangle rect;
	gtk_text_view_get_visible_rect(text_view, &rect);
	printf("\n\nx=%d\ny=%d\nw=%d\nh=%d\n", rect.x, rect.y, rect.width, rect.height);*/


	return false;
}



gboolean main_wnd_key_press_event_cb (GtkWidget* widget, GdkEvent* event, gpointer user_data)
{
	GdkEventKey key_event		= event->key;
	GtkWidget* search_window	= GLOBAL_SEARCH_WND.search_wnd;
	GtkEntry* search_entry		= GLOBAL_SEARCH_WND.search_query_entry;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.text_buff;
	GtkClipboard* clipboard		= GLOBAL_FB2_READER.clipboard;

	switch(key_event.keyval)
	{
		case GDK_KEY_f:
		case GDK_KEY_F:
			if(key_event.state & GDK_CONTROL_MASK)
			{
				gtk_widget_show(search_window);
				gtk_widget_grab_focus(GTK_WIDGET(search_entry));
			}

			break;
		case GDK_KEY_C:
		case GDK_KEY_c:
			if(key_event.state & GDK_CONTROL_MASK)
			{
				if(gtk_text_buffer_get_has_selection(text_buff) == true)
				{
					gtk_text_buffer_copy_clipboard(text_buff, clipboard);
				}
			}

			break;
		default:
			break;
	}

	return true;
}

void settings_color_dark_scheme_checkmenuitem_toggled_cb(GtkCheckMenuItem* checkmenuitem, gpointer user_data)
{
	GtkTextView* text_view	= GLOBAL_FB2_READER.text_view;
	GtkTextTag* default_tag	= GLOBAL_FB2_READER.default_tag;
	GdkRGBA color;
	GValue value = G_VALUE_INIT;
	g_value_init(&value, G_TYPE_STRING);

	if(gtk_check_menu_item_get_active(checkmenuitem))
	{
		gdk_rgba_parse(&color, "#293134");
		gtk_widget_override_background_color(GTK_WIDGET(text_view), GTK_STATE_FLAG_NORMAL, &color);
		g_value_set_string(&value, "white");

		printf("Apply dark color scheme\n");
	}
	else
	{
		gdk_rgba_parse(&color, "#ffffff");
		gtk_widget_override_background_color(GTK_WIDGET(text_view), GTK_STATE_FLAG_NORMAL, &color);
		g_value_set_string(&value, "black");

		printf("Apply white color scheme\n");
	}

	g_object_set_property(G_OBJECT(default_tag), "foreground", &value);
	g_value_unset(&value);



}


