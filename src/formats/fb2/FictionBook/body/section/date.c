#include "section_chunks.h"

int parse_fb2_date(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	GtkTextBuffer* text_buff	= app->text_buff;
	char* value_attr			= (char*)xmlGetProp(parent_node, (xmlChar*)"id");

	if(value_attr != NULL)
		gtk_text_buffer_insert(text_buff, text_buff_end, value_attr, -1);

	xmlFree(value_attr);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	return EXIT_SUCCESS;
}
