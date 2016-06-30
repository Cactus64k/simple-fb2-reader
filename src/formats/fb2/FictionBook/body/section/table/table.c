#include "table_chunks.h"
#include "wchar.h"

int td_fill_spaces(GString** cells_buff, glong* cells_table, size_t cells_count, glong* max_height);
int td_word_wrap(GString** cells_buff, glong* cells_table, size_t cells_count);

int parse_fb2_table(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,		EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,		EXIT_FAILURE);

	GtkTextBuffer* text_buff	= app->text_buff;
	xmlNode* node				= parent_node->children;

	parse_fb2_id_attribute(app, parent_node, text_buff_end);

	GtkTextMark* start_tag_mark	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	glong* cells_table			= NULL;
	size_t cells_count			= 0;
	parse_fb2_table_get_size(app, parent_node, &cells_table, &cells_count);

	GString** cells_buff		= calloc(sizeof(GString*),	cells_count);

	for(size_t i=0; i<cells_count; i++)
		cells_buff[i] = g_string_new(NULL);

	parse_fb2_table_put_line(app, text_buff_end, cells_table, cells_count, "┌", "┬",  "┐\n");

	size_t coll_index = 0;

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "tr") == 0)
			{
				xmlNode* td_node = node->children;
				size_t cell_index = 0;

				while(td_node != NULL)
				{
					if(td_node->type == XML_ELEMENT_NODE)
					{
						if((strcmp((char*)td_node->name, "td") == 0) || (strcmp((char*)td_node->name, "th") == 0))
							parse_fb2_p_get_text(td_node, cells_buff[cell_index++]);
					}

					td_node = td_node->next;
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



				if(parse_fb2_table_tr_is_next(node) == 0)
					parse_fb2_table_put_line(app, text_buff_end, cells_table, cells_count, "└", "┴",  "┘\n");
				else
					parse_fb2_table_put_line(app, text_buff_end, cells_table, cells_count, "├", "┼",  "┤\n");

				coll_index++;

			}
		}
		node = node->next;
	}

	for(size_t i=0; i<cells_count; i++)
		g_string_free(cells_buff[i], TRUE);

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag_by_name(text_buff, "table_tag", &start_tag_iter, text_buff_end);


	free(cells_buff);
	free(cells_table);

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
		if(cells_buff[i] != NULL)
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
							//j = j +1;
							ptrdiff_t insert_pos = (ptrdiff_t)(space - cells_buff[i]->str);

							if(need_space > 0)
								g_string_insert_len(cells_buff[i], insert_pos, spaces, need_space);
						}
					}
				}
			}

		}
	}

	return EXIT_SUCCESS;
}


int td_fill_spaces(GString** cells_buff, glong* cells_table, size_t cells_count, glong* max_height)
{
	g_return_val_if_fail(cells_buff != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(cells_table != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(max_height != NULL,	EXIT_FAILURE);

	char spaces[MAX_CELL_LENGTH];
		memset(spaces, ' ', sizeof(spaces));


	*max_height = 0;
	glong* cell_len = calloc(sizeof(glong), cells_count);

	for(size_t i=0; i<cells_count; i++)
	{
		if(cells_buff[i] != NULL)
		{
			cell_len[i] = g_utf8_strlen(cells_buff[i]->str, cells_buff[i]->len);
			if(cells_table[i] != 0)
			{
				glong height	= cell_len[i]/cells_table[i];
				*max_height		= MAX(*max_height, height);
			}
		}
	}

	for(size_t i=0; i<cells_count; i++)						// проходимся по всем ячейкам
	{
		if(cells_table[i] != 0)
		{
			glong need_space = (*max_height+1) * cells_table[i];
			glong tail = need_space % MAX_CELL_LENGTH;

			g_string_append_len(cells_buff[i], spaces, tail);

			for(glong j=0; j<need_space; j+=MAX_CELL_LENGTH)
				g_string_append_len(cells_buff[i], spaces, MAX_CELL_LENGTH);
		}
	}


	free(cell_len);

	return EXIT_SUCCESS;
}














