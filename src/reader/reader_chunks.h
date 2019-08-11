
#ifndef READER_CHUNKS_H_
#define READER_CHUNKS_H_

	#include "../chunks.h"
	#include "reader_book/reader_book_chunks.h"
	#include "reader_app/reader_app.h"

	int reader_scroll_restore					(APP* app, int line, int offset);
	int reader_scroll_save						(APP* app);
	int reader_scroll_to_line_offset			(APP* app, gint line, gint line_offset);
	int reader_set_color_theme					(APP* app);
	int reader_create_text_tags					(APP* app);
	int reader_start_screen						(APP* app);
	int reader_add_book_to_start_screen			(APP* app, const char* book_title, const char* book_hash, const char* book_path);

	gboolean auto_scroll_update					(gpointer user_data);

#endif /* READER_CHUNKS_H_ */
