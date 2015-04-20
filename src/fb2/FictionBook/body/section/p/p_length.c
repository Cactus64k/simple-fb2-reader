#include "p_chunks.h"

int p_get_length(xmlNode* parent_node, glong* len)
{
	g_return_val_if_fail(parent_node	!= NULL, -1);
	g_return_val_if_fail(len			!= NULL, -2);

	xmlNode* node = parent_node->children;

	while(node != NULL)
	{
		if(node->type == XML_TEXT_NODE)
		{
			if(strcmp((char*)node->name, "text") == 0)
			{
				*len += g_utf8_strlen((char*)node->content, -1);
			}
		}
		else if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "strong") == 0)				// жирный
				p_get_length(node, len);
			else if(strcmp((char*)node->name, "emphasis") == 0)			// курсив
				p_get_length(node, len);
			else if(strcmp((char*)node->name, "a") == 0)				// ссылка
				p_get_length(node, len);
			else if(strcmp((char*)node->name, "strikethrough") == 0)	// зачеркнутый
				p_get_length(node, len);
			else if(strcmp((char*)node->name, "sub") == 0)				// нижний индекс
				p_get_length(node, len);
			else if(strcmp((char*)node->name, "sup") == 0)				// верхний индекс
				p_get_length(node, len);
			else if(strcmp((char*)node->name, "code") == 0)				// код, моноширинный шрифт
				p_get_length(node, len);
			else if(strcmp((char*)node->name, "image") == 0)			// картинка
				p_get_length(node, len);
			else if(strcmp((char*)node->name, "style") == 0)			// стилевое оформление
				p_get_length(node, len);
		}
		node = node->next;
	}

	return 0;
}
