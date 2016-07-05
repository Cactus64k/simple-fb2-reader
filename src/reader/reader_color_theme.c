#include "reader_chunks.h"

int reader_set_color_theme(APP* app, const char* color_theme)
{
	GKeyFile* app_config		= app->app_config;

	GtkTextTagTable* tag_table	= gtk_text_buffer_get_tag_table(app->text_buff);
	GtkTextTag* default_tag		= gtk_text_tag_table_lookup(tag_table, "default_tag");
	GtkTextTag* code_tag		= gtk_text_tag_table_lookup(tag_table, "code_tag");

	char* background_color		= g_key_file_get_string(app_config, color_theme, "background", NULL);
	char* text_color			= g_key_file_get_string(app_config, color_theme, "text", NULL);
	char* selection_color		= g_key_file_get_string(app_config, color_theme, "selection", NULL);

	char* font_general			= g_key_file_get_string(app_config, color_theme, "font_general", NULL);
	char* font_monospace		= g_key_file_get_string(app_config, color_theme, "font_monospace", NULL);
	gint line_spacing			= g_key_file_get_integer(app_config, color_theme, "line_spacing", NULL);

	g_return_val_if_fail(background_color	!= NULL, EXIT_FAILURE);
	g_return_val_if_fail(text_color			!= NULL, EXIT_FAILURE);
	g_return_val_if_fail(selection_color	!= NULL, EXIT_FAILURE);

	g_return_val_if_fail(text_color			!= NULL, EXIT_FAILURE);
	g_return_val_if_fail(selection_color	!= NULL, EXIT_FAILURE);

	GdkRGBA color;
	gdk_rgba_parse(&color, background_color);
	gtk_widget_override_background_color(GTK_WIDGET(app->text_view), GTK_STATE_FLAG_NORMAL, &color);

	gdk_rgba_parse(&color, selection_color);
	gtk_widget_override_background_color(GTK_WIDGET(app->text_view), GTK_STATE_FLAG_SELECTED, &color);

	GValue str_value = G_VALUE_INIT;
	g_value_init(&str_value, G_TYPE_STRING);

	g_value_set_string(&str_value, text_color);
	g_object_set_property(G_OBJECT(default_tag),	"foreground", &str_value);

	g_value_set_string(&str_value, font_general);
	g_object_set_property(G_OBJECT(default_tag),	"family", &str_value);

	g_value_set_string(&str_value, font_monospace);
	g_object_set_property(G_OBJECT(code_tag),		"family", &str_value);

	GValue int_value = G_VALUE_INIT;
	g_value_init(&int_value, G_TYPE_INT);

	g_value_set_int(&int_value, line_spacing);
	g_object_set_property(G_OBJECT(default_tag),	"pixels-inside-wrap", &int_value);

	g_value_set_int(&int_value, line_spacing);
	g_object_set_property(G_OBJECT(default_tag),	"pixels-above-lines", &int_value);


	g_free(background_color);
	g_free(text_color);
	g_free(selection_color);

	g_free(font_general);
	g_free(font_monospace);

	g_value_unset(&str_value);
	g_value_unset(&int_value);

	return EXIT_SUCCESS;
}
