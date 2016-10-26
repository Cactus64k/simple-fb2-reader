#include "../reader_chunks.h"

int reader_app_config(APP* app)
{
	const char* conf_dir		= g_get_user_config_dir();
	assert(conf_dir != NULL);

	GKeyFile* app_config		= g_key_file_new();

	char* app_config_folder		= g_strdup_printf("%s/simple-fb2-reader/", conf_dir);
	g_mkdir_with_parents(app_config_folder, 0666);
	g_free(app_config_folder);

	char* app_config_path		= g_strdup_printf("%s/simple-fb2-reader/config.cfg", conf_dir);
	GError* error				= NULL;

	if(g_key_file_load_from_file(app_config, app_config_path, G_KEY_FILE_NONE, &error) == FALSE)
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

		g_warning("%s: %s", error->message, app_config_path);

		g_error_free(error);
	}
	else
	{
		if(g_key_file_has_key(app_config,		"app",				"color_theme", NULL) == FALSE)
			g_key_file_set_string(app_config,	"app",				"color_theme", "default_theme");

		if(g_key_file_has_key(app_config,		"app",				"x_pos", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"x_pos", 640/2);

		if(g_key_file_has_key(app_config,		"app",				"y_pos", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"y_pos", 480/2);

		if(g_key_file_has_key(app_config,		"app",				"width", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"width", 640);

		if(g_key_file_has_key(app_config,		"app",				"height", NULL) == FALSE)
			g_key_file_set_integer(app_config,	"app",				"height", 480);

		if(g_key_file_has_key(app_config,		"app",				"maximize", NULL) == FALSE)
			g_key_file_set_boolean(app_config,"app",				"maximize", FALSE);

		if(g_key_file_has_key(app_config,		"app",				"auto_scroll_divider", NULL) == FALSE)
			g_key_file_set_double(app_config,	"app",				"auto_scroll_divider", 4096);

		if(g_key_file_has_key(app_config,		"app",				"font_scale", NULL) == FALSE)
			g_key_file_set_double(app_config,	"app",				"font_scale", 1.0);



		char* cur_theme		= g_key_file_get_string(app_config,	"app", "color_theme", NULL);

		if(g_key_file_has_key(app_config,		cur_theme,	"background", NULL) == FALSE)
			g_key_file_set_string(app_config,	cur_theme,	"background", "#ffffff");

		if(g_key_file_has_key(app_config,		cur_theme,	"text", NULL) == FALSE)
			g_key_file_set_string(app_config,	cur_theme,	"text", "#000000");

		if(g_key_file_has_key(app_config,		cur_theme,	"selection", NULL) == FALSE)
			g_key_file_set_string(app_config,	cur_theme,	"selection", "rgba(132, 169, 215, 200)");

		if(g_key_file_has_key(app_config,		cur_theme,	"font_general", NULL) == FALSE)
			g_key_file_set_string(app_config,	cur_theme,	"font_general", "DejaVu");

		if(g_key_file_has_key(app_config,		cur_theme,	"font_monospace", NULL) == FALSE)
			g_key_file_set_string(app_config,	cur_theme,	"font_monospace", "monospace");

		if(g_key_file_has_key(app_config,		cur_theme,	"line_spacing", NULL) == FALSE)
			g_key_file_set_integer(app_config,	cur_theme,	"line_spacing", 10);


		g_free(cur_theme);

	}

	app->app_config				= app_config;
	app->app_config_path		= app_config_path;

	return EXIT_SUCCESS;
}
