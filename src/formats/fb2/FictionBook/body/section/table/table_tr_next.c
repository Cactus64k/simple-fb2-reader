#include "table_chunks.h"

gboolean parse_fb2_table_tr_is_next(xmlNode* node)
{
	g_return_val_if_fail(node != NULL, FALSE);

	node = node->next;

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "tr") == 0)
				return TRUE;
		}
		node = node->next;
	}
	return FALSE;
}
