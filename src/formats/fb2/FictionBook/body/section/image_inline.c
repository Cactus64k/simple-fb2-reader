#include "section_chunks.h"

int parse_fb2_image_inline(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GtkTextBuffer* text_buff		= app->text_buff;
	GHashTable* book_img_table		= app->book_img_table;

	parse_fb2_id_attribute(app, parent_node, text_buff_end);

	char* href_attr			= (char*)xmlGetProp(parent_node, (xmlChar*)"href");

	if(href_attr != NULL)
	{
		if(*href_attr == '#') // local
		{
			GdkPixbuf* image		= g_hash_table_lookup(book_img_table, href_attr+1);
			if(image != NULL)
				gtk_text_buffer_insert_pixbuf(text_buff, text_buff_end, image);
			else
				g_warning("Image %s not found in table", href_attr+1);
		}
		else
			g_log(NULL, G_LOG_LEVEL_ERROR, "Not local links not supported");

	}

	xmlFree(href_attr);

	return EXIT_SUCCESS;
}

