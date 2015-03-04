#include "../chunks.h"

int init_app_config(FB2_READER* obj)
{
	const char* conf_dir				= g_get_user_config_dir();
	assert(conf_dir != NULL);

	obj->app_config						= g_key_file_new();
	obj->app_config_path				= g_strdup_printf("%s/simple-fb2-reader/config.cfg", conf_dir);

	g_key_file_load_from_file(obj->app_config, obj->app_config_path, G_KEY_FILE_NONE, NULL);


	if(g_key_file_has_key(obj->app_config, "app",				"dark_color_cheme", NULL) == FALSE)
		g_key_file_set_boolean(obj->app_config, "app",			"dark_color_cheme", FALSE);

	if(g_key_file_has_key(obj->app_config, "app",				"x_pos", NULL) == FALSE)
		g_key_file_set_integer(obj->app_config, "app",			"x_pos", 640/2);

	if(g_key_file_has_key(obj->app_config, "app",				"y_pos", NULL) == FALSE)
		g_key_file_set_integer(obj->app_config, "app",			"y_pos", 480/2);

	if(g_key_file_has_key(obj->app_config, "app",				"width", NULL) == FALSE)
		g_key_file_set_integer(obj->app_config, "app",			"width", 640);

	if(g_key_file_has_key(obj->app_config, "app",				"height", NULL) == FALSE)
		g_key_file_set_integer(obj->app_config, "app",			"height", 480);

	if(g_key_file_has_key(obj->app_config, "app",				"maximize", NULL) == FALSE)
		g_key_file_set_boolean(obj->app_config, "app",			"maximize", FALSE);

	//##################################

	if(g_key_file_has_key(obj->app_config, "default_theme",		"background", NULL) == FALSE)
		g_key_file_set_string(obj->app_config, "default_theme",	"background", "#ffffff");

	if(g_key_file_has_key(obj->app_config, "default_theme",		"text", NULL) == FALSE)
		g_key_file_set_string(obj->app_config, "default_theme",	"text", "#000000");

	//##################################

	if(g_key_file_has_key(obj->app_config, "dark_theme",		"background", NULL) == FALSE)
		g_key_file_set_string(obj->app_config, "dark_theme",	"background", "#293134");

	if(g_key_file_has_key(obj->app_config, "dark_theme",		"text", NULL) == FALSE)
		g_key_file_set_string(obj->app_config, "dark_theme",	"text", "#e8e2b7");



	return 0;
}
