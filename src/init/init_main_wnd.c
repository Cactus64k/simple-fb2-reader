#include "../chunks.h"

int init_main_wnd(GtkBuilder* builder, FB2_READER* obj)
{
	memset(obj, 0, sizeof(*obj));

	create_config_dir();
	init_app_config(obj);
	init_main_reader_book_view(builder, obj);


	obj->main_wnd						= GTK_WIDGET(				gtk_builder_get_object(builder, "main_wnd"));
	obj->filechooserdialog				= GTK_FILE_CHOOSER_DIALOG(	gtk_builder_get_object(builder, "book_filechooserdialog"));
	obj->navigation_dialog				= GTK_DIALOG(				gtk_builder_get_object(builder, "navigation_dialog"));
	obj->about_dialog					= GTK_ABOUT_DIALOG(			gtk_builder_get_object(builder, "reader_aboutdialog"));
	obj->sections_treeview				= GTK_TREE_VIEW(			gtk_builder_get_object(builder, "books_section_treeview"));
	obj->color_check_item				= GTK_CHECK_MENU_ITEM(		gtk_builder_get_object(builder, "reader_color_dark_theme_checkmenuitem"));
	obj->forget_books_dialog			= GTK_MESSAGE_DIALOG(		gtk_builder_get_object(builder, "forget_all_books_message_dialog"));



	assert(obj->main_wnd				!= NULL);
	assert(obj->filechooserdialog		!= NULL);
	assert(obj->navigation_dialog		!= NULL);
	assert(obj->sections_treeview		!= NULL);

	const char* conf_dir				= g_get_user_config_dir();
	assert(conf_dir != NULL);

	gboolean color_check_item_state = g_key_file_get_boolean(obj->app_config, "app", "dark_color_cheme", NULL);
	if(gtk_check_menu_item_get_active(obj->color_check_item) != color_check_item_state)
		gtk_check_menu_item_set_active(obj->color_check_item, color_check_item_state);

	gint main_wnd_x_pos = g_key_file_get_integer(obj->app_config, "app", "x_pos", NULL);
	gint main_wnd_y_pos = g_key_file_get_integer(obj->app_config, "app", "y_pos", NULL);
	gtk_window_move(GTK_WINDOW(obj->main_wnd), main_wnd_x_pos, main_wnd_y_pos);

	gint main_wnd_width = g_key_file_get_integer(obj->app_config, "app", "width", NULL);
	gint main_wnd_height = g_key_file_get_integer(obj->app_config, "app", "height", NULL);
	gtk_window_resize(GTK_WINDOW(obj->main_wnd), main_wnd_width, main_wnd_height);


	if(g_key_file_get_boolean(obj->app_config, "app", "maximize", NULL) == TRUE)
		gtk_window_maximize(GTK_WINDOW(obj->main_wnd));

	//create_fb2_tags(obj->text_buff);

	obj->cursor_link				= gdk_cursor_new(GDK_HAND2);
	obj->cursor_watch				= gdk_cursor_new(GDK_WATCH);
	obj->clipboard					= gtk_clipboard_get(0);

	gtk_widget_show_all(obj->main_wnd);

	return 0;
}

