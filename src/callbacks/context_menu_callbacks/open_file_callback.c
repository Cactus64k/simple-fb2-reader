#include "../callbacks_chunk.h"

void open_file_imagemenuitem_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	GtkFileChooserDialog* file_open_dialog	= GLOBAL_FB2_READER.filechooserdialog;
	char* book_path							= GLOBAL_FB2_READER.book_text_view.path;

	gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_open_dialog), book_path);

	if(gtk_dialog_run(GTK_DIALOG(file_open_dialog)) == 2)
	{

		char* file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_open_dialog));
		reader_close_book();
		reader_open_book(file_path);

		//g_free(file_path);
	}

	gtk_widget_hide(GTK_WIDGET(file_open_dialog));
}

void book_filechooserdialog_file_activated_cb(GtkFileChooser* chooser, gpointer user_data)
{
	GtkFileChooserDialog* file_open_dialog	= GLOBAL_FB2_READER.filechooserdialog;
	char* book_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_open_dialog));

	BOOK_TYPE book_type = reader_get_book_type(book_path);
	if(book_type != BOOK_TYPE_NONE)
	{
		gtk_widget_hide(GTK_WIDGET(file_open_dialog));

		reader_close_book();
		reader_open_book(book_path);
	}
	else
		g_free(book_path);
}
