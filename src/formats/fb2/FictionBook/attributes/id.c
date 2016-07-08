#include "attributes_chunks.h"

int parse_fb2_id_attribute(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GHashTable* links_hash_table	= app->links_hash_table;
	const char* id_attr				= NULL;

	parse_fb2_attribute(app, parent_node, "id", &id_attr);
	if(id_attr != NULL)
	{
		gint pos		= gtk_text_iter_get_line(text_buff_end);

		if(g_hash_table_contains(links_hash_table, id_attr) == FALSE)
		{
			char* id	= g_strdup(id_attr);
			g_hash_table_insert(links_hash_table, id, GINT_TO_POINTER(pos));
		}
		else
			g_warning("Id %s already exist in table", id_attr);
	}



	return EXIT_SUCCESS;
}
