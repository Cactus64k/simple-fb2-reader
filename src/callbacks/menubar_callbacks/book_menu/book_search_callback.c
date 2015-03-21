#include "../../../chunks.h"

void book_search_imagemenuitem_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	GtkWidget* search_window	= GLOBAL_SEARCH_WND.search_wnd;
	GtkEntry* search_entry		= GLOBAL_SEARCH_WND.search_query_entry;
	gtk_widget_show(search_window);
	gtk_widget_grab_focus(GTK_WIDGET(search_entry));
}
