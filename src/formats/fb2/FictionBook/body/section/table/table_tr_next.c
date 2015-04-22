#include "table_chunks.h"

int parse_fb2_table_tr_is_next(xmlNode* node)
{
	g_return_val_if_fail(node != NULL, -1);

	node = node->next;

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "tr") == 0)
				return 1;
		}
		node = node->next;
	}
	return 0;
}
