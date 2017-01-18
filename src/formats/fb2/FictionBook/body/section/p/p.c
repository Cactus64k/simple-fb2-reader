#include "p_chunks.h"

int parse_fb2_p(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node	!= NULL, EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end	!= NULL, EXIT_FAILURE);

	GtkTextBuffer* text_buff	= app->text_buff;
	xmlNode* node				= parent_node;//parent_node->children;

	parse_fb2_id_attribute(app, parent_node, text_buff_end);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\t", -1);
	parse_fb2_p__(app, node, text_buff_end);

	return EXIT_SUCCESS;
}



int parse_fb2_p__(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GtkTextBuffer* text_buff	= app->text_buff;
	xmlNode* node				= parent_node->children;

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
			else if(strcmp((char*)node->name, "style") == 0)			// стилевое оформление
				parse_fb2_style(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "a") == 0)				// ссылка
				parse_fb2_a(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "strikethrough") == 0)	// зачеркнутый
				tag = "strikethrough_tag";
			else if(strcmp((char*)node->name, "sub") == 0)				// нижний индекс
				tag = "sub_tag";
			else if(strcmp((char*)node->name, "sup") == 0)				// верхний индекс
				tag = "sup_tag";
			else if(strcmp((char*)parent_node->name, "code") == 0)		// код, моноширинный шрифт
				tag = "code_tag";
			else if(strcmp((char*)node->name, "image") == 0)			// картинка
				parse_fb2_image_inline(app, node, text_buff_end);
		}



		if(tag != NULL)
		{
			GtkTextMark* start_tag_mark = gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

			parse_fb2_p__(app, node, text_buff_end);

			GtkTextIter start_tag_iter;
			gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
			gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
			//g_object_unref(G_OBJECT(start_tag_mark));
			gtk_text_buffer_apply_tag_by_name(text_buff, tag, &start_tag_iter, text_buff_end);

		}

		node = node->next;
	}

	//gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	return EXIT_SUCCESS;
}
