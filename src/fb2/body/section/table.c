#include "section_chunks.h"

size_t get_formated_text_len(xmlNode* parent_node);
int table_get_column_size(xmlNode* parent_node, size_t column_array_len);

int parse_table(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	parse_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_tag_mark		= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	table_get_column_size(parent_node, 0);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "tr") == 0)
			{
				xmlNode* td_node = node->children;

				while(td_node != NULL)
				{
					if(td_node->type == XML_ELEMENT_NODE)
					{
						if(strcmp((char*)td_node->name, "td") == 0)
						{
							if(td_node->children != NULL)
							{
								parse_formated_text(obj, td_node->children, text_buff_end);

							}
						}

						gtk_text_buffer_insert(text_buff, text_buff_end, "\t\t", -1);
					}

					td_node = td_node->next;
				}
				gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
			}
		}
		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag_by_name(text_buff, "table_tag", &start_tag_iter, text_buff_end);

	return 0;
}

int table_get_column_size(xmlNode* parent_node, size_t column_array_len)
{
	g_return_val_if_fail(parent_node != NULL, -1);

	xmlNode* node = parent_node->children;

	size_t column_index = 0;
	size_t* column_array = NULL;

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "tr") == 0)
			{
				xmlNode* td_node = node->children;

				column_index = 0;

				while(td_node != NULL)
				{
					if(td_node->type == XML_ELEMENT_NODE)
					{
						if((strcmp((char*)td_node->name, "td") == 0) || (strcmp((char*)td_node->name, "th") == 0))
						{
							column_index++;
							if(column_index > column_array_len)
							{
								column_array = realloc(column_array, column_index * sizeof(size_t));
								column_array[column_index-1] = 0;
								column_array_len++;
							}
							size_t len = get_formated_text_len(td_node);

							column_array[column_index-1] = (column_array[column_index-1] > len)? column_array[column_index-1]: len;

						}
					}

					td_node = td_node->next;
				}
			}
		}

		node = node->next;
	}
	return 0;
}

size_t get_formated_text_len(xmlNode* parent_node)
{
	g_return_val_if_fail(parent_node != NULL, 0);

	size_t len = 0;

	while(parent_node != NULL)
	{
		gboolean valid_tag = FALSE;

		if(parent_node->type == XML_TEXT_NODE)
		{
			if(strcmp((char*)parent_node->name, "text") == 0)
				len += g_utf8_strlen((char*)parent_node->content, -1);
		}
		else if(parent_node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)parent_node->name, "strong") == 0)				// жирный
				valid_tag = TRUE;
			else if(strcmp((char*)parent_node->name, "emphasis") == 0)		// курсив
				valid_tag = TRUE;
			else if(strcmp((char*)parent_node->name, "a") == 0)				// ссылка
				valid_tag = TRUE;
			else if(strcmp((char*)parent_node->name, "strikethrough") == 0)	// зачеркнутый
				valid_tag = TRUE;
			else if(strcmp((char*)parent_node->name, "sub") == 0)			// нижний индекс
				valid_tag = TRUE;
			else if(strcmp((char*)parent_node->name, "sup") == 0)			// верхний индекс
				valid_tag = TRUE;
			else if(strcmp((char*)parent_node->name, "code") == 0)			// код, моноширинный шрифт
				valid_tag = TRUE;
			else if(strcmp((char*)parent_node->name, "image") == 0)			// картинка
				valid_tag = TRUE;
			else if(strcmp((char*)parent_node->name, "style") == 0)			// стилевое оформление
				valid_tag = TRUE;
		}

		if(valid_tag == TRUE)
			len += get_formated_text_len(parent_node->children);



		parent_node = parent_node->next;
	}

	return len;
}














