#include "section_chunks.h"

int parse_fb2_image_inline(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GtkTextBuffer* text_buff		= app->text_buff;
	GHashTable* binary_hash_table	= app->binary_hash_table;

	parse_fb2_id_attribute(app, parent_node, text_buff_end);

	const char* href_attr			= NULL;

	parse_fb2_attribute(app, parent_node, "href", &href_attr);

	if(href_attr != NULL)
	{
		if(*href_attr == '#') // local
		{
			href_attr++;

			GdkPixbuf* image		= g_hash_table_lookup(binary_hash_table, href_attr);
			if(image != NULL)
				gtk_text_buffer_insert_pixbuf(text_buff, text_buff_end, image);
			else
				g_warning("Image %s not found in table", href_attr);
		}
		else
			g_error("Not local links not supported");

	}

	return EXIT_SUCCESS;
}

