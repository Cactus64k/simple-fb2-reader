#include "section_chunks.h"

int parse_date(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff	= obj->text_buff;
	const char* value_attr		= NULL;

	parse_attribute(obj, parent_node, "id", &value_attr);

	if(value_attr != NULL)
		gtk_text_buffer_insert(text_buff, text_buff_end, value_attr, -1);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	return 0;
}
