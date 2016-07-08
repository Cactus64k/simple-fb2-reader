#include "../callbacks_chunk.h"

G_MODULE_EXPORT void book_textview_populate_popup_cb(GtkTextView* entry, GtkMenu* menu, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GList* items_list				= gtk_container_get_children(GTK_CONTAINER(menu));
	g_list_free_full(items_list, (GDestroyNotify)gtk_widget_destroy);

	GtkWidget* item;
	GtkWidget* sub_menu;

	item = gtk_menu_item_new_with_label(_C("Backward"));
	g_signal_connect(item, "activate", G_CALLBACK(backward_itemmenu_cb), app);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);
	//*************************************************************************************************

	item = gtk_menu_item_new_with_label(_C("Navigation"));
	g_signal_connect(item, "activate", G_CALLBACK(navigation_menuitem_activate_cb), app);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_menu_item_new_with_label(_C("Find"));
	g_signal_connect(item, "activate", G_CALLBACK(search_menuitem_activate_cb), app);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);
	//*************************************************************************************************

	item = gtk_menu_item_new_with_label(_C("Auto scrolling"));
	sub_menu = gtk_menu_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	g_signal_connect(item, "activate", G_CALLBACK(auto_scroll_activate_cb), app);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), sub_menu);
	gtk_widget_show(item);

	item = gtk_menu_item_new_with_label(_C("Color Theme"));
	sub_menu = gtk_menu_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	g_signal_connect(item, "activate", G_CALLBACK(color_theme_activate_cb), app);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), sub_menu);
	gtk_widget_show(item);

	item = gtk_menu_item_new_with_label(_C("About"));
	g_signal_connect(item, "activate", G_CALLBACK(about_menuitem_activate_cb), app);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_menu_item_new_with_label(_C("Open Book"));
	g_signal_connect(item, "activate", G_CALLBACK(open_file_menuitem_activate_cb), app);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_menu_item_new_with_label(_C("Exit"));
	g_signal_connect(item, "activate", G_CALLBACK(gtk_main_quit), app);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);


}

