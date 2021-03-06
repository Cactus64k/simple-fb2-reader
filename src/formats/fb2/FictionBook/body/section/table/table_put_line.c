#include "table_chunks.h"

int parse_fb2_table_put_line(APP* app, GtkTextIter* text_buff_end, glong* cells_width, size_t cells_count, const char* start, const char* middle, const char* end)
{
	g_return_val_if_fail(cells_width != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(start != NULL,			EXIT_FAILURE);
	g_return_val_if_fail(middle != NULL,		EXIT_FAILURE);
	g_return_val_if_fail(end != NULL,			EXIT_FAILURE);

	GtkTextBuffer* text_buff = app->text_buff;

	GString* buff = g_string_new(NULL);

	//g_string_append_c(buff, '\n');
	g_string_append(buff, start);


	for(size_t i=0; i<cells_count; i++)
	{
		for(size_t k=0; k<cells_width[i]; k++)
			g_string_append(buff, "─");

		if(cells_count > i+1)
			g_string_append(buff, middle);
	}
	g_string_append(buff, end);
	//g_string_append_c(buff, '\n');
	gtk_text_buffer_insert(text_buff, text_buff_end, buff->str, -1);

	g_string_free(buff, TRUE);

	return EXIT_SUCCESS;
}
