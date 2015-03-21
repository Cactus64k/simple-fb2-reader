
#ifndef READER_CHUNKS_H_
#define READER_CHUNKS_H_

	#include "../chunks.h"

	int reader_open_book(char* file_path);
	int reader_close_book();
	int reader_close_app();
	int reader_load_book_config(FB2_READER_BOOK_VIEW* obj, char* file_path);
	gboolean reader_test_file_type(char* file_path, const char* file_ext);
	int reader_set_scroll(FB2_READER_BOOK_VIEW* obj, gint line, gint offset);
	int reader_set_scroll_from_config(FB2_READER_BOOK_VIEW* obj);
	int reader_get_scroll_line_offset(FB2_READER_BOOK_VIEW* obj, gint* line, gint* offset);


#endif /* READER_CHUNKS_H_ */
