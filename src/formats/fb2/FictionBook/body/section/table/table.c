#include "table_chunks.h"

int td_fll_spaces(GString** cells_buff, glong* cells_table, size_t cells_count, glong* max_height);

int parse_fb2_table(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	parse_fb2_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_tag_mark	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	glong* cells_table			= NULL;
	size_t cells_count			= 0;
	parse_fb2_table_get_size(obj, parent_node, &cells_table, &cells_count);

	GString** cells_buff		= calloc(sizeof(GString*),	cells_count);

	for(size_t i=0; i<cells_count; i++)
		cells_buff[i] = g_string_new(NULL);

	parse_fb2_table_put_line(obj, text_buff_end, cells_table, cells_count, "┌", "┬",  "┐");

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
				td_fll_spaces(cells_buff, cells_table, cells_count, &max_height);

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
					parse_fb2_table_put_line(obj, text_buff_end, cells_table, cells_count, "└", "┴",  "┘");
				else
					parse_fb2_table_put_line(obj, text_buff_end, cells_table, cells_count, "├", "┼",  "┤");

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

	return 0;
}


int td_fll_spaces(GString** cells_buff, glong* cells_table, size_t cells_count, glong* max_height)
{
	g_return_val_if_fail(cells_buff != NULL, -1);
	g_return_val_if_fail(cells_table != NULL, -2);


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
			for(glong j=0; j<need_space; j++)			// проходимся по отсутствующим строкам
				g_string_append_c(cells_buff[i], ' ');
		}
	}


	free(cell_len);

	return 0;
}














