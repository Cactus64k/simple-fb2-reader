#include "../../chunks.h"

void reader_forger_books_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkMessageDialog* forget_book_dialog	= GLOBAL_FB2_READER.forget_books_dialog;

	if(gtk_dialog_run(GTK_DIALOG(forget_book_dialog)) == 2)
	{
		gtk_widget_hide(GTK_WIDGET(forget_book_dialog));



		//g_free(file_path);
	}

	gtk_widget_hide(GTK_WIDGET(forget_book_dialog));

}


