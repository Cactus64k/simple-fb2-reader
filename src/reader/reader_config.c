#include "../chunks.h"

int reader_read_config(APP* app)
{
	const char* conf_dir				= g_get_user_config_dir();
	assert(conf_dir != NULL);

	GKeyFile* app_config				= g_key_file_new();

	app->app_config_path				= g_strdup_printf("%s/simple-fb2-reader/config.cfg", conf_dir);

	GError* error						= NULL;

	if(g_key_file_load_from_file(app_config, app->app_config_path, G_KEY_FILE_NONE, &error) == FALSE)
	{
		g_key_file_set_string(app_config,	"app",				"color_theme", "default_theme");
		g_key_file_set_integer(app_config,	"app",				"x_pos", 640/2);
		g_key_file_set_integer(app_config,	"app",				"y_pos", 480/2);
		g_key_file_set_integer(app_config,	"app",				"width", 640);
		g_key_file_set_integer(app_config,	"app",				"height", 480);
		g_key_file_set_boolean(app_config,	"app",				"maximize", FALSE);
		g_key_file_set_boolean(app_config,	"app",				"auto_scroll", FALSE);
		g_key_file_set_double(app_config,	"app",				"auto_scroll_divider", 4096);
		g_key_file_set_double(app_config,	"app",				"font_scale", 1.0);

		g_key_file_set_string(app_config,	"default_theme",	"background", "#ffffff");
		g_key_file_set_string(app_config,	"default_theme",	"text", "#000000");
		g_key_file_set_string(app_config,	"default_theme",	"selection", "rgba(132, 169, 215, 200)");
		g_key_file_set_string(app_config,	"default_theme",	"font_general", "DejaVu");
		g_key_file_set_string(app_config,	"default_theme",	"font_monospace", "monospace");
		g_key_file_set_integer(app_config,	"default_theme",	"line_spacing", 10);

		g_key_file_set_string(app_config,	"dark_theme",		"background", "#293134");
		g_key_file_set_string(app_config,	"dark_theme",		"text", "#e8e2b7");
		g_key_file_set_string(app_config,	"dark_theme",		"selection", "rgba(100, 100, 100, 200)");
		g_key_file_set_string(app_config,	"dark_theme",		"font_general", "DejaVu");
		g_key_file_set_string(app_config,	"dark_theme",		"font_monospace", "monospace");
		g_key_file_set_integer(app_config,	"dark_theme",		"line_spacing", 10);
	}

	reader_hndl_GError(app, &error);

	app->app_config						= app_config;

	return EXIT_SUCCESS;
}
