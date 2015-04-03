#include "body_chunks.h"

int parse_section(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end, GtkTreeIter* tree_iter)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	xmlNode* node						= parent_node->children;
	GtkTreeStore* sections_treestore	= obj->sections_treestore;

	parse_id_attribute(obj, parent_node, text_buff_end);


	GtkTreeIter section_iter;
	gtk_tree_store_append(sections_treestore, &section_iter, tree_iter);
	gint cur_line = gtk_text_iter_get_line(text_buff_end);
	gtk_tree_store_set(sections_treestore, &section_iter,	SECTION_STRING_COLUMN,	cur_line,
															SECTION_NAME_COLUMN,	_C("No Title"),-1);

	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, "title") == 0)
			{
				navigation_set_chapter_by_title(obj, node, &section_iter);
				parse_title(obj, node, text_buff_end);
			}
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_epigraph(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "annotation") == 0)
				parse_annotation(obj, node, text_buff_end);
			else if(strcmp((char*)node->name, "section") == 0)
				parse_section(obj, node, text_buff_end, &section_iter);
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

	return 0;
}
