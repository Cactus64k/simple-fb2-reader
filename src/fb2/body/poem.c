#include "../fb2_chunks.h"

int parse_poem(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);


	node = node->children;

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	while(node != NULL)
	{
		if(strcmp((char*)node->name, "title") == 0)
		{
			print_unsupported_tag("title");
		}
		else if(strcmp((char*)node->name, "epigraph") == 0)
		{
			print_unsupported_tag("epigraph");
		}
		else if(strcmp((char*)node->name, "stanza") == 0)
		{
			print_unsupported_tag("stanza");
		}
		else if(strcmp((char*)node->name, "text-author") == 0)
			parse_p(node, text_buff, text_buff_end);
		else if(strcmp((char*)node->name, "date") == 0)
		{
			print_unsupported_tag("table");
		}

		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	return 0;
}
