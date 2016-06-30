#include "../chunks.h"

int init_app_config(APP* obj)
{
	const char* conf_dir				= g_get_user_config_dir();
	assert(conf_dir != NULL);

	obj->app_config						= g_key_file_new();
	obj->app_config_path				= g_strdup_printf("%s/simple-fb2-reader/config.cfg", conf_dir);

	if(g_key_file_load_from_file(obj->app_config, obj->app_config_path, G_KEY_FILE_NONE, NULL) == FALSE)
	{
		g_key_file_set_string(obj->app_config, "app",			"color_theme", "default_theme");
		g_key_file_set_integer(obj->app_config, "app",			"x_pos", 640/2);
		g_key_file_set_integer(obj->app_config, "app",			"y_pos", 480/2);
		g_key_file_set_integer(obj->app_config, "app",			"width", 640);
		g_key_file_set_integer(obj->app_config, "app",			"height", 480);
		g_key_file_set_boolean(obj->app_config, "app",			"maximize", FALSE);
		g_key_file_set_double(obj->app_config, "app",			"font_scale", 1.0);

		g_key_file_set_string(obj->app_config, "default_theme",	"background", "#ffffff");
		g_key_file_set_string(obj->app_config, "default_theme",	"text", "#000000");
		g_key_file_set_string(obj->app_config, "default_theme",	"selection", "rgba(132, 169, 215, 200)");
		g_key_file_set_string(obj->app_config, "default_theme",	"font_general", "DejaVu");
		g_key_file_set_string(obj->app_config, "default_theme",	"font_monospace", "monospace");
		g_key_file_set_integer(obj->app_config, "default_theme","line_spacing", 10);

		g_key_file_set_string(obj->app_config, "dark_theme",	"background", "#293134");
		g_key_file_set_string(obj->app_config, "dark_theme",	"text", "#e8e2b7");
		g_key_file_set_string(obj->app_config, "dark_theme",	"selection", "rgba(100, 100, 100, 200)");
		g_key_file_set_string(obj->app_config, "dark_theme",	"font_general", "DejaVu");
		g_key_file_set_string(obj->app_config, "dark_theme",	"font_monospace", "monospace");
		g_key_file_set_integer(obj->app_config, "dark_theme",	"line_spacing", 10);
	}

	return EXIT_SUCCESS;
}
