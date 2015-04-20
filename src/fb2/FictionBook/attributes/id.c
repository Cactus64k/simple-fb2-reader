#include "../FictionBook_chunks.h"

int parse_id_attribute(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GHashTable* links_hash_table	= obj->links_hash_table;
	const char* id_attr				= NULL;

	parse_attribute(obj, parent_node, "id", &id_attr);
	if(id_attr != NULL)
	{
		gint pos		= gtk_text_iter_get_line(text_buff_end);

		if(g_hash_table_contains(links_hash_table, id_attr) == FALSE)
		{
			char* id	= g_strdup(id_attr);
			g_hash_table_insert(links_hash_table, id, GINT_TO_POINTER(pos));
		}
		else
			fprintf(stderr, _C("ERROR: id %s already exist in table\n"), id_attr);

	}



	return 0;
}
