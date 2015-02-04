#include "../fb2_chunks.h"

int parse_section(xmlNode* parent_node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	bool section_in_section = false;

	xmlNode* node					= parent_node->children;
	xmlAttr* properties				= parent_node->properties;
	GHashTable* links_hash_table	= GLOBAL_FB2_READER.binary_hash_table;

	//########################################################################################################

	while(properties != NULL)
	{
		if(properties->type == XML_ATTRIBUTE_NODE)
		{
			if(strcmp((char*)properties->name, "id") == 0)
			{
				char* link_id = (char*)properties->children->content;
				GtkTextMark* mark = gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, true);

				g_hash_table_insert(links_hash_table, link_id, mark);
				break;
			}
		}

		properties = properties->next;
	}

	//########################################################################################################

	while(node != NULL)
	{
		if((node->type == XML_ELEMENT_NODE) && (strcmp((char*)node->name, "section") == 0))
		{
			section_in_section = true;
			break;
		}

		node = node->next;
	}

	//########################################################################################################

	node				= parent_node->children;
	size_t title_count	= 0;
	size_t image_count	= 0;
	size_t anntn_count	= 0;
	size_t textt_count	= 0;

	if(section_in_section == true)
	{
		while(node != NULL)
		{
			if(node->type == XML_ELEMENT_NODE)
			{
				if(strcmp((char*)node->name, "title") == 0)
				{
					if(title_count == 0)
					{
						parse_title(node, text_buff, text_buff_end);
						title_count++;
					}
					else
						fputs("fb2 format error: more then one title in section tag\n", stderr);
				}
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
						fputs("fb2 format error: more then one image in section tag\n", stderr);
				}
				else if(strcmp((char*)node->name, "annotation") == 0)
				{
					if(anntn_count == 0)
					{
						print_unsupported_tag("annotation");
						anntn_count++;
					}
					else
						fputs("fb2 format error: more then one annotation in section tag\n", stderr);

				}
				else if(strcmp((char*)node->name, "section") == 0)
					parse_section(node, text_buff, text_buff_end);
			}

			node = node->next;
		}
	}
	else
	{
		while(node != NULL)
		{
			if(node->type == XML_ELEMENT_NODE)
			{
				if(strcmp((char*)node->name, "p") == 0)
				{
					parse_p(node, text_buff, text_buff_end);
					textt_count++;
				}
				else if(strcmp((char*)node->name, "empty-line") == 0)
				{
					gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
					textt_count++;
				}
				else if(strcmp((char*)node->name, "title") == 0)
				{
					parse_title(node, text_buff, text_buff_end);
					textt_count++;
				}
				else if(strcmp((char*)node->name, "epigraph") == 0)
				{
					parse_epigraph(node, text_buff, text_buff_end);
					textt_count++;
				}
				else if(strcmp((char*)node->name, "image") == 0)
				{
					parse_image(node, text_buff, text_buff_end);
					textt_count++;
				}
				else if(strcmp((char*)node->name, "poem") == 0)
				{
					parse_poem(node, text_buff, text_buff_end);
					textt_count++;
				}
				else if(strcmp((char*)node->name, "subtitle") == 0)
				{
					parse_subtitle(node, text_buff, text_buff_end);
					textt_count++;
				}
				else if(strcmp((char*)node->name, "cite") == 0)
				{
					parse_cite(node, text_buff, text_buff_end);
					textt_count++;
				}
				else if(strcmp((char*)node->name, "table") == 0)
				{
					print_unsupported_tag("table");
					textt_count++;
				}
			}

			node = node->next;
		}
		if(textt_count == 0)
			fputs("fb2 format error: no text tags in section tag\n", stderr);
	}
	return 0;
}

