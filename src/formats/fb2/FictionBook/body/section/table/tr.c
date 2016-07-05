#include "table_chunks.h"

int td_fill_spaces(GString** cells_buff, glong* cells_table, size_t cells_count, glong* max_height);
int td_word_wrap(GString** cells_buff, glong* cells_table, size_t cells_count);

int fb2_parse_tr(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end, GString** cells_buff, glong* cells_table, size_t cells_count)
{
	GtkTextBuffer* text_buff	= app->text_buff;
	xmlNode* node				= parent_node->children;
	size_t cell_index			= 0;

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "td") == 0)
				parse_fb2_p_get_text(node, cells_buff[cell_index++]);
			else if (strcmp((char*)node->name, "th") == 0)
				parse_fb2_p_get_text(node, cells_buff[cell_index++]);
		}

		node = node->next;
	}

	glong max_height = 0;
	td_word_wrap(cells_buff, cells_table, cells_count);
	td_fill_spaces(cells_buff, cells_table, cells_count, &max_height);

	for(size_t i=0; i<=max_height; i++)
	{
		gtk_text_buffer_insert(text_buff, text_buff_end, "│", -1);

		for(size_t j=0; j<cells_count; j++)
		{
			glong cell_size	= cells_table[j];

			char* pos_l = g_utf8_offset_to_pointer(cells_buff[j]->str, i*cell_size);
			char* pos_r = g_utf8_offset_to_pointer(cells_buff[j]->str, (i+1)*cell_size);

			glong cell_string_size = (ptrdiff_t)(pos_r - pos_l);

			gtk_text_buffer_insert(text_buff, text_buff_end, pos_l, cell_string_size);
			gtk_text_buffer_insert(text_buff, text_buff_end, "│", -1);
		}
		gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
	}

	for(size_t i=0; i<cells_count; i++)
		g_string_set_size(cells_buff[i], 0);

	return EXIT_SUCCESS;
}


int td_word_wrap(GString** cells_buff, glong* cells_table, size_t cells_count)
{
	g_return_val_if_fail(cells_buff != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(cells_table != NULL,	EXIT_FAILURE);

	char spaces[MAX_CELL_LENGTH];
	memset(spaces, ' ', sizeof(spaces));

	for(size_t i=0; i<cells_count; i++)
	{
		glong str_len	= g_utf8_strlen(cells_buff[i]->str, (gssize)cells_buff[i]->len);
		glong cell_len	= cells_table[i];
		for(glong j=0; j<str_len; j+=cell_len)
		{
			char* l_pos	= g_utf8_offset_to_pointer(cells_buff[i]->str, j);
			char* r_pos	= g_utf8_offset_to_pointer(cells_buff[i]->str, (j+cell_len>str_len)? str_len: j+cell_len);
			if(*r_pos != 0)
			{
				char* space	= g_utf8_strrchr(l_pos, (ptrdiff_t)(r_pos - l_pos), ' ');

				if(space != NULL)
				{
					glong space_pos	= g_utf8_pointer_to_offset(cells_buff[i]->str, space);
					if(space_pos != 0)
					{
						glong need_space = cell_len - (space_pos % cell_len)-1;

						str_len = str_len + need_space;
						ptrdiff_t insert_pos = (ptrdiff_t)(space - cells_buff[i]->str);

						if(need_space > 0)
							g_string_insert_len(cells_buff[i], insert_pos, spaces, need_space);
					}
				}
			}
		}

	}

	return EXIT_SUCCESS;
}


int td_fill_spaces(GString** cells_buff, glong* cells_table, size_t cells_count, glong* max_height)		// добиваем каждую ячейку до размера максимальной ячейки
{
	g_return_val_if_fail(cells_buff != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(cells_table != NULL,	EXIT_FAILURE);

	char spaces[MAX_CELL_LENGTH];
		memset(spaces, ' ', sizeof(spaces));


	*max_height = 0;
	for(size_t i=0; i<cells_count; i++)		// вычисляем максимальную высоту в строках
	{
		glong cur_height = g_utf8_strlen(cells_buff[i]->str, cells_buff[i]->len);
		if(cells_table[i] != 0)
		{
			glong height	= cur_height/cells_table[i];
			*max_height		= MAX(*max_height, height);
		}
	}

	for(size_t i=0; i<cells_count; i++)						// проходимся по всем ячейкам
	{
		if(cells_table[i] != 0)
		{
			glong need_space	= (*max_height+1) * cells_table[i];
			glong tail			= need_space % MAX_CELL_LENGTH;

			g_string_append_len(cells_buff[i], spaces, tail);

			for(glong j=0; j<need_space; j+=MAX_CELL_LENGTH)
				g_string_append_len(cells_buff[i], spaces, MAX_CELL_LENGTH);
		}
	}

	return EXIT_SUCCESS;
}
