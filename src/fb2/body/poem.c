#include "../fb2_chunks.h"

int parse_stanza(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end);

int parse_poem(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);


	node = node->children;
	size_t title_count	= 0;
	size_t stanza_count	= 0;
	size_t date_count	= 0;


	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

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
					fputs("fb2 format error: more then one title in poem tag\n", stderr);
			}
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_epigraph(node, text_buff, text_buff_end);
			else if(strcmp((char*)node->name, "stanza") == 0)
			{
				parse_stanza(node, text_buff, text_buff_end);
				stanza_count++;
			}
			else if(strcmp((char*)node->name, "text-author") == 0)
				parse_text_autor(node, text_buff, text_buff_end);
			else if(strcmp((char*)node->name, "date") == 0)
			{
				if(date_count == 0)
				{
					parse_date(node, text_buff, text_buff_end);
					date_count++;
				}
				else
					fputs("fb2 format error: more then one date in poem tag\n", stderr);
			}
		}

		node = node->next;
	}

	if(stanza_count == 0)
		fputs("fb2 format error: no stanza in poem tag\n", stderr);

	return 0;
}

int parse_stanza(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	node = node->children;

	GtkTextMark* start_tag_mark	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, true);
	GtkTextTag* stanza_tag		= GLOBAL_FB2_READER.stanza_tag;

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "title") == 0)
				parse_title(node, text_buff, text_buff_end);
			else if(strcmp((char*)node->name, "subtitle") == 0)
				parse_subtitle(node, text_buff, text_buff_end);
			else if(strcmp((char*)node->name, "v") == 0)
			{
				xmlNode* v_node = node->children;
				parse_formated_text(v_node, text_buff, text_buff_end);
				gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
			}
		}

		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	//g_object_unref(G_OBJECT(start_tag_mark));
	gtk_text_buffer_apply_tag(text_buff, stanza_tag, &start_tag_iter, text_buff_end);

	return 0;
}
