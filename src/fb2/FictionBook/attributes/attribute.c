#include "../FictionBook_chunks.h"

int parse_attribute(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, const char* attribute_name, const char** value)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(attribute_name != NULL, -2);
	g_return_val_if_fail(value != NULL, -2);

	xmlAttr* properties				= parent_node->properties;

	while(properties != NULL)
	{
		if(properties->type == XML_ATTRIBUTE_NODE)
		{
			if(strcmp((char*)properties->name, attribute_name) == 0)
			{
				*value = (char*)properties->children->content;
				break;
			}
		}

		properties = properties->next;
	}

	return 0;
}
