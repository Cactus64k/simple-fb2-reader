#include "section_chunks.h"

int parse_fb2_section(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end, GtkTreeIter* tree_iter)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	xmlNode* node						= parent_node->children;
	GtkTreeStore* sections_treestore	= app->sections_treestore;

	parse_fb2_id_attribute(app, parent_node, text_buff_end);


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
				parse_fb2_navigation_set_chapter_by_title(app, node, &section_iter);
				parse_fb2_title(app, node, text_buff_end);
			}
			else if(strcmp((char*)node->name, "epigraph") == 0)
				parse_fb2_epigraph(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "annotation") == 0)
				parse_fb2_annotation(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "section") == 0)
				parse_fb2_section(app, node, text_buff_end, &section_iter);
			else if(strcmp((char*)node->name, "p") == 0)
				parse_fb2_p(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "empty-line") == 0)
				parse_fb2_empty_line(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "image") == 0)
				parse_fb2_image(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "poem") == 0)
				parse_fb2_poem(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "subtitle") == 0)
				parse_fb2_subtitle(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "cite") == 0)
				parse_fb2_cite(app, node, text_buff_end);
			else if(strcmp((char*)node->name, "table") == 0)
				parse_fb2_table(app, node, text_buff_end);
		}

		node = node->next;
	}

	return EXIT_SUCCESS;
}
