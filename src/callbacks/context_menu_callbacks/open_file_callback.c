#include "../callbacks_chunk.h"

G_MODULE_EXPORT void open_file_menuitem_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	APP* app								= (APP*)user_data;
	GtkFileChooserDialog* file_open_dialog	= app->filechooserdialog;

	if(gtk_dialog_run(GTK_DIALOG(file_open_dialog)) == 2)
	{
		gtk_widget_hide(GTK_WIDGET(file_open_dialog));

		char* file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_open_dialog));
		reader_close_book(app);
		reader_open_book(app, file_path);
		g_free(file_path);
	}

	gtk_widget_hide(GTK_WIDGET(file_open_dialog));
}

G_MODULE_EXPORT void book_filechooserdialog_file_activated_cb(GtkFileChooser* chooser, gpointer user_data)
{
	APP* app								= (APP*)user_data;
	GtkFileChooserDialog* file_open_dialog	= app->filechooserdialog;
	char* book_path						= gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_open_dialog));

	BOOK_TYPE book_type					= reader_get_book_type(book_path);
	if(book_type != BOOK_TYPE_NONE)
	{
		gtk_widget_hide(GTK_WIDGET(file_open_dialog));

		reader_close_book(app);
		reader_open_book(app, book_path);
		g_free(book_path);

	}
	else
		g_free(book_path);
}
