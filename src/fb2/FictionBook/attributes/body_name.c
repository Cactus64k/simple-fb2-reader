#include "../FictionBook_chunks.h"

int parse_body_name_attribute(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	xmlAttr* properties				= parent_node->properties;

	while(properties != NULL)
	{
		if(properties->type == XML_ATTRIBUTE_NODE)
		{
			if(strcmp((char*)properties->name, "name") == 0)
			{
				char* properties_value = (char*)(properties->children->content);
				if((strcmp(properties_value, "notes") == 0) || (strcmp(properties_value, "comments") == 0))
					return 1;
			}
		}

		properties = properties->next;
	}

	return 0;
}
