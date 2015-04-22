#include "table_chunks.h"

#define MAX_CELL_LENGTH 25

int parse_fb2_table_get_size(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, glong** cells_table, size_t* cells_count)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(cells_table != NULL, -2);
	g_return_val_if_fail(cells_count != NULL, -3);

	xmlNode* node = parent_node->children;

	*cells_count = 0;

	size_t table_alloc_size		= 8;
	*cells_table				= calloc(table_alloc_size, sizeof(glong));

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "tr") == 0)
			{
				xmlNode* td_node = node->children;
				size_t cell_index = 0;

				while(td_node != NULL)
				{
					if(td_node->type == XML_ELEMENT_NODE)
					{
						if((strcmp((char*)td_node->name, "td") == 0) || (strcmp((char*)td_node->name, "th") == 0))
						{
							if(cell_index >= table_alloc_size)
							{
								*cells_table = realloc(*cells_table, (table_alloc_size*2) * sizeof(glong));
								memset(*cells_table + table_alloc_size, 0, table_alloc_size * sizeof(glong));
								table_alloc_size = table_alloc_size*2;
							}

							glong cell_length = 0;
							parse_fb2_p_get_length(td_node, &cell_length);

							cell_length = MIN(cell_length, MAX_CELL_LENGTH);

							(*cells_table)[cell_index] = MAX((*cells_table)[cell_index], cell_length);

							cell_index++;
						}
					}

					td_node = td_node->next;
				}

				*cells_count = MAX(*cells_count, cell_index);

			}
		}
		node = node->next;
	}

	return 0;
}
