#include "body_chunks.h"

int parse_fb2_title(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GtkTextBuffer* text_buff	= app->text_buff;
	xmlNode* node				= parent_node->children;

	parse_fb2_id_attribute(app, parent_node, text_buff_end);

	GtkTextMark* start_title	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "p") == 0)
				parse_fb2_p(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "empty-line") == 0)
				parse_fb2_empty_line(app, node, text_buff_end);
		}

		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	GtkTextIter start_title_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_title_iter, start_title);
	gtk_text_buffer_delete_mark(text_buff, start_title);
	gtk_text_buffer_apply_tag_by_name(text_buff, "title_tag", &start_title_iter, text_buff_end);

	return EXIT_SUCCESS;
}

int parse_fb2_navigation_set_chapter_by_title(APP* app, xmlNode* parent_node, GtkTreeIter* cur_tree_iter)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(cur_tree_iter != NULL,	EXIT_FAILURE);

	GtkTreeStore* sections_treestore	= app->sections_treestore;
	xmlNode* node						= parent_node->children;
	GString* buff						= g_string_new(NULL);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "p") == 0)
			{
				parse_fb2_p_get_text(node, buff);
				g_string_append_c(buff, ' ');
			}
			else if(strcmp((char*)node->name, "empty-line") == 0)
				g_string_append_c(buff, '\n');
		}

		node = node->next;
	}

	gtk_tree_store_set(sections_treestore, cur_tree_iter,  SECTION_NAME_COLUMN, buff->str, -1);
	g_string_free(buff, TRUE);

	return EXIT_SUCCESS;
}


