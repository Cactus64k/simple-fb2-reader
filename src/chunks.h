#ifndef CHUNKS_H_
#define CHUNKS_H_

	#include <stdlib.h>
	#include <stdio.h>
	//#include <stdbool.h>
	#include <string.h>
	#include <stddef.h>
	#include <errno.h>
	#include <assert.h>
	#include <locale.h>
	#include <string.h>
	#include <stdint.h>

	#include <sys/stat.h>
	#include <sys/types.h>

	#include <libxml/parser.h>
	#include <libxml/tree.h>

	#include <libintl.h>

	#include <gtk/gtk.h>

	#include <zip.h>

	#define _C(str) gettext(str)

	enum
	{
		SECTION_NAME_COLUMN = 0,
		SECTION_STRING_COLUMN
	};

	enum
	{
		IS_ENCODE_COLUMN = 0,
		ENCODE_NAME_COLUMN
	};

	typedef struct SEARCH_WINDOW
	{
		GtkWidget*		search_wnd;
		gboolean		entry_edited;
		GtkEntry*		search_query_entry;
		GtkTextIter		last_pos;
	} SEARCH_WINDOW;

	typedef struct ENCODE_DIALOG
	{
		GtkDialog*		dialog;
		GtkTreeView*	treeview;
		GtkTreeStore*	treestore;
		GtkTextBuffer*	textbuffer;
		size_t			buffer_data_size;
		char			src_buffer[1024];
		char			dst_buffer[1024*6];
	} ENCODE_DIALOG;

	typedef struct FB2_READER_TEXT_VIEW
	{
		GtkTextBuffer*			text_buff;
		GtkTextView*			text_view;

		gint					tag_table_default_size;

		GtkTreeStore*			sections_treestore;
		GtkTreeView*			sections_treeview;
		gboolean				save_section;


		GHashTable*				binary_hash_table;			// должно ссылаться на указатель в глобальном объекте ридера
		GHashTable*				links_hash_table;

	} FB2_READER_TEXT_VIEW;

	typedef struct FB2_READER
	{
		GtkWidget*				main_wnd;

		GtkCheckMenuItem*		color_check_item;

		FB2_READER_TEXT_VIEW	book_text_view;

		GtkFileChooserDialog*	filechooserdialog;
		GtkDialog*				navigation_dialog;
		GtkDialog*				notes_dialog;

		GdkCursor*				link_cursor;
		GdkCursor*				def_cursor;

		GtkClipboard* 			clipboard;

		GKeyFile*				app_config;
		char*					app_config_path;

		GKeyFile*				book_config;
		char*					book_config_path;

		GHashTable*				binary_hash_table;

	} FB2_READER;

	ENCODE_DIALOG	GLOBAL_ENCODE_DIALOG;
	FB2_READER		GLOBAL_FB2_READER;
	SEARCH_WINDOW	GLOBAL_SEARCH_WND;

	int create_fb2_tags(GtkTextBuffer* text_buff);
	int create_config_dir();
	int init_main_reader_text_view(GtkBuilder* builder, FB2_READER* obj0);

	int reader_open_book(char* file_path);
	int reader_close_book();
	int reader_close();
	gboolean test_file_type(char* file_path, const char* file_ext);
	int get_scroll_line_offset(GtkTextView* text_view, gint* line, gint* offset);

	int init_main_wnd(GtkBuilder* builder, FB2_READER* obj);
	int init_search_wnd(GtkBuilder* builder, SEARCH_WINDOW* obj);
	int init_encode_wnd(GtkBuilder* builder, ENCODE_DIALOG* obj);
	int init_app_config(FB2_READER* obj);


	#include "fb2/fb2_chunks.h"
	#include "txt/txt_chunks.h"
	#include "fb2_zip/fb2_zip_chunks.h"

#endif /* CHUNKS_H_ */
