#include "body_chunks.h"

int parse_fb2_body(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	xmlNode* node						= parent_node->children;
	GtkTreeStore* sections_treestore	= obj->sections_treestore;

	GtkTreeIter section_iter;
	gtk_tree_store_append(sections_treestore, &section_iter, NULL);
	gint cur_line = gtk_text_iter_get_line(text_buff_end);
	gtk_tree_store_set(sections_treestore, &section_iter,	SECTION_STRING_COLUMN,	cur_line,
															SECTION_NAME_COLUMN,	_C("No Title"),-1);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "image") == 0)
				parse_fb2_image(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "title") == 0)
			{
				parse_fb2_navigation_set_chapter_by_title(obj, node, &section_iter);
				parse_fb2_title(obj, node, text_buff_end);
			}
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_fb2_epigraph(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "section") == 0)
				parse_fb2_section(obj, node, text_buff_end, &section_iter);

		}

		node = node->next;
	}

	return 0;
}
