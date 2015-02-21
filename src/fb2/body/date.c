#include "../fb2_chunks.h"

int parse_date(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff_end != NULL);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	xmlAttr* properties	= node->properties;

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
