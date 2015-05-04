
#ifndef READER_CHUNKS_H_
#define READER_CHUNKS_H_

	#include "../chunks.h"

	int reader_open_book(char* file_path);
	int reader_close_book();
	int reader_close_app();
	int reader_load_book_config(FB2_READER_BOOK_VIEW* obj, char* file_path);
	BOOK_TYPE reader_get_book_type(char* file_path);
	int reader_scroll_restore(FB2_READER_BOOK_VIEW* obj);
	int reader_scroll_save(FB2_READER_BOOK_VIEW* obj);
	int reader_scroll_at_line_offset(FB2_READER_BOOK_VIEW* obj, gint line, gint line_offset);
	int reader_set_color_theme(FB2_READER* obj, const char* color_theme);


#endif /* READER_CHUNKS_H_ */
