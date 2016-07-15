#include "../callbacks_chunk.h"

G_MODULE_EXPORT void close_book_menuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	APP* app = (APP*)user_data;

	if(app->book_type != BOOK_TYPE_NONE)
	{
		reader_close_book(app);
		reader_start_screen(app);
	}
}
