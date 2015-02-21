#include "../chunks.h"

int main_wnd_init(GtkBuilder* builder, FB2_READER* obj)
{
	create_config_dir();
	init_main_reader_text_view(builder, obj);

	obj->main_wnd					= GTK_WIDGET(				gtk_builder_get_object(builder, "main_wnd"));
	obj->filechooserdialog			= GTK_FILE_CHOOSER_DIALOG(	gtk_builder_get_object(builder, "book_filechooserdialog"));
	obj->navigation_dialog			= GTK_DIALOG(				gtk_builder_get_object(builder, "navigation_dialog"));

	assert(obj->main_wnd			!= NULL);
	assert(obj->filechooserdialog	!= NULL);
	assert(obj->navigation_dialog	!= NULL);
	const char* conf_dir			= g_get_user_config_dir();
	assert(conf_dir != NULL);

	obj->app_config					= g_key_file_new();
	obj->app_config_path			= g_strdup_printf("%s/simple-fb2-reader/cfg", conf_dir);


	if(g_key_file_load_from_file(obj->app_config, obj->app_config_path, G_KEY_FILE_NONE, NULL) == FALSE)
	{
		g_key_file_set_string(obj->app_config, "app",				"color_cheme",		"white");
		g_key_file_set_boolean(obj->app_config, "app",				"open_last_book",	FALSE);
		g_key_file_set_string(obj->app_config, "app",				"last_book",		"");

	/*	g_key_file_set_double(obj->app_config, "default_tag",		"size_points",		15.f);
		g_key_file_set_string(obj->app_config, "default_tag",		"family",			"DejaVu");

		g_key_file_set_double(obj->app_config, "title_tag",			"size_points",		17.f);

		g_key_file_set_double(obj->app_config, "sub_tag",			"size_points",		8.f);
		g_key_file_set_int64(obj->app_config, "sub_tag",			"rise",				-5000);

		g_key_file_set_double(obj->app_config, "sup_tag",			"size_points",		8.f);
		g_key_file_set_int64(obj->app_config, "sup_tag",			"rise",				7000);

		g_key_file_set_string(obj->app_config, "code_tag",			"family",			"Mono");

		g_key_file_set_double(obj->app_config, "image_tag",			"size_points",		10.f);

		g_key_file_set_double(obj->app_config, "cite_tag",			"size_points",		15.f);

		g_key_file_set_double(obj->app_config, "text_author_tag",	"size_points",		12.f);*/
	}

	//create_fb2_tags(obj->text_buff);

	obj->binary_hash_table			= g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_object_unref);

	obj->link_cursor				= gdk_cursor_new(GDK_HAND2);
	obj->def_cursor					= gdk_cursor_new(GDK_ARROW);
	obj->clipboard					= gtk_clipboard_get(0);

	gtk_widget_show_all(obj->main_wnd);

	return 0;
}


