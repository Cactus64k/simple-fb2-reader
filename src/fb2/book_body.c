#include "fb2_chunks.h"

int parse_body(xmlNode* parent_node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);


	xmlNode* node			= parent_node->children;
	size_t image_count		= 0;
	size_t section_count	= 0;

	//########################################################################################################

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "section") == 0)
			{
				parse_section(node, text_buff, text_buff_end);
				section_count++;
			}
			else if(strcmp((char*)node->name, "title") == 0)
				parse_title(node, text_buff, text_buff_end);
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_epigraph(node, text_buff, text_buff_end);
			else if(strcmp((char*)node->name, "image") == 0)
			{
				if(image_count == 0)
				{
					parse_image(node, text_buff, text_buff_end);
					image_count++;
				}
				else
					fputs("fb2 format error: more then one image in body tag\n", stderr);
			}
		}

		node = node->next;
	}

	if(section_count == 0)
		fputs("fb2 format error: no section in body tag\n", stderr);

	return 0;
}

int print_unsupported_tag(char* tag)
{
	fprintf(stderr, "Finde unsupported tag: %s\n", tag);
	return 0;
}
