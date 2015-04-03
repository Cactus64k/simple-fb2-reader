#include "../callbacks_chunk.h"

void about_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkAboutDialog* about_dialog	= GLOBAL_FB2_READER.about_dialog;
	gtk_dialog_run(GTK_DIALOG(about_dialog));
	gtk_widget_hide(GTK_WIDGET(about_dialog));

}
