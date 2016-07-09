#include "../callbacks_chunk.h"

G_MODULE_EXPORT void color_theme_checkmenuitem_toggled_cb(GtkCheckMenuItem* checkmenuitem, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GKeyFile* app_config			= app->app_config;
	const char* menu_item_name		= gtk_widget_get_name(GTK_WIDGET(checkmenuitem));

	reader_set_color_theme(app, menu_item_name);

	g_key_file_set_string(app_config, "app", "color_theme", menu_item_name);
}

G_MODULE_EXPORT void color_theme_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GKeyFile* app_config			= app->app_config;
	GtkWidget* sub_menu				= gtk_menu_item_get_submenu(menuitem);

	GList* items_list				= gtk_container_get_children(GTK_CONTAINER(sub_menu));
	g_list_free_full(items_list, (GDestroyNotify)gtk_widget_destroy);

	g_return_if_fail(sub_menu != NULL);
	g_return_if_fail(app_config != NULL);

	gsize groups_size	= 0;
	char** groups		= g_key_file_get_groups(app_config, &groups_size);
	char* color_theme	= g_key_file_get_string(app_config, "app", "color_theme", NULL);
	if(color_theme == NULL)
		color_theme = g_strdup("default_theme");

	for(size_t i=0;groups_size > i; i++)
	{
		if(strcmp(groups[i], "app") != 0)
		{
			GtkWidget* item = gtk_check_menu_item_new_with_label(groups[i]);
			gtk_check_menu_item_set_draw_as_radio(GTK_CHECK_MENU_ITEM(item), TRUE);
			gtk_widget_set_name(GTK_WIDGET(item), groups[i]);

			if(strcmp(groups[i], color_theme) == 0)
				gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);

			g_signal_connect(item, "toggled", G_CALLBACK(color_theme_checkmenuitem_toggled_cb), app);

			gtk_menu_shell_append(GTK_MENU_SHELL(sub_menu), item);
			gtk_widget_show(item);
		}
	}
	g_free(color_theme);
	g_strfreev(groups);
}
