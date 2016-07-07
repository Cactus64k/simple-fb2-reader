#include "attributes_chunks.h"

int parse_fb2_attribute(APP* app, xmlNode* parent_node, const char* attribute_name, const char** value)
{
	g_return_val_if_fail(parent_node	!= NULL, EXIT_FAILURE);
	g_return_val_if_fail(attribute_name	!= NULL, EXIT_FAILURE);
	g_return_val_if_fail(value			!= NULL, EXIT_FAILURE);

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


	return EXIT_SUCCESS;
}
