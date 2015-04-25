#include "body_chunks.h"

int parse_fb2_image(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff		= obj->text_buff;
	GHashTable* binary_hash_table	= obj->binary_hash_table;

	parse_fb2_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_tag_mark		= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);


	const char* href_attr			= NULL;
	const char* title_attr			= NULL;

	parse_fb2_attribute(obj, parent_node, "href", &href_attr);
	parse_fb2_attribute(obj, parent_node, "title", &title_attr);

	if(href_attr != NULL)
	{
		if(*href_attr == '#') // local
		{
			href_attr++;

			GdkPixbuf* image		= g_hash_table_lookup(binary_hash_table, href_attr);
			if(image != NULL)
			{
				gtk_text_buffer_insert_pixbuf(text_buff, text_buff_end, image);
				gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

				if(title_attr != NULL)
					gtk_text_buffer_insert(text_buff, text_buff_end, title_attr, -1);
			}
			else
				fprintf(stderr, _C("Image %s not found in table\n"), href_attr);
		}
		else
			fputs(_C("Not local links not supported\n"), stderr);
	}

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag_by_name(text_buff, "image_tag", &start_tag_iter, text_buff_end);

	return 0;
}
