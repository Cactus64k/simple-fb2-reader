#include "section_chunks.h"

int parse_image_inline(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff		= obj->text_buff;
	GHashTable* binary_hash_table	= obj->binary_hash_table;
	xmlAttr* properties				= parent_node->properties;

	parse_id_attribute(obj, parent_node, text_buff_end);

	GdkPixbuf* image				= NULL;

	while(properties != NULL)
	{
		if(properties->type == XML_ATTRIBUTE_NODE)
		{
			if(strcmp((char*)properties->name, "href") == 0)
			{
				char* image_id = (char*)(properties->children->content);
				if(*image_id == '#') // local
				{
					image_id++;

					image = g_hash_table_lookup(binary_hash_table, image_id);
					if(image == NULL)
						fprintf(stderr, _C("Image %s not found in table\n"), image_id);
				}
				else
					fputs(_C("Not local links not supported\n"), stderr);

				break;
			}
		}

		properties = properties->next;
	}

	if(image != NULL)
		gtk_text_buffer_insert_pixbuf(text_buff, text_buff_end, image);

	return 0;
}

