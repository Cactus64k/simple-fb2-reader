#include "reader_chunks.h"

gboolean auto_scroll_update(gpointer user_data)
{
	APP* app 								= (APP*)user_data;
	GtkScrolledWindow* scrolled_window		= app->text_scrolledwindow;
	GtkAdjustment* adj						= gtk_scrolled_window_get_vadjustment(scrolled_window);
	double scroll_pos						= gtk_adjustment_get_value(adj);

	gtk_adjustment_set_value(adj, scroll_pos + 1);

	return app->auto_scroll;
}

int reader_scroll_save(APP* app)
{
	GtkTextView* text_view		= app->text_view;
	int64_t book_index			= app->book_index;
	char* book_hash				= app->book_hash;
	GtkAdjustment* vertical_adj	= gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(text_view));
	double scroll_pos			= gtk_adjustment_get_value(vertical_adj);
	GtkTextIter scroll_iter;

	gtk_text_view_get_iter_at_location(text_view, &scroll_iter, 0, (gint)scroll_pos);

	gint line					= gtk_text_iter_get_line(&scroll_iter);
	gint line_offset			= gtk_text_iter_get_line_offset(&scroll_iter);

	if((line != 0) || (line_offset != 0))
	{
		if(book_index == -1)
			reader_books_table_add_new(app, book_hash, &book_index);

		reader_books_table_set_int_by_index(app, book_index, "line", line);
		reader_books_table_set_int_by_index(app, book_index, "line_offset", line_offset);

		app->book_index = book_index;
	}

	return EXIT_SUCCESS;
}

int reader_scroll_to_line_offset(APP* app, gint line, gint line_offset)
{
	GtkTextBuffer* text_buff			= app->text_buff;
	GtkTextView* text_view				= app->text_view;
	GtkAdjustment* horisontal_adj		= gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(text_view));
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
			}

			gtk_adjustment_set_value(horisontal_adj, 0.0);
		}
	}

	return EXIT_FAILURE;
}

int reader_scroll_restore(APP* app, int line, int line_offset)
{
	while(gtk_events_pending())
		gtk_main_iteration();

	reader_scroll_to_line_offset(app, line, line_offset);

	return EXIT_SUCCESS;
}
