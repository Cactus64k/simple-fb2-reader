#include "reader_chunks.h"

int reader_get_scroll_line_offset(FB2_READER_BOOK_VIEW* obj, gint* line, gint* offset)
{
	GtkTextView* text_view = obj->text_view;
	GtkTextIter scroll_iter;
	GtkAdjustment* adj	= gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(text_view));
	gint scroll_pos		= round(gtk_adjustment_get_value(adj));

	gtk_text_view_get_iter_at_location(text_view, &scroll_iter, 0, scroll_pos);

	*line	= gtk_text_iter_get_line(&scroll_iter);
	*offset	= gtk_text_iter_get_line_offset(&scroll_iter);

	return 0;
}

int reader_set_scroll(FB2_READER_BOOK_VIEW* obj, gint line, gint offset)
{
	GtkTextBuffer* text_buff = obj->text_buff;
	GtkTextView* text_view = obj->text_view;
	GtkTextIter iter;

	while(gtk_events_pending())
		gtk_main_iteration();

	gtk_text_buffer_get_iter_at_line_offset(text_buff, &iter, line, offset);

	GtkTextMark* line_mark = gtk_text_buffer_create_mark(text_buff, NULL, &iter, TRUE);

	gtk_text_view_scroll_to_mark(text_view, line_mark, 0.0, TRUE, 0.0, 0.0);

	gtk_text_buffer_delete_mark(text_buff, line_mark);

	return 0;
}

int reader_set_scroll_from_config(FB2_READER_BOOK_VIEW* obj)
{

	GtkTextBuffer* text_buff	= obj->text_buff;
	GtkTextView* text_view		= obj->text_view;
	GtkTextIter iter;

	while(gtk_events_pending())
		gtk_main_iteration();

	gint line					= g_key_file_get_integer(obj->config, "book", "read_line", NULL);
	gint offset					= g_key_file_get_integer(obj->config, "book", "read_line_offset", NULL);

	gtk_text_buffer_get_iter_at_line_offset(text_buff, &iter, line, offset);

	if(gtk_text_view_scroll_to_iter(text_view, &iter, 0.0, TRUE, 0.0, 0.0) == FALSE)
	{
		GtkTextMark* line_mark = gtk_text_buffer_create_mark(text_buff, NULL, &iter, TRUE);

		gtk_text_view_scroll_to_mark(text_view, line_mark, 0.0, TRUE, 0.0, 0.0);

		gtk_text_buffer_delete_mark(text_buff, line_mark);

	}

	return 0;
}
