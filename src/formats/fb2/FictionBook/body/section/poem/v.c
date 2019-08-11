#include "poem.h"

int parse_fb2_v(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(text_buff_end != NULL,	EXIT_FAILURE);

	//GtkTextBuffer* text_buff	= app->text_buff;

	parse_fb2_p_no_tab(app, parent_node, text_buff_end);
	//gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	return EXIT_SUCCESS;
}
