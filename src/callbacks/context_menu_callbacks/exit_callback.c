#include "../callbacks_chunk.h"

G_MODULE_EXPORT void exit_menuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	APP* app	= (APP*)user_data;
	reader_scroll_save(app);
	reader_close_book(app);
	reader_close_app(app);
	gtk_main_quit();
}
