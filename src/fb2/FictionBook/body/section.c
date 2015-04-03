#include "body_chunks.h"

<<<<<<< HEAD
int parse_section(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end, GtkTreeIter* tree_iter)
=======
int parse_section(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end, GtkTreeIter* tree_iter, gboolean store_section)
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

<<<<<<< HEAD
=======
	GtkTextBuffer* text_buff			= obj->text_buff;
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
	xmlNode* node						= parent_node->children;
	GtkTreeStore* sections_treestore	= obj->sections_treestore;

	parse_id_attribute(obj, parent_node, text_buff_end);

<<<<<<< HEAD

	GtkTreeIter section_iter;
	gtk_tree_store_append(sections_treestore, &section_iter, tree_iter);
	gint cur_line = gtk_text_iter_get_line(text_buff_end);
	gtk_tree_store_set(sections_treestore, &section_iter,	SECTION_STRING_COLUMN,	cur_line,
															SECTION_NAME_COLUMN,	_C("No Title"),-1);
=======
	gboolean has_title		= FALSE;
	GtkTreeIter section_iter;

	if(store_section == TRUE)
	{
		gtk_tree_store_append(sections_treestore, &section_iter, tree_iter);

		gint cur_line = gtk_text_iter_get_line(text_buff_end);
		gtk_tree_store_set(sections_treestore, &section_iter, SECTION_STRING_COLUMN, cur_line, -1);
	}
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "title") == 0)
			{
<<<<<<< HEAD
				navigation_set_chapter_by_title(obj, node, &section_iter);
				parse_title(obj, node, text_buff_end);
=======
				if(store_section == TRUE)
				{
					GtkTextMark* start_tag_mark = gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);

					parse_title(obj, node, text_buff_end);

					GtkTextIter start_tag_iter;
					gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
					gtk_text_buffer_delete_mark(text_buff, start_tag_mark);

					char* title_data = gtk_text_buffer_get_text(text_buff, &start_tag_iter, text_buff_end, TRUE);

					gtk_tree_store_set(sections_treestore, &section_iter,  SECTION_NAME_COLUMN, title_data, -1);
					g_free(title_data);
				}
				else
					parse_title(obj, node, text_buff_end);

				has_title = TRUE;
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
			}
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_epigraph(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "annotation") == 0)
				parse_annotation(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "section") == 0)
<<<<<<< HEAD
				parse_section(obj, node, text_buff_end, &section_iter);
=======
				parse_section(obj, node, text_buff_end, &section_iter, store_section);
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
			else if(strcmp((char*)node->name, "p") == 0)
				parse_p(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "empty-line") == 0)
				parse_empty_line(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "image") == 0)
				parse_image(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "poem") == 0)
				parse_poem(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "subtitle") == 0)
				parse_subtitle(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "cite") == 0)
				parse_cite(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "table") == 0)
				parse_table(obj, node, text_buff_end);
		}

		node = node->next;
	}

<<<<<<< HEAD
=======
	if((has_title == FALSE) && (store_section == TRUE))
	{
		gtk_tree_store_set(sections_treestore, &section_iter, SECTION_NAME_COLUMN, "NO NAME", -1);
	}

>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
	return 0;
}
