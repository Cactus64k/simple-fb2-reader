#include "reader_chunks.h"

int reader_scroll_save(FB2_READER_BOOK_VIEW* obj)
{
	GtkTextView* text_view = obj->text_view;
	GtkTextIter scroll_iter;
	GtkAdjustment* adj		= gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(text_view));
	double scroll_pos		= gtk_adjustment_get_value(adj);

	gtk_text_view_get_iter_at_location(text_view, &scroll_iter, 0, scroll_pos);

	gint read_line			= gtk_text_iter_get_line(&scroll_iter);
	g_key_file_set_integer(obj->config, "book", "read_line", read_line);

	gint read_line_offset	= gtk_text_iter_get_line_offset(&scroll_iter);
	g_key_file_set_integer(obj->config, "book", "read_line_offset", read_line_offset);

	return 0;
}

int reader_scroll_at_line_offset(FB2_READER_BOOK_VIEW* obj, gint line, gint line_offset)
{
	GtkTextBuffer* text_buff		= obj->text_buff;
	GtkTextView* text_view			= obj->text_view;
	GtkAdjustment* horisontal_adj	= gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(text_view));
	GtkTextIter scroll_iter;

	if(gtk_text_buffer_get_line_count(text_buff) >= line)
	{
		GtkTextIter test_iter;
		gtk_text_buffer_get_iter_at_line(text_buff, &test_iter, line);

		gtk_text_iter_forward_to_line_end(&test_iter);

		if(gtk_text_iter_get_line_offset(&test_iter) >= line_offset)
		{
			gtk_text_buffer_get_iter_at_line_offset(text_buff, &scroll_iter, line, line_offset);

			if(gtk_text_view_scroll_to_iter(text_view, &scroll_iter, 0.0, TRUE, 0.0, 0.0) == FALSE)
			{
				GtkTextMark* line_mark = gtk_text_buffer_create_mark(text_buff, NULL, &scroll_iter, TRUE);
				gtk_text_view_scroll_to_mark(text_view, line_mark, 0.0, TRUE, 0.0, 0.0);
				gtk_text_buffer_delete_mark(text_buff, line_mark);

				gtk_adjustment_set_value(horisontal_adj, 0.0);

				return 0;
			}
		}
	}

	return -1;
}

int reader_scroll_restore(FB2_READER_BOOK_VIEW* obj)
{
	while(gtk_events_pending())
		gtk_main_iteration();

	gint line					= g_key_file_get_integer(obj->config, "book", "read_line", NULL);
	gint offset					= g_key_file_get_integer(obj->config, "book", "read_line_offset", NULL);

	reader_scroll_at_line_offset(obj, line, offset);

	return 0;
}
