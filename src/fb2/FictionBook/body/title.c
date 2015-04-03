#include "body_chunks.h"

int parse_title(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff	= obj->text_buff;
	xmlNode* node				= parent_node->children;

	parse_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_title	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "p") == 0)
				parse_p(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "empty-line") == 0)
				parse_empty_line(obj, node, text_buff_end);
		}

		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	GtkTextIter start_title_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_title_iter, start_title);
	gtk_text_buffer_delete_mark(text_buff, start_title);
	gtk_text_buffer_apply_tag_by_name(text_buff, "title_tag", &start_title_iter, text_buff_end);

	return 0;
}
<<<<<<< HEAD

int navigation_set_chapter_by_title(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTreeIter* cur_tree_iter)
{
	GtkTreeStore* sections_treestore	= obj->sections_treestore;
	xmlNode* node						= parent_node->children;
	GString* buff						= g_string_new(NULL);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "p") == 0)
			{
				get_p_text(node, buff);
				g_string_append_c(buff, ' ');
			}
			else if(strcmp((char*)node->name, "empty-line") == 0)
				g_string_append_c(buff, '\n');
		}

		node = node->next;
	}

	gtk_tree_store_set(sections_treestore, cur_tree_iter,  SECTION_NAME_COLUMN, buff->str, -1);
	g_string_free(buff, TRUE);

	return 0;
}


=======
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
