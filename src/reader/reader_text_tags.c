#include "../chunks.h"

int reader_create_text_tags(APP* app)
{
	GtkTextBuffer* text_buff	= app->text_buff;
	GKeyFile* app_config		= app->app_config;
	GError* error				= NULL;
	double font_scale			= g_key_file_get_double(app_config, "app", "font_scale", &error);
	reader_hndl_GError(app, &error);


	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "default_tag", 		"size-points",			15.f,
																"scale",				font_scale,
																"wrap_mode",			GTK_WRAP_WORD_CHAR, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "title_tag", 			"size-points",			19.f,
																"justification",		GTK_JUSTIFY_CENTER, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "strong_tag", 		"weight",				PANGO_WEIGHT_BOLD, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "sub_tag", 			"size-points",			8.f,
																"rise",					-PANGO_SCALE*7, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "sup_tag", 			"size-points",			8.f,
																"rise",					PANGO_SCALE*9, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "strikethrough_tag", 	"strikethrough",		TRUE, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "emphasis_tag", 		"style",				PANGO_STYLE_ITALIC, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "code_tag", 			"family",				"monospace",
																"wrap_mode",			GTK_WRAP_NONE, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "subtitle_tag", 		"justification",		GTK_JUSTIFY_CENTER, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "image_tag", 			"size-points",			10.f,
																"justification",		GTK_JUSTIFY_CENTER, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "cite_tag", 			"size-points",			15.f,
																"style",				PANGO_STYLE_ITALIC, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "text_author_tag", 	"size-points",			12.f,
																"justification",		GTK_JUSTIFY_RIGHT, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "epigraph_tag", 		"style",				PANGO_STYLE_ITALIC,
																"justification",		GTK_JUSTIFY_RIGHT, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "stanza_tag", 		"style",				PANGO_STYLE_ITALIC,
																"justification",		GTK_JUSTIFY_CENTER, NULL);
	//####################################################################################################################################
	gtk_text_buffer_create_tag(text_buff, "table_tag", 			"family",				"monospace",
																"pixels-above-lines",	0,
																//"justification",		GTK_JUSTIFY_CENTER,
																"wrap_mode",			GTK_WRAP_NONE, NULL);
	//####################################################################################################################################

	return EXIT_SUCCESS;
}
