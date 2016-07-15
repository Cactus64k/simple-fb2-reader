#ifndef READER_READER_BOOK_READER_BOOK_CHUNKS_H_
	#define READER_READER_BOOK_READER_BOOK_CHUNKS_H_

	#include "../reader_chunks.h"

	int reader_open_book						(APP* app, char* book_path);
	int reader_close_book						(APP* app);
	char* reader_get_book_hash					(APP* app, char* file_path);
	int reader_books_db_init					(APP* app);
	int reader_books_table_add_new				(APP* app, const char* hash, int64_t* index);
	int reader_books_table_get_index_by_hash	(APP* app, const char* hash, int64_t* index);
	int reader_books_table_get_int_by_index		(APP* app, int64_t index, const char* param, int* value);
	int reader_books_table_set_int_by_index		(APP* app, int64_t index, const char* param, int value);
	BOOK_TYPE reader_get_book_type				(char* file_path);

#endif /* READER_READER_BOOK_READER_BOOK_CHUNKS_H_ */
