#include "reader_chunks.h"

int reader_set_color_theme(FB2_READER* obj, const char* color_theme)
{
	FB2_READER_BOOK_VIEW* book_view = &(obj->book_text_view);

	GtkTextTagTable* tag_table	= gtk_text_buffer_get_tag_table(book_view->text_buff);
	GtkTextTag* default_tag	= gtk_text_tag_table_lookup(tag_table, "default_tag");

	char* background_color	= g_key_file_get_string(obj->app_config, color_theme, "background", NULL);
	char* text_color		= g_key_file_get_string(obj->app_config, color_theme, "text", NULL);
	char* selection_color	= g_key_file_get_string(obj->app_config, color_theme, "selection", NULL);

	g_return_val_if_fail(background_color	!= NULL, -1);
	g_return_val_if_fail(text_color			!= NULL, -1);
	g_return_val_if_fail(selection_color	!= NULL, -1);

	GValue value = G_VALUE_INIT;
	g_value_init(&value, G_TYPE_STRING);

	GdkRGBA color;
	gdk_rgba_parse(&color, background_color);
	gtk_widget_override_background_color(GTK_WIDGET(book_view->text_view), GTK_STATE_FLAG_NORMAL, &color);

	gdk_rgba_parse(&color, selection_color);
	gtk_widget_override_background_color(GTK_WIDGET(book_view->text_view), GTK_STATE_FLAG_SELECTED, &color);

	g_value_set_string(&value, text_color);
	g_object_set_property(G_OBJECT(default_tag), "foreground", &value);


	g_free(background_color);
	g_free(text_color);

	g_value_unset(&value);

	return 0;
}
