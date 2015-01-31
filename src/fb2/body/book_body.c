#include "../fb2_chunks.h"

int parse_book_body(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	node = node->children;

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "section") == 0)
				parse_body_section(node, text_buff, text_buff_end);
			else if(strcmp((char*)node->name, "title") == 0)
				parse_title(node, text_buff, text_buff_end);
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_epigraph(node, text_buff, text_buff_end);
			else if(strcmp((char*)node->name, "image") == 0)
				parse_image(node, text_buff, text_buff_end);
		}
		node = node->next;
	}
	return 0;
}


int print_unsupported_tag(char* tag)
{
	fprintf(stderr, "Finde unsupported tag: %s\n", tag);
	return 0;
}
