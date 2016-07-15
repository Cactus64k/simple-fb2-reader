#include "body_chunks.h"

int parse_fb2_image(APP* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GtkTextBuffer* text_buff		= obj->text_buff;
	GHashTable* book_img_table		= obj->book_img_table;

	parse_fb2_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_tag_mark		= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);
	char* href_attr					= (char*)xmlGetProp(parent_node, (xmlChar*)"href");
	char* title_attr				= (char*)xmlGetProp(parent_node, (xmlChar*)"title");

	if(href_attr != NULL)
	{
		if(*href_attr == '#') // local
		{
			GdkPixbuf* image		= g_hash_table_lookup(book_img_table, href_attr+1);
			if(image != NULL)
			{
				gtk_text_buffer_insert_pixbuf(text_buff, text_buff_end, image);
				gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

				if(title_attr != NULL)
					gtk_text_buffer_insert(text_buff, text_buff_end, title_attr, -1);
			}
			else
				g_warning("Image %s not found in table", href_attr+1);
		}
		else
			g_error("Not local links not supported");
	}

	xmlFree(href_attr);
	xmlFree(title_attr);

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag_by_name(text_buff, "image_tag", &start_tag_iter, text_buff_end);

	return EXIT_SUCCESS;
}
