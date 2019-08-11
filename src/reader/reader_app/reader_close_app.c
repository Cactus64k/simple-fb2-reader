#include "reader_app.h"

int reader_close_app(APP* app)
{
	GKeyFile* app_config			= app->app_config;
	char* app_config_path			= app->app_config_path;
	char* app_css_path				= app->app_css_path;
	GtkWidget* main_wnd				= app->main_wnd;
	GdkCursor* cursor_link			= app->cursor_link;
	GdkCursor* cursor_watch			= app->cursor_watch;
	GtkTextBuffer* text_buff		= app->text_buff;
	sqlite3* db						= app->book_db;

	app->auto_scroll				= FALSE;

	GtkTextTagTable* text_tag_table	= gtk_text_buffer_get_tag_table(text_buff);
	GtkTextTag* default_tag			= gtk_text_tag_table_lookup(text_tag_table, "default_tag");
	//**************************************************************************************************
	GValue value = G_VALUE_INIT;
	g_value_init(&value, G_TYPE_BOOLEAN);
	g_object_get_property(G_OBJECT(main_wnd), "is-maximized", &value);
	g_key_file_set_boolean(app_config, "app",				"maximize",	g_value_get_boolean(&value));
	g_value_unset(&value);
	//**************************************************************************************************
	g_value_init(&value, G_TYPE_DOUBLE);
	g_object_get_property(G_OBJECT(default_tag), "scale", &value);
	double font_scale = g_value_get_double(&value);
	g_key_file_set_double(app_config, "app",				"font_scale",		font_scale);
	g_value_unset(&value);
	//**************************************************************************************************
	gint main_wnd_width = 0;
	gint main_wnd_height = 0;
	gtk_window_get_size(GTK_WINDOW(main_wnd), &main_wnd_width, &main_wnd_height);
	g_key_file_set_integer(app_config, "app",				"width",			main_wnd_width);
	g_key_file_set_integer(app_config, "app",				"height",			main_wnd_height);
	//**************************************************************************************************
	gint main_wnd_x_pos = 0;
	gint main_wnd_y_pos = 0;
	gtk_window_get_position(GTK_WINDOW(main_wnd), &main_wnd_x_pos, &main_wnd_y_pos);
	g_key_file_set_integer(app_config, "app",				"x_pos",			main_wnd_x_pos);
	g_key_file_set_integer(app_config, "app",				"y_pos",			main_wnd_y_pos);
	//**************************************************************************************************

	if(g_key_file_save_to_file(app_config, app_config_path, NULL) == FALSE)
		g_log(NULL, G_LOG_LEVEL_WARNING, "Failed to write app config");

	g_object_unref(cursor_link);
	g_object_unref(cursor_watch);

	g_free(app_config_path);
	g_free(app_css_path);

	sqlite3_close(db);

	return EXIT_SUCCESS;
}
