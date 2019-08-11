#include "../reader_chunks.h"

int reader_app_config(APP* app)
{
	const char* conf_dir		= g_get_user_config_dir();
	assert(conf_dir != NULL);

	GKeyFile* app_config		= g_key_file_new();

	char* app_config_folder		= g_strdup_printf("%s/simple-fb2-reader/", conf_dir);
	g_mkdir_with_parents(app_config_folder, 0755);
	g_free(app_config_folder);

	char* app_config_path		= g_strdup_printf("%s/simple-fb2-reader/config.cfg", conf_dir);
	GError* error				= NULL;

	char* app_css_path			= g_strdup_printf("%s/simple-fb2-reader/simple-fb2-reader.css", conf_dir);

	if(g_key_file_load_from_file(app_config, app_config_path, G_KEY_FILE_NONE, &error) == FALSE)
	{
		g_key_file_set_integer(app_config,	"app",				"x_pos", 640/2);
		g_key_file_set_integer(app_config,	"app",				"y_pos", 480/2);
		g_key_file_set_integer(app_config,	"app",				"width", 640);
		g_key_file_set_integer(app_config,	"app",				"height", 480);
		g_key_file_set_boolean(app_config,	"app",				"maximize", FALSE);
		g_key_file_set_integer(app_config,	"app",				"auto_scroll_period", 60);
		g_key_file_set_double(app_config,	"app",				"font_scale", 1.0);
		g_key_file_set_integer(app_config,	"app",				"pixels_inside_wrap", 12);
		g_key_file_set_integer(app_config,	"app",				"pixels_above_lines", 12);

		g_log(NULL, G_LOG_LEVEL_WARNING, "%s: %s", error->message, app_config_path);

		g_error_free(error);
	}
	else
	{
		if(g_key_file_has_key(app_config,		"app",				"x_pos", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"x_pos", 640/2);

		if(g_key_file_has_key(app_config,		"app",				"y_pos", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"y_pos", 480/2);

		if(g_key_file_has_key(app_config,		"app",				"width", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"width", 640);

		if(g_key_file_has_key(app_config,		"app",				"height", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"height", 480);

		if(g_key_file_has_key(app_config,		"app",				"maximize", NULL) == FALSE)
			g_key_file_set_boolean(app_config,	"app",				"maximize", FALSE);

		if(g_key_file_has_key(app_config,		"app",				"auto_scroll_period", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"auto_scroll_period", 60);

		if(g_key_file_has_key(app_config,		"app",				"font_scale", NULL) == FALSE)
			g_key_file_set_double(app_config,	"app",				"font_scale", 1.0);

		if(g_key_file_has_key(app_config,		"app",				"pixels_inside_wrap", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"pixels_inside_wrap", 12);

		if(g_key_file_has_key(app_config,		"app",				"pixels_above_lines", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"pixels_above_lines", 12);
	}

	app->app_config				= app_config;
	app->app_config_path		= app_config_path;
	app->app_css_path			= app_css_path;

	return EXIT_SUCCESS;
}
