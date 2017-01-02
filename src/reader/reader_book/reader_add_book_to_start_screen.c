#include "reader_book_chunks.h"

int reader_get_recent_books_count(APP* app)
{
	sqlite3* db			= app->book_db;
	sqlite3_stmt* query	= NULL;
	int books_count		= 0;

	sqlite3_prepare(db, "SELECT count(rowid) FROM recent_books_ring;", -1, &query, NULL);
	if(sqlite3_step(query) != SQLITE_ERROR)
		books_count = sqlite3_column_int(query, 0);
	sqlite3_finalize(query);
	return books_count;
}

gboolean reader_book_exist_in_table(APP* app, const char* book_hash)
{
	sqlite3* db			= app->book_db;
	sqlite3_stmt* query	= NULL;
	gboolean status		= FALSE;

	sqlite3_prepare(db, "SELECT rowid FROM recent_books_ring WHERE hash IS ?;", -1, &query, NULL);
	sqlite3_bind_text(query, 1, book_hash, -1, NULL);
	if(sqlite3_step(query) == SQLITE_ROW)
		status = TRUE;
	sqlite3_finalize(query);
	return status;
}



int reader_add_book_to_start_screen(APP* app, const char* book_title, const char* book_hash, const char* book_path)
{
	sqlite3* db					= app->book_db;
	int status					= EXIT_SUCCESS;

	if(reader_book_exist_in_table(app, book_hash) == TRUE)
	{
		sqlite3_stmt* query	= NULL;

		sqlite3_prepare(db, "UPDATE recent_books_ring SET path = ? WHRERE hash IS ?;", -1, &query, NULL);
		sqlite3_bind_text(query, 1, book_path, -1, NULL);
		sqlite3_bind_text(query, 2, book_hash, -1, NULL);
		if(sqlite3_step(query) == SQLITE_ERROR)
		{
			g_log(NULL, G_LOG_LEVEL_WARNING, "Failed to update book in recent_books_ring: %s", sqlite3_errmsg(db));
			status = EXIT_FAILURE;
		}
		sqlite3_finalize(query);
	}
	else
	{
		if(reader_get_recent_books_count(app) >= 5)
		{
			sqlite3_stmt* query	= NULL;

			sqlite3_prepare(db, "UPDATE recent_books_ring SET name = ?, hash = ?, path = ?, time = ? WHERE time == (SELECT MIN(time) FROM recent_books_ring);", -1, &query, NULL);
			sqlite3_bind_text(query,	1, book_title,	-1, NULL);
			sqlite3_bind_text(query,	2, book_hash,	-1, NULL);
			sqlite3_bind_text(query,	3, book_path,	-1, NULL);
			sqlite3_bind_int64(query,	4, time(NULL));

			if(sqlite3_step(query) == SQLITE_ERROR)
			{
				g_log(NULL, G_LOG_LEVEL_WARNING, "Failed to update books in recent_table_ring: %s", sqlite3_errmsg(db));
				status = EXIT_FAILURE;
			}
			sqlite3_finalize(query);
		}
		else
		{
			sqlite3_stmt* query	= NULL;

			sqlite3_prepare(db, "INSERT INTO recent_books_ring VALUES(?, ?, ?, ?);", -1, &query, NULL);
			sqlite3_bind_text(query,	1, book_title,	-1, NULL);
			sqlite3_bind_text(query,	2, book_hash,	-1, NULL);
			sqlite3_bind_text(query,	3, book_path,	-1, NULL);
			sqlite3_bind_int64(query,	4, time(NULL));
			if(sqlite3_step(query) == SQLITE_ERROR)
			{
				g_log(NULL, G_LOG_LEVEL_WARNING, "Failed add books in recent_table_ring: %s", sqlite3_errmsg(db));
				status = EXIT_FAILURE;
			}
			sqlite3_finalize(query);
		}
	}


	return status;
}
