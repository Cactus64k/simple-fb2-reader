#include "../fb2_chunks.h"

int parse_body_section(xmlNode* parent_node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	xmlNode* node = parent_node->children;
	bool section_in_section = false;

	while(node != NULL)
	{
		if((node->type == XML_ELEMENT_NODE) && (strcmp((char*)node->name, "section") == 0))
		{
			section_in_section = true;
			break;
		}

		node = node->next;
	}

	if(section_in_section == true)
	{
		node = parent_node->children;

		while(node != NULL)
		{
			if(node->type == XML_ELEMENT_NODE)
			{
				if(strcmp((char*)node->name, "title") == 0)
					parse_title(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "epigraph") == 0)
					parse_epigraph(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "image") == 0)
					parse_image(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "annotation") == 0)
				{
					print_unsupported_tag("annotation");
				}
				else if(strcmp((char*)node->name, "section") == 0)
					parse_body_section(node, text_buff, text_buff_end);
			}

			node = node->next;
		}
	}
	else
	{
		node = parent_node->children;

		while(node != NULL)
		{
			if(node->type == XML_ELEMENT_NODE)
			{
				if(strcmp((char*)node->name, "p") == 0)
					parse_p(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "empty-line") == 0)		// пустая строка
					gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
				else if(strcmp((char*)node->name, "title") == 0)
					parse_title(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "epigraph") == 0)
					parse_epigraph(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "image") == 0)
					parse_image(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "poem") == 0)				// стихотворение
					parse_poem(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "subtitle") == 0)			// подзаголовок
					parse_subtitle(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "cite") == 0)				// цитата
					parse_cite(node, text_buff, text_buff_end);
				else if(strcmp((char*)node->name, "table") == 0)			// таблица
				{
					print_unsupported_tag("table");
				}
			}


			node = node->next;
		}
	}
	return 0;
}

