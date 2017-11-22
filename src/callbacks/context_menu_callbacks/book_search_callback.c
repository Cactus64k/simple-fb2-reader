#include "../callbacks_chunk.h"

G_MODULE_EXPORT void search_menuitem_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GtkWidget* search_window		= app->search_window.search_wnd;
	GtkEntry* search_entry		= app->search_window.search_query_entry;
	BOOK_TYPE book_type			= app->book_type;

	if(book_type != BOOK_TYPE_NONE)
	{
		gtk_widget_show(search_window);
		gtk_widget_grab_focus(GTK_WIDGET(search_entry));
	}
}
