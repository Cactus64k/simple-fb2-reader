#include "section_chunks.h"

int parse_fb2_empty_line(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	GtkTextBuffer* text_buff = app->text_buff;

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	return EXIT_SUCCESS;
}
