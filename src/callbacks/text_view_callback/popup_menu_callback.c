#include "../callbacks_chunk.h"

void backward_itemmenu_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	FB2_READER_BOOK_VIEW* book_view	= (FB2_READER_BOOK_VIEW*)user_data;
	GtkTextView* text_view			= book_view->text_view;
	GList* link_jump_list			= book_view->link_jump_list;

	if(link_jump_list != NULL)
	{
		GtkTextMark* mark = GTK_TEXT_MARK(link_jump_list->data);
		gtk_text_view_scroll_to_mark(text_view, mark, 0.0, TRUE, 0.0, 0.0);

		book_view->link_jump_list = g_list_remove(link_jump_list, mark);
	}
}


void book_textview_populate_popup_cb(GtkTextView* entry, GtkMenu* menu, gpointer user_data)
{
	FB2_READER_BOOK_VIEW* book_view	= &(GLOBAL_FB2_READER.book_text_view);
	GKeyFile* app_config			= GLOBAL_FB2_READER.app_config;

	GList* items_list				= gtk_container_get_children(GTK_CONTAINER(menu));
	g_list_free_full(items_list, (GDestroyNotify)gtk_widget_destroy);

	GtkWidget* item;
	GtkWidget* icon;
	GtkWidget* sub_menu;

	item = gtk_image_menu_item_new_with_label(_C("Backward"));
	icon = gtk_image_new_from_icon_name("go-previous", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(backward_itemmenu_cb), book_view);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);
	//*************************************************************************************************

	item = gtk_image_menu_item_new_with_label(_C("Navigation"));
	icon = gtk_image_new_from_icon_name("gtk-index", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(navigation_imagemenuitem_activate_cb), book_view);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_image_menu_item_new_with_label(_C("Find"));
	icon = gtk_image_new_from_icon_name("gtk-find", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(search_imagemenuitem_activate_cb), book_view);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_image_menu_item_new_with_label(_C("Change Encode"));
	icon = gtk_image_new_from_icon_name("gtk-convert", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(encode_imagemenuitem_activate_cb), book_view);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);
	//*************************************************************************************************

	sub_menu = gtk_menu_new();
	item = gtk_image_menu_item_new_with_label(_C("Color Theme"));
	icon = gtk_image_new_from_icon_name("gtk-select-color", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), sub_menu);
	gtk_widget_show(item);

	char** groups		= g_key_file_get_groups(app_config, NULL);
	char* color_theme	= g_key_file_get_string(app_config, "app", "color_theme", NULL);
	for(size_t i=0;groups[i] != NULL; i++)
	{
		if(strcmp(groups[i], "app") != 0)
		{
			item = gtk_check_menu_item_new_with_label(groups[i]);
			gtk_check_menu_item_set_draw_as_radio(GTK_CHECK_MENU_ITEM(item), TRUE);
			gtk_widget_set_name(GTK_WIDGET(item), groups[i]);

			if(strcmp(groups[i], color_theme) == 0)
				gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);

			g_signal_connect(item, "toggled", G_CALLBACK(color_theme_checkmenuitem_toggled_cb), book_view); // FIXME
			gtk_menu_shell_append(GTK_MENU_SHELL(sub_menu), item);
			gtk_widget_show(item);
		}
	}
	g_free(color_theme);
	g_strfreev(groups);


	item = gtk_image_menu_item_new_with_label(_C("Forget All Books"));
	icon = gtk_image_new_from_icon_name("gtk-delete", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(forger_books_imagemenuitem_activate_cb), book_view);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_image_menu_item_new_with_label(_C("About"));
	icon = gtk_image_new_from_icon_name("gtk-about", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(about_imagemenuitem_activate_cb), book_view);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);
	//*************************************************************************************************

	item = gtk_image_menu_item_new_with_label(_C("Open Book"));
	icon = gtk_image_new_from_icon_name("gtk-open", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(open_file_imagemenuitem_activate_cb), book_view);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_image_menu_item_new_with_label(_C("Exit"));
	icon = gtk_image_new_from_icon_name("gtk-quit", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(gtk_main_quit), book_view);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);


}

