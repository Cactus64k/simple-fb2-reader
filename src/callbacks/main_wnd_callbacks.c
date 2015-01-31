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
		default:
			break;
	}

	return true;
}


gboolean a_tag_event_cb(GtkTextTag* tag, GObject* object, GdkEventButton* event, GtkTextIter* iter, gpointer user_data)
{
	if(event->type == GDK_BUTTON_RELEASE)
		if(event->state & GDK_BUTTON1_MASK)
		{
			char* href = (char*)g_object_get_data(G_OBJECT(tag), "href");
			printf("link href=%s\n", href);
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
		color.alpha	= 1;
		color.blue	= 0.21176470588;
		color.green	= 0.20392156863;
		color.red	= 0.18039215686;
		gtk_widget_override_background_color(GTK_WIDGET(text_view), GTK_STATE_FLAG_NORMAL, &color);
		g_value_set_string(&value, "white");

		printf("Apply dark color scheme\n");
	}
	else
	{
		color.alpha	= 1;
		color.blue	= 1;
		color.green	= 1;
		color.red	= 1;
		gtk_widget_override_background_color(GTK_WIDGET(text_view), GTK_STATE_FLAG_NORMAL, &color);
		g_value_set_string(&value, "black");

		printf("Apply white color scheme\n");
	}

	g_object_set_property(G_OBJECT(default_tag), "foreground", &value);
	g_value_unset(&value);



}


