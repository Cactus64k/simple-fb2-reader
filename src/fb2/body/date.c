#include "../fb2_chunks.h"

int parse_date(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	xmlAttr* properties = node->properties;

	while(properties != NULL)
	{
		if((properties->type == XML_ATTRIBUTE_NODE) && (strcmp((char*)properties->name, "value") == 0))
		{
			char* date = (char*)properties->children->content;
			gtk_text_buffer_insert(text_buff, text_buff_end, date, -1);
			break;
		}

		properties = properties->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);



	return 0;
}
