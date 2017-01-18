#include "p_chunks.h"

int parse_fb2_p_get_text(xmlNode* parent_node, GString* buff)
{
	g_return_val_if_fail(parent_node	!= NULL, EXIT_FAILURE);;
	g_return_val_if_fail(buff	!= NULL, EXIT_FAILURE);;

	xmlNode* node = parent_node->children;

	while(node != NULL)
	{
		if(node->type == XML_TEXT_NODE)
		{
			if(strcmp((char*)node->name, "text") == 0)
				g_string_append(buff, (char*)node->content);
		}
		else if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "strong") == 0)				// жирный
				parse_fb2_p_get_text(node, buff);
			else if(strcmp((char*)node->name, "emphasis") == 0)		// курсив
				parse_fb2_p_get_text(node, buff);
			else if(strcmp((char*)node->name, "a") == 0)				// ссылка
				parse_fb2_p_get_text(node, buff);
			else if(strcmp((char*)node->name, "strikethrough") == 0)	// зачеркнутый
				parse_fb2_p_get_text(node, buff);
			else if(strcmp((char*)node->name, "sub") == 0)				// нижний индекс
				parse_fb2_p_get_text(node, buff);
			else if(strcmp((char*)node->name, "sup") == 0)				// верхний индекс
				parse_fb2_p_get_text(node, buff);
			else if(strcmp((char*)node->name, "code") == 0)				// код, моноширинный шрифт
				parse_fb2_p_get_text(node, buff);
			else if(strcmp((char*)node->name, "image") == 0)			// картинка
				parse_fb2_p_get_text(node, buff);
			else if(strcmp((char*)node->name, "style") == 0)			// стилевое оформление
				parse_fb2_p_get_text(node, buff);
		}
		node = node->next;
	}


	return EXIT_SUCCESS;
}
