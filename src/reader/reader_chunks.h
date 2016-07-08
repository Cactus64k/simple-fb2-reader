
#ifndef READER_CHUNKS_H_
#define READER_CHUNKS_H_

	#include "../chunks.h"

	int reader_open_book						(APP* app, char* book_path);
	int reader_close_book						(APP* app);
	int reader_close_app						(APP* app);
	int reader_scroll_restore					(APP* app, int line, int offset);
	int reader_scroll_save						(APP* app);
	int reader_scroll_at_line_offset			(APP* app, gint line, gint line_offset);
	int reader_set_color_theme					(APP* app, const char* color_theme);
	int reader_show_error						(APP* app, const char* message);
	int reader_hndl_GError						(APP* app, GError** error);
	int reader_read_config						(APP* app);
	int reader_gui								(APP* app, GtkBuilder* builder);
	int reader_search_wnd						(APP* app, GtkBuilder* builder);
	int reader_create_text_tags							(APP* app);
	char* reader_get_book_hash					(APP* app, char* file_path);
	BOOK_TYPE reader_get_book_type				(char* file_path);


	int reader_books_db_init					(APP* app);
	int64_t reader_books_db_add_new				(APP* app, const char* hash);
	int64_t reader_books_db_get_index_by_hash	(APP* app, const char* hash);
	int reader_books_db_get_int_by_index		(APP* app, int64_t index, const char* param);
	int reader_books_db_set_int_by_index		(APP* app, int64_t index, const char* param, int value);

	gboolean auto_scroll_update					(gpointer user_data);

#endif /* READER_CHUNKS_H_ */
