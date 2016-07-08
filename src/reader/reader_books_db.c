#include "reader_chunks.h"


int reader_books_db_init(APP* app)
{
	g_return_val_if_fail(app != NULL,		EXIT_FAILURE);

	const char* conf_dir		= g_get_user_config_dir();
	char* db_path				= g_strdup_printf("%s/simple-fb2-reader/books.sqlite3", conf_dir);
	sqlite3** books_db			= &(app->books_db);
	if(sqlite3_open(db_path, books_db) == SQLITE_OK)
	{
		if(sqlite3_exec(*books_db, "CREATE TABLE IF NOT EXISTS books(hash TEXT, line INT, line_offset INT);", NULL, NULL, NULL) != SQLITE_OK)
		{
			g_error("Failed to create books table. %s", sqlite3_errmsg(*books_db));
			return EXIT_FAILURE;
		}
	}
	else
	{
		g_error("Failed to open books database. %s", sqlite3_errmsg(*books_db));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int64_t reader_books_db_add_new(APP* app, const char* hash)
{
	g_return_val_if_fail(app != NULL,		EXIT_FAILURE);
	g_return_val_if_fail(hash != NULL,		EXIT_FAILURE);

	sqlite3* books_db			= app->books_db;
	sqlite3_stmt* query			= NULL;

	sqlite3_prepare(books_db, "INSERT INTO books VALUES(?, 0, 0);", -1, &query, NULL);
	sqlite3_bind_text(query, 1, hash, -1, NULL);
	sqlite3_step(query);

	sqlite3_finalize(query);

	return sqlite3_last_insert_rowid(books_db);
}

int64_t reader_books_db_get_index_by_hash(APP* app, const char* hash)
{
	g_return_val_if_fail(app != NULL,		EXIT_FAILURE);
	g_return_val_if_fail(hash != NULL,		EXIT_FAILURE);

	sqlite3* books_db			= app->books_db;
	sqlite3_stmt* query			= NULL;
	int64_t index				= -1;

	sqlite3_prepare(books_db, "SELECT rowid FROM books WHERE hash IS ?;", -1, &query, NULL);
	sqlite3_bind_text(query, 1, hash, -1, NULL);
	if(sqlite3_step(query) == SQLITE_ROW)
		index = sqlite3_column_int64(query, 0);

	sqlite3_finalize(query);

	return index;
}


//##################################################################################################

int reader_books_db_get_int_by_index(APP* app, int64_t index, const char* param)
{
	g_return_val_if_fail(app != NULL,		EXIT_FAILURE);
	g_return_val_if_fail(param != NULL,		EXIT_FAILURE);

	sqlite3* books_db			= app->books_db;
	sqlite3_stmt* query			= NULL;
	int value					= 0;
	char buff[512];

	snprintf(buff, sizeof(buff), "SELECT %s FROM books WHERE rowid IS ?;", param);

	if(sqlite3_prepare(books_db, buff, -1, &query, NULL) != SQLITE_OK)
	{
		g_warning("Failed to get row from books table. %s", sqlite3_errmsg(books_db));
		return EXIT_FAILURE;
	}

	sqlite3_bind_int64(query, 1, index);

	if(sqlite3_step(query) == SQLITE_ROW)
		value = sqlite3_column_int(query, 0);

	sqlite3_finalize(query);

	return value;
}

int reader_books_db_set_int_by_index(APP* app, int64_t index, const char* param, int value)
{
	g_return_val_if_fail(app != NULL,		EXIT_FAILURE);
	g_return_val_if_fail(param != NULL,		EXIT_FAILURE);

	sqlite3* books_db			= app->books_db;
	sqlite3_stmt* query			= NULL;
	char buff[512];

	snprintf(buff, sizeof(buff), "UPDATE books SET %s=? WHERE rowid IS ?;", param);

	if(sqlite3_prepare(books_db, buff, -1, &query, NULL) != SQLITE_OK)
	{
		g_warning("Failed to update row from books table. %s", sqlite3_errmsg(books_db));
		return EXIT_FAILURE;
	}

	sqlite3_bind_int(query, 1, value);
	sqlite3_bind_int64(query, 2, index);

	sqlite3_step(query);

	sqlite3_finalize(query);

	return EXIT_SUCCESS;
}
