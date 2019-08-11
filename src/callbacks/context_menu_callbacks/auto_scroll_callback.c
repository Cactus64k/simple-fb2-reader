#include "../callbacks_chunk.h"

G_MODULE_EXPORT void auto_scroll_toggled_cb(GtkCheckMenuItem* menuitem, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GKeyFile* app_config			= app->app_config;
	GtkWidget* sub_menu				= gtk_menu_item_get_submenu(menuitem);

	if((gtk_check_menu_item_get_active(menuitem) == TRUE) && (app->book_type != BOOK_TYPE_NONE))
	{
		app->auto_scroll		= TRUE;
		int period				= app->auto_scroll_period;
		g_timeout_add(period, auto_scroll_update, app);
	}
	else
		app->auto_scroll = FALSE;

}
