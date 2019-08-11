#include "reader_app.h"

int reader_app_gui(APP* app, GtkBuilder* builder)
{
	app->main_wnd					= GTK_WIDGET(				gtk_builder_get_object(builder, "main_wnd"));
	app->filechooserdialog			= GTK_FILE_CHOOSER_DIALOG(	gtk_builder_get_object(builder, "book_filechooserdialog"));
	app->navigation_dialog			= GTK_DIALOG(				gtk_builder_get_object(builder, "navigation_dialog"));
	app->about_dialog				= GTK_ABOUT_DIALOG(			gtk_builder_get_object(builder, "reader_aboutdialog"));
	app->sections_treeview			= GTK_TREE_VIEW(			gtk_builder_get_object(builder, "books_section_treeview"));

	app->text_buff					= GTK_TEXT_BUFFER(			gtk_builder_get_object(builder, "book_textbuff"));
	app->text_view					= GTK_TEXT_VIEW(			gtk_builder_get_object(builder, "book_textview"));
	app->text_scrolledwindow		= GTK_SCROLLED_WINDOW(		gtk_builder_get_object(builder, "book_scrolledwindow"));
	app->sections_treestore			= GTK_TREE_STORE(			gtk_builder_get_object(builder, "books_sections_treestore"));
	app->book_type					= BOOK_TYPE_NONE;


	assert(app->main_wnd				!= NULL);
	assert(app->filechooserdialog		!= NULL);
	assert(app->navigation_dialog		!= NULL);
	assert(app->about_dialog			!= NULL);
	assert(app->sections_treeview		!= NULL);

	assert(app->text_buff				!= NULL);
	assert(app->text_view				!= NULL);
	assert(app->text_scrolledwindow		!= NULL);
	assert(app->sections_treestore		!= NULL);

	gtk_about_dialog_set_version(app->about_dialog, PACKAGE_VERSION);

	gint main_wnd_x_pos				= g_key_file_get_integer(app->app_config, "app", "x_pos", NULL);
	gint main_wnd_y_pos				= g_key_file_get_integer(app->app_config, "app", "y_pos", NULL);
	gtk_window_move(GTK_WINDOW(app->main_wnd), main_wnd_x_pos, main_wnd_y_pos);

	gint main_wnd_width				= g_key_file_get_integer(app->app_config, "app", "width", NULL);
	gint main_wnd_height			= g_key_file_get_integer(app->app_config, "app", "height", NULL);
	gtk_window_resize(GTK_WINDOW(app->main_wnd), main_wnd_width, main_wnd_height);

	if(g_key_file_get_boolean(app->app_config, "app", "maximize", NULL) == TRUE)
		gtk_window_maximize(GTK_WINDOW(app->main_wnd));

	app->auto_scroll_period			= g_key_file_get_integer(app->app_config, "app", "auto_scroll_period", NULL);

	GdkDisplay* def_display			= gdk_display_get_default();
	app->cursor_link				= gdk_cursor_new_for_display(def_display, GDK_HAND2);
	app->cursor_watch				= gdk_cursor_new_for_display(def_display, GDK_HAND2);
	app->clipboard					= gtk_widget_get_clipboard(app->main_wnd, GDK_SELECTION_CLIPBOARD);

	gtk_widget_show_all(app->main_wnd);

	return EXIT_SUCCESS;
}

