#include "../chunks.h"

int main_wnd_init(GtkBuilder* builder, FB2_READER* obj)
{
	create_config_dir();
	init_main_reader_text_view(builder, obj);

	obj->main_wnd						= GTK_WIDGET(				gtk_builder_get_object(builder, "main_wnd"));
	obj->filechooserdialog				= GTK_FILE_CHOOSER_DIALOG(	gtk_builder_get_object(builder, "book_filechooserdialog"));
	obj->navigation_dialog				= GTK_DIALOG(				gtk_builder_get_object(builder, "navigation_dialog"));

	GtkCheckMenuItem* color_check_item	= GTK_CHECK_MENU_ITEM(		gtk_builder_get_object(builder, "book_color_dark_scheme_checkmenuitem"));

	assert(obj->main_wnd				!= NULL);
	assert(obj->filechooserdialog		!= NULL);
	assert(obj->navigation_dialog		!= NULL);
	const char* conf_dir				= g_get_user_config_dir();
	assert(conf_dir != NULL);

	obj->app_config						= g_key_file_new();
	obj->app_config_path				= g_strdup_printf("%s/simple-fb2-reader/config.cfg", conf_dir);


	if(g_key_file_load_from_file(obj->app_config, obj->app_config_path, G_KEY_FILE_NONE, NULL) == FALSE)
	{
		g_key_file_set_boolean(obj->app_config, "app",				"dark_color_cheme",		FALSE);

		g_key_file_set_integer(obj->app_config, "app",				"x_pos",		640/2);
		g_key_file_set_integer(obj->app_config, "app",				"y_pos",		480/2);
		g_key_file_set_integer(obj->app_config, "app",				"width",		640);
		g_key_file_set_integer(obj->app_config, "app",				"height",		480);
		g_key_file_set_boolean(obj->app_config, "app",				"maximize",	FALSE);


	}

	if(g_key_file_get_boolean(obj->app_config, "app", "dark_color_cheme", NULL) == TRUE)
		gtk_check_menu_item_set_active(color_check_item, TRUE);

	gint main_wnd_x_pos = g_key_file_get_integer(obj->app_config, "app", "x_pos", NULL);
	gint main_wnd_y_pos = g_key_file_get_integer(obj->app_config, "app", "y_pos", NULL);
	gtk_window_move(GTK_WINDOW(obj->main_wnd), main_wnd_x_pos, main_wnd_y_pos);

	gint main_wnd_width = g_key_file_get_integer(obj->app_config, "app", "width", NULL);
	gint main_wnd_height = g_key_file_get_integer(obj->app_config, "app", "height", NULL);
	gtk_window_resize(GTK_WINDOW(obj->main_wnd), main_wnd_width, main_wnd_height);


	if(g_key_file_get_boolean(obj->app_config, "app", "maximize", NULL) == TRUE)
		gtk_window_maximize(GTK_WINDOW(obj->main_wnd));

	//create_fb2_tags(obj->text_buff);

	obj->link_cursor				= gdk_cursor_new(GDK_HAND2);
	obj->def_cursor					= gdk_cursor_new(GDK_ARROW);
	obj->clipboard					= gtk_clipboard_get(0);

	gtk_widget_show_all(obj->main_wnd);

	return 0;
}


