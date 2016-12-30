#include "attributes_chunks.h"

int parse_fb2_id_attribute(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GHashTable* book_id_table		= app->book_id_table;
	char* id_attr					= (char*)xmlGetProp(parent_node, (xmlChar*)"id");

	if(id_attr != NULL)
	{
		gint pos	= gtk_text_iter_get_line(text_buff_end);

		if(g_hash_table_contains(book_id_table, id_attr) == FALSE)
		{
			char* id	= g_strdup(id_attr);
			g_hash_table_insert(book_id_table, id, GINT_TO_POINTER(pos));
		}
		else
			g_log(NULL, G_LOG_LEVEL_WARNING, "Id %s already exist in table", id_attr);
	}

	xmlFree(id_attr);



	return EXIT_SUCCESS;
}
