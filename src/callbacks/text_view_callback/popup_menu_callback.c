#include "../callbacks_chunk.h"

void book_textview_populate_popup_cb(GtkTextView* entry, GtkMenu* menu, gpointer user_data)
{
	FB2_READER_BOOK_VIEW* book_view	= &(GLOBAL_FB2_READER.book_text_view);

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
	g_signal_connect(item, "activate", G_CALLBACK(navigation_imagemenuitem_activate_cb), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_image_menu_item_new_with_label(_C("Find"));
	icon = gtk_image_new_from_icon_name("gtk-find", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(search_imagemenuitem_activate_cb), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_image_menu_item_new_with_label(_C("Change Encoding"));
	icon = gtk_image_new_from_icon_name("gtk-convert", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(encoding_imagemenuitem_activate_cb), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);
	//*************************************************************************************************

	item = gtk_image_menu_item_new_with_label(_C("Color Theme"));
	icon = gtk_image_new_from_icon_name("gtk-select-color", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	sub_menu = gtk_menu_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	g_signal_connect(item, "activate", G_CALLBACK(color_theme_activate_cb), NULL);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), sub_menu);
	gtk_widget_show(item);

	item = gtk_image_menu_item_new_with_label(_C("Forget All Books"));
	icon = gtk_image_new_from_icon_name("gtk-delete", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(forger_books_imagemenuitem_activate_cb), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_image_menu_item_new_with_label(_C("About"));
	icon = gtk_image_new_from_icon_name("gtk-about", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(about_imagemenuitem_activate_cb), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);
	//*************************************************************************************************

	item = gtk_image_menu_item_new_with_label(_C("Open Book"));
	icon = gtk_image_new_from_icon_name("gtk-open", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(open_file_imagemenuitem_activate_cb), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);

	item = gtk_image_menu_item_new_with_label(_C("Exit"));
	icon = gtk_image_new_from_icon_name("gtk-quit", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
	g_signal_connect(item, "activate", G_CALLBACK(gtk_main_quit), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);


}

