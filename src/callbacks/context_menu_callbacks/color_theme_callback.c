#include "../callbacks_chunk.h"

void color_theme_checkmenuitem_toggled_cb(GtkCheckMenuItem* checkmenuitem, gpointer user_data)
{
	GKeyFile* app_config			= GLOBAL_FB2_READER.app_config;

	const char* menu_item_name = gtk_widget_get_name(GTK_WIDGET(checkmenuitem));

	reader_set_color_theme(&GLOBAL_FB2_READER, menu_item_name);

	g_key_file_set_string(app_config, "app", "color_theme", menu_item_name);
}


