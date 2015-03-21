#include "../../../chunks.h"

void reader_color_dark_theme_checkmenuitem_toggled_cb(GtkCheckMenuItem* checkmenuitem, gpointer user_data)
{
	GtkTextView* text_view		= GLOBAL_FB2_READER.book_text_view.text_view;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	GKeyFile* app_config		= GLOBAL_FB2_READER.app_config;
	GtkTextTagTable* tag_table	= gtk_text_buffer_get_tag_table(text_buff);

	GtkTextTag* default_tag	= gtk_text_tag_table_lookup(tag_table, "default_tag");

	const char* color_theme = NULL;

	if(gtk_check_menu_item_get_active(checkmenuitem))
		color_theme = "dark_theme";
	else
		color_theme = "default_theme";

	char* background_color	= g_key_file_get_string(app_config, color_theme, "background", NULL);
	char* text_color		= g_key_file_get_string(app_config, color_theme, "text", NULL);
	char* selection_color	= g_key_file_get_string(app_config, color_theme, "selection", NULL);

	g_return_if_fail(background_color	!= NULL);
	g_return_if_fail(text_color			!= NULL);
	g_return_if_fail(selection_color	!= NULL);

	GValue value = G_VALUE_INIT;
	g_value_init(&value, G_TYPE_STRING);

	GdkRGBA color;
	gdk_rgba_parse(&color, background_color);
	gtk_widget_override_background_color(GTK_WIDGET(text_view), GTK_STATE_FLAG_NORMAL, &color);

	gdk_rgba_parse(&color, selection_color);
	gtk_widget_override_background_color(GTK_WIDGET(text_view), GTK_STATE_FLAG_SELECTED, &color);

	g_value_set_string(&value, text_color);
	g_object_set_property(G_OBJECT(default_tag), "foreground", &value);


	g_free(background_color);
	g_free(text_color);

	g_value_unset(&value);

}
