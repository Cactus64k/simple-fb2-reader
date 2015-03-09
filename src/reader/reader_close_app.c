#include "../chunks.h"

int reader_close_app()
{
	GKeyFile* app_config				= GLOBAL_FB2_READER.app_config;
	char* app_config_path				= GLOBAL_FB2_READER.app_config_path;
	GtkWidget* main_wnd					= GLOBAL_FB2_READER.main_wnd;
	GtkCheckMenuItem* color_check_item	= GLOBAL_FB2_READER.color_check_item;

	GValue main_wnd_maximize = G_VALUE_INIT;
	g_value_init(&main_wnd_maximize, G_TYPE_BOOLEAN);
	g_object_get_property(G_OBJECT(main_wnd), "is-maximized", &main_wnd_maximize);

	g_key_file_set_boolean(app_config, "app",				"maximize",	g_value_get_boolean(&main_wnd_maximize));

	gboolean state = gtk_check_menu_item_get_active(color_check_item);
	g_key_file_set_boolean(app_config, "app",				"dark_color_cheme",		state);

	gint main_wnd_width = 0;
	gint main_wnd_height = 0;
	gtk_window_get_size(GTK_WINDOW(main_wnd), &main_wnd_width, &main_wnd_height);
	g_key_file_set_integer(app_config, "app",				"width",		main_wnd_width);
	g_key_file_set_integer(app_config, "app",				"height",		main_wnd_height);

	gint main_wnd_x_pos = 0;
	gint main_wnd_y_pos = 0;
	gtk_window_get_position(GTK_WINDOW(main_wnd), &main_wnd_x_pos, &main_wnd_y_pos);
	g_key_file_set_integer(app_config, "app",				"x_pos",		main_wnd_x_pos);
	g_key_file_set_integer(app_config, "app",				"y_pos",		main_wnd_y_pos);

	gsize app_config_len	= 0;
	char* app_config_data	= g_key_file_to_data(app_config, &app_config_len, NULL);

	FILE* f = fopen(app_config_path, "wb");
	fwrite(app_config_data, 1, app_config_len,  f);
	fclose(f);
	g_free(app_config_data);

	return 0;
}
