#include "../fb2_chunks.h"

int parse_id_attribute(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff_end != NULL);

	GHashTable* links_hash_table	= obj->links_hash_table;
	//GtkTextBuffer* text_buff		= obj->text_buff;
	xmlAttr* properties				= parent_node->properties;

	while(properties != NULL)
	{
		if(properties->type == XML_ATTRIBUTE_NODE)
		{
			if(strcmp((char*)properties->name, "id") == 0)
			{
				char* id				= g_strdup((char*)properties->children->content);
				gint pos 				= gtk_text_iter_get_line(text_buff_end);

				g_hash_table_insert(links_hash_table, id, GINT_TO_POINTER(pos));
				break;
			}
		}

		properties = properties->next;
	}

	return 0;
}
