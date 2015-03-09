#include "../fb2_chunks.h"

int parse_id_attribute(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GHashTable* links_hash_table	= obj->links_hash_table;
	xmlAttr* properties				= parent_node->properties;

	while(properties != NULL)
	{
		if(properties->type == XML_ATTRIBUTE_NODE)
		{
			if(strcmp((char*)properties->name, "id") == 0)
			{
				char* id				= g_strdup((char*)properties->children->content);
				gint pos 				= gtk_text_iter_get_line(text_buff_end);

				if(g_hash_table_contains(links_hash_table, id) == FALSE)
				{
					g_hash_table_insert(links_hash_table, id, GINT_TO_POINTER(pos));
					break;
				}
				else
					fprintf(stderr, _C("ERROR: id %s already exist in table\n"), id);
			}
		}

		properties = properties->next;
	}

	return 0;
}
