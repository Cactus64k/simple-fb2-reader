#include "../chunks.h"

void file_open_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkFileChooserDialog* file_open_dialog	= GLOBAL_FB2_READER.filechooserdialog;

	if(gtk_dialog_run(GTK_DIALOG(file_open_dialog)) == 2)
	{
		gtk_widget_hide(GTK_WIDGET(file_open_dialog));

		char* file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_open_dialog));
		reader_close_book();

		reader_open_book(file_path);

		g_free(file_path);
	}

	gtk_widget_hide(GTK_WIDGET(file_open_dialog));
}

void book_search_imagemenuitem_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	GtkWidget* search_window	= GLOBAL_SEARCH_WND.search_wnd;
	GtkEntry* search_entry		= GLOBAL_SEARCH_WND.search_query_entry;
	gtk_widget_show(search_window);
	gtk_widget_grab_focus(GTK_WIDGET(search_entry));
}


void book_position_imagemenuitem_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	GKeyFile* book_config		= GLOBAL_FB2_READER.book_config;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view		= GLOBAL_FB2_READER.book_text_view.text_view;

	if(book_config != NULL)
	{
		gint read_line				= g_key_file_get_int64(book_config, "book", "read_line", NULL);
		gint read_line_offset		= g_key_file_get_int64(book_config, "book", "read_line_offset", NULL);

		GtkTextIter iter;
		gtk_text_buffer_get_iter_at_line_offset(text_buff, &iter, read_line, read_line_offset);
		gtk_text_view_scroll_to_iter(text_view, &iter, 0.f, TRUE, 0.f, 0.0f);
	}
}

gboolean main_wnd_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	reader_close();

	return FALSE;
}

void main_wnd_destroy_cb(GtkWidget *object, gpointer user_data)
{

	reader_close_book();
	gtk_main_quit();
}



void book_navigation_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkDialog* dialog			= GLOBAL_FB2_READER.navigation_dialog;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view		= GLOBAL_FB2_READER.book_text_view.text_view;
	GtkTreeView* tree_view		= GLOBAL_FB2_READER.book_text_view.sections_treeview;
	GtkTreeStore* section_store	= GLOBAL_FB2_READER.book_text_view.sections_treestore;
	GtkTextIter text_iter;
	GtkTreeIter tree_iter;
	gint string_number = 0;

	if(gtk_dialog_run(dialog) == 2)
	{
		gtk_widget_hide(GTK_WIDGET(dialog));
		GtkTreeModel* tree_model = GTK_TREE_MODEL(section_store);

		GtkTreeSelection* tree_selection = gtk_tree_view_get_selection(tree_view);
		gtk_tree_selection_get_selected(tree_selection, &tree_model, &tree_iter);
		gtk_tree_model_get(GTK_TREE_MODEL(section_store), &tree_iter, SECTION_STRING_COLUMN, &string_number, -1);

		gtk_text_buffer_get_iter_at_line(text_buff, &text_iter, string_number);
		gtk_text_view_scroll_to_iter(text_view, &text_iter, 0.f, TRUE, 0.f, 0.f);
	}

	gtk_widget_hide(GTK_WIDGET(dialog));
}

void main_wnd_size_allocate_cb (GtkWidget *widget, GdkRectangle *allocation, gpointer user_data)
{	GtkTextView* text_view = GTK_TEXT_VIEW(user_data);
	GKeyFile* app_config	= GLOBAL_FB2_READER.app_config;

	gint margin = allocation->width * 0.15;

	gtk_text_view_set_right_margin(text_view, margin);
	gtk_text_view_set_left_margin(text_view, margin);
}

void books_section_treeview_row_activated_cb(GtkTreeView* tree_view, GtkTreePath* path, GtkTreeViewColumn* column, gpointer user_data)
{
	GtkDialog* dialog			= GLOBAL_FB2_READER.navigation_dialog;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view		= GLOBAL_FB2_READER.book_text_view.text_view;
	GtkTreeStore* section_store	= GLOBAL_FB2_READER.book_text_view.sections_treestore;
	GtkTextIter text_iter;
	GtkTreeIter tree_iter;
	gint string_number = 0;

	gtk_widget_hide(GTK_WIDGET(dialog));


	GtkTreeModel* tree_model = GTK_TREE_MODEL(section_store);

	if(gtk_tree_model_get_iter(tree_model, &tree_iter, path) == TRUE)
	{
		gtk_tree_model_get(GTK_TREE_MODEL(section_store), &tree_iter, SECTION_STRING_COLUMN, &string_number, -1);

		gtk_text_buffer_get_iter_at_line(text_buff, &text_iter, string_number);
		gtk_text_view_scroll_to_iter(text_view, &text_iter, 0.f, TRUE, 0.f, 0.f);
	}

}


gboolean main_wnd_key_press_event_cb (GtkWidget* widget, GdkEvent* event, gpointer user_data)
{
	GdkEventKey key_event		= event->key;
	GtkWidget* search_window	= GLOBAL_SEARCH_WND.search_wnd;
	GtkEntry* search_entry		= GLOBAL_SEARCH_WND.search_query_entry;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
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
				if(gtk_text_buffer_get_has_selection(text_buff) == TRUE)
					gtk_text_buffer_copy_clipboard(text_buff, clipboard);
			}

			break;
		default:
			break;
	}

	return TRUE;
}


void settings_color_dark_scheme_checkmenuitem_toggled_cb(GtkCheckMenuItem* checkmenuitem, gpointer user_data)
{
	GtkTextView* text_view		= GLOBAL_FB2_READER.book_text_view.text_view;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	GKeyFile* app_config		= GLOBAL_FB2_READER.app_config;
	GtkTextTagTable* tag_table	= gtk_text_buffer_get_tag_table(text_buff);

	GtkTextTag* default_tag	= gtk_text_tag_table_lookup(tag_table, "default_tag");

	const char* color_theme = NULL;

	if(gtk_check_menu_item_get_active(checkmenuitem))
		color_theme = "dark_theme";
	else
		color_theme = "default_theme";

	char* background_color	= g_key_file_get_string(app_config, color_theme, "background", NULL);
	char* text_color		= g_key_file_get_string(app_config, color_theme, "text", NULL);

	g_return_if_fail(background_color	!= NULL);
	g_return_if_fail(text_color			!= NULL);

	GValue value = G_VALUE_INIT;
	g_value_init(&value, G_TYPE_STRING);

	GdkRGBA color;
	gdk_rgba_parse(&color, background_color);
	gtk_widget_override_background_color(GTK_WIDGET(text_view), GTK_STATE_FLAG_NORMAL, &color);

	g_value_set_string(&value, text_color);
	g_object_set_property(G_OBJECT(default_tag), "foreground", &value);

	g_free(background_color);
	g_free(text_color);

	g_value_unset(&value);

}


