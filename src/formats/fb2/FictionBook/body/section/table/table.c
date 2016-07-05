#include "table_chunks.h"
#include "wchar.h"

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

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "tr") == 0)
			{
				fb2_parse_tr(app, node, text_buff_end, cells_buff, cells_table, cells_count);

				if(parse_fb2_table_tr_is_next(node) == TRUE)
					parse_fb2_table_put_line(app, text_buff_end, cells_table, cells_count, "├", "┼",  "┤\n");
			}
		}
		node = node->next;
	}

	parse_fb2_table_put_line(app, text_buff_end, cells_table, cells_count, "└", "┴",  "┘\n");

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

















