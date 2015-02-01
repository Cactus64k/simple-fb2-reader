#include "../fb2_chunks.h"

int parse_image(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	GHashTable* binary_hash_table	= GLOBAL_FB2_READER.binary_hash_table;
	GtkTextTag* image_tag			= GLOBAL_FB2_READER.image_tag;
	xmlAttr* properties				= node->properties;
	GdkPixbuf* image				= NULL;
	GtkTextMark* start_tag_mark		= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, true);
	char* image_title				= NULL;


	while(properties != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)properties->name, "href") == 0)
			{
				char* image_id = (char*)(properties->children->content+1);
				image = g_hash_table_lookup(binary_hash_table, image_id);
				if(image == NULL)
					fprintf(stderr, "image %s not fount in table\n", image_id);
				break;
			}
			else if(strcmp((char*)properties->name, "title") == 0)
				image_title = (char*)properties->children->content;
		}

		properties = properties->next;
	}

	if(image != NULL)
		gtk_text_buffer_insert_pixbuf(text_buff, text_buff_end, image);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
	if(image_title != NULL)
		gtk_text_buffer_insert(text_buff, text_buff_end, image_title, -1);

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag(text_buff, image_tag, &start_tag_iter, text_buff_end);

	return 0;
}
