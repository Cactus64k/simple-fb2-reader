#include "FictionBook_chunks.h"

int parse_body(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

<<<<<<< HEAD
	xmlNode* node						= parent_node->children;
	GtkTreeStore* sections_treestore	= obj->sections_treestore;

	GtkTreeIter section_iter;
	gtk_tree_store_append(sections_treestore, &section_iter, NULL);
	gint cur_line = gtk_text_iter_get_line(text_buff_end);
	gtk_tree_store_set(sections_treestore, &section_iter,	SECTION_STRING_COLUMN,	cur_line,
															SECTION_NAME_COLUMN,	_C("No Title"),-1);
=======
	xmlNode* node				= parent_node->children;

	gboolean store_section = !parse_body_name_attribute(obj, parent_node, text_buff_end);
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
<<<<<<< HEAD
			if(strcmp((char*)node->name, "image") == 0)
				parse_image(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "title") == 0)
			{
				navigation_set_chapter_by_title(obj, node, &section_iter);
				parse_title(obj, node, text_buff_end);
			}
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_epigraph(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "section") == 0)
				parse_section(obj, node, text_buff_end, &section_iter);

=======
			if(strcmp((char*)node->name, "section") == 0)
				parse_section(obj, node, text_buff_end, NULL, store_section);
			else if(strcmp((char*)node->name, "title") == 0)
				parse_title(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_epigraph(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "image") == 0)
				parse_image(obj, node, text_buff_end);
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
		}

		node = node->next;
	}
	return 0;
}
