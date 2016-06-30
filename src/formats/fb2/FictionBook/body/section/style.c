#include "section_chunks.h"

int parse_fb2_style(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	xmlNode* node				= parent_node;//parent_node->children;

	//fputs(_C("tag <style> not fully supported!\n"), stderr);
	parse_fb2_p__(app, node, text_buff_end);

	return EXIT_SUCCESS;
}
