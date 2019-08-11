#include "reader_chunks.h"

int reader_set_color_theme(APP* app)
{
	g_return_val_if_fail(app, EXIT_FAILURE);


	GKeyFile* app_config		= app->app_config;
	char* app_css_path			= app->app_css_path;

	GtkCssProvider* css_provider	= gtk_css_provider_new();
	if(gtk_css_provider_load_from_path(css_provider, app_css_path, NULL) == TRUE)
	{
		GdkScreen* screen_default = gdk_screen_get_default();
		gtk_style_context_add_provider_for_screen(screen_default, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

		GtkStyleContext* style_context = gtk_widget_get_style_context(GTK_WIDGET(app->text_view));
		gtk_style_context_add_provider(style_context, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	}

	g_object_unref(css_provider);

	GValue int_value = G_VALUE_INIT;
	g_value_init(&int_value, G_TYPE_INT);

	GtkTextTagTable* tag_table	= gtk_text_buffer_get_tag_table(app->text_buff);
	GtkTextTag* default_tag		= gtk_text_tag_table_lookup(tag_table, "default_tag");

	int pixels_inside_wrap = g_key_file_get_integer(app_config, "app", "pixels_inside_wrap", NULL);
	g_value_set_int(&int_value, pixels_inside_wrap);
	g_object_set_property(G_OBJECT(default_tag),	"pixels-inside-wrap", &int_value);

	int  pixels_above_lines = g_key_file_get_integer(app_config, "app", "pixels_above_lines", NULL);
	g_value_set_int(&int_value, pixels_above_lines);
	g_object_set_property(G_OBJECT(default_tag),	"pixels-above-lines", &int_value);



//	g_value_unset(&str_value);
	g_value_unset(&int_value);

	return EXIT_SUCCESS;
}
