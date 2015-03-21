#include "../../../chunks.h"

void file_open_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkFileChooserDialog* file_open_dialog	= GLOBAL_FB2_READER.filechooserdialog;

	if(gtk_dialog_run(GTK_DIALOG(file_open_dialog)) == 2)
	{
		gtk_widget_hide(GTK_WIDGET(file_open_dialog));

		char* file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_open_dialog));
		if(reader_close_book() != 1)
			reader_open_book(file_path);

		//g_free(file_path);
	}

	gtk_widget_hide(GTK_WIDGET(file_open_dialog));
}
