#include "../fb2_chunks.h"

int parse_style(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	node = node->children;
	fputs("tag <style> not fully supported!\n", stderr);
	parse_formated_text(node, text_buff, text_buff_end);

	return 0;
}
