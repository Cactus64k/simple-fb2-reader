#include "reader_chunks.h"

int reader_start_screen(APP* app)
{
	sqlite3* db					= app->book_db;
	sqlite3_stmt* query			= NULL;
	GtkTextBuffer* text_buff	= app->text_buff;
	GtkTextIter text_buff_end;

	sqlite3_prepare(db, "SELECT name, path FROM recent_books_ring ORDER BY time DESC;", -1, &query, NULL);

	gtk_text_buffer_get_end_iter(text_buff, &text_buff_end);

	GtkTextMark* start_tag_mark	= gtk_text_buffer_create_mark(text_buff, NULL, &text_buff_end, TRUE);

	gtk_text_buffer_insert_with_tags_by_name(text_buff, &text_buff_end, _C("\n\nRecent books:\n\n"), -1, "title_tag",  NULL);

	while(sqlite3_step(query) == SQLITE_ROW)
	{
		const char* book_name = (const char*)sqlite3_column_text(query, 0);
		const char* book_path = (const char*)sqlite3_column_text(query, 1);

		if((book_path != NULL)
			&&
			(g_file_test(book_path, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_REGULAR) == TRUE))
		{
			GtkTextTag* a_tag = gtk_text_buffer_create_tag(text_buff, NULL,	"underline",	PANGO_UNDERLINE_SINGLE, NULL);		// освобождается при открытии книги и якобы закрытии старой

			char* book_path_dup	= g_strdup_printf("file://%s", book_path);
			g_signal_connect(G_OBJECT(a_tag), "event", G_CALLBACK(a_tag_event_cb), app);
			g_object_set_data_full(G_OBJECT(a_tag), "href", book_path_dup, g_free);


			book_name = book_name? book_name: _C("No name book");

			gtk_text_buffer_insert(text_buff, &text_buff_end, "○\t", -1);
			gtk_text_buffer_insert_with_tags(text_buff, &text_buff_end, book_name, -1, a_tag, NULL);
			gtk_text_buffer_insert(text_buff, &text_buff_end, "\n\n", -1);
		}
		else
			g_log(NULL, G_LOG_LEVEL_MESSAGE, "Failed to find file on path %s", book_path);
	}

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag_by_name(text_buff, "default_tag", &start_tag_iter, &text_buff_end);

	sqlite3_finalize(query);

	return EXIT_SUCCESS;
}


