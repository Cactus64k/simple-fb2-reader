#include "../callbacks_chunk.h"

G_MODULE_EXPORT void auto_scroll_enable_checkmenuitem_toggled_cb(GtkCheckMenuItem* checkmenuitem, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	if(app->book_type != BOOK_TYPE_NONE)
	{
		app->auto_scroll			= TRUE;
		double period			= app->auto_scroll_period;
		g_timeout_add(period, auto_scroll_update, app);
	}

}

G_MODULE_EXPORT void auto_scroll_disable_checkmenuitem_toggled_cb(GtkCheckMenuItem* checkmenuitem, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	app->auto_scroll				= FALSE;
}

G_MODULE_EXPORT void auto_scroll_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GKeyFile* app_config			= app->app_config;
	GtkWidget* sub_menu			= gtk_menu_item_get_submenu(menuitem);

	GList* items_list				= gtk_container_get_children(GTK_CONTAINER(sub_menu));
	g_list_free_full(items_list, (GDestroyNotify)gtk_widget_destroy);

	g_return_if_fail(sub_menu != NULL);
	g_return_if_fail(app_config != NULL);

	GtkWidget* enable_item = gtk_check_menu_item_new_with_label(_C("Enable"));
	gtk_check_menu_item_set_draw_as_radio(GTK_CHECK_MENU_ITEM(enable_item), TRUE);
	gtk_menu_shell_append(GTK_MENU_SHELL(sub_menu), enable_item);
	gtk_widget_show(enable_item);

	GtkWidget* disable_item = gtk_check_menu_item_new_with_label(_C("Disable"));
	gtk_check_menu_item_set_draw_as_radio(GTK_CHECK_MENU_ITEM(disable_item), TRUE);
	gtk_menu_shell_append(GTK_MENU_SHELL(sub_menu), disable_item);
	gtk_widget_show(disable_item);

	if(app->auto_scroll == TRUE)
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(enable_item), TRUE);
	else
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(disable_item), TRUE);

	g_signal_connect(disable_item, "toggled", G_CALLBACK(auto_scroll_disable_checkmenuitem_toggled_cb), app);
	g_signal_connect(enable_item, "toggled", G_CALLBACK(auto_scroll_enable_checkmenuitem_toggled_cb), app);
}
