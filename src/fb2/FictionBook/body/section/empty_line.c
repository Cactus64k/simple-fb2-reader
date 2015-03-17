#include "section_chunks.h"

int parse_empty_line(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	GtkTextBuffer* text_buff = obj->text_buff;

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	return 0;
}
