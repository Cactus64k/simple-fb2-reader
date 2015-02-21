#include "../fb2_chunks.h"

int parse_p(FB2_READER_TEXT_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	assert(parent_node != NULL);
	assert(text_buff_end != NULL);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	parse_id_attribute(obj, parent_node, text_buff_end);


	if(node != NULL)
	{
		gtk_text_buffer_insert(text_buff, text_buff_end, "\t", -1);
		parse_formated_text(obj, node, text_buff_end);
		gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
	}

	return 0;
}


int parse_formated_text(FB2_READER_TEXT_VIEW* obj, xmlNode* node, GtkTextIter* text_buff_end)
{
	assert(node != NULL);
	assert(text_buff_end != NULL);

	GtkTextBuffer* text_buff	= obj->text_buff;

	const char* tag = NULL;

	while(node != NULL)
	{
		tag = NULL;

		if(node->type == XML_TEXT_NODE)
		{
			if(strcmp((char*)node->name, "text") == 0)
				gtk_text_buffer_insert(text_buff, text_buff_end, (char*)node->content, -1);
		}
		else if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "strong") == 0)				// жирный
				tag = "strong_tag";
			else if(strcmp((char*)node->name, "emphasis") == 0)			// курсив
				tag = "emphasis_tag";
			else if(strcmp((char*)node->name, "a") == 0)				// ссылка
				parse_link(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "strikethrough") == 0)	// зачеркнутый
				tag = "strikethrough_tag";
			else if(strcmp((char*)node->name, "sub") == 0)				// нижний индекс
				tag = "sub_tag";
			else if(strcmp((char*)node->name, "sup") == 0)				// верхний индекс
				tag = "sup_tag";
			else if(strcmp((char*)node->name, "code") == 0)				// код, моноширинный шрифт
				tag = "code_tag";
			else if(strcmp((char*)node->name, "image") == 0)			// картинка
				parse_image_inline(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "style") == 0)			// стилевое оформление
				parse_style(obj, node, text_buff_end);
		}



		if(tag != NULL)
		{
			GtkTextMark* start_tag_mark = gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

			parse_formated_text(obj, node->children, text_buff_end);

			GtkTextIter start_tag_iter;
			gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
			gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
			//g_object_unref(G_OBJECT(start_tag_mark));
			gtk_text_buffer_apply_tag_by_name(text_buff, tag, &start_tag_iter, text_buff_end);

		}

		node = node->next;
	}
	return 0;
}
