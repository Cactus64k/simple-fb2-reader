#include "../fb2_chunks.h"

int parse_stanza(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end);

int parse_poem(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	parse_id_attribute(obj, parent_node, text_buff_end);


	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "title") == 0)
				parse_title(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_epigraph(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "stanza") == 0)
				parse_stanza(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "text-author") == 0)
				parse_text_autor(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "date") == 0)
				parse_date(obj, node, text_buff_end);
		}

		node = node->next;
	}

	return 0;
}

int parse_stanza(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	GtkTextMark* start_tag_mark	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "title") == 0)
				parse_title(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "subtitle") == 0)
				parse_subtitle(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "v") == 0)
			{
				xmlNode* v_node = node->children;
				parse_formated_text(obj, v_node, text_buff_end);
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
	gtk_text_buffer_apply_tag_by_name(text_buff, "stanza_tag", &start_tag_iter, text_buff_end);

	return 0;
}
