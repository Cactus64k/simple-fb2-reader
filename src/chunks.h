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
	#define ENCODE_LIST_PATH "/etc/simple-fb2-reader_encoding_list.cfg"
	#define ENCODE_BUFF_SIZE 1024

	enum
	{
		SECTION_NAME_COLUMN = 0,
		SECTION_STRING_COLUMN
	};

	typedef enum
	{
		BOOK_TYPE_NONE = 0,
		BOOK_TYPE_FB2,
		BOOK_TYPE_FB2_ZIP,
		BOOK_TYPE_TXT
	} BOOK_TYPE;

	typedef struct FB2_READER_SEARCH_WINDOW
	{
		GtkWidget*		search_wnd;
		GtkEntry*		search_query_entry;
		GtkTextIter		last_pos;
		GtkCheckButton*	case_sensitive;
		GtkRadioButton*	forward;
		GtkRadioButton* backward;
	} FB2_READER_SEARCH_WINDOW;

	typedef struct FB2_READER_ENCODE_DIALOG
	{
		GtkDialog*		dialog;
		GtkTreeView*	treeview;
		GtkListStore*	liststore;
		GtkTextBuffer*	textbuffer;

		char			src_text[ENCODE_BUFF_SIZE];
		size_t			src_text_size;
	} FB2_READER_ENCODE_DIALOG;

	typedef struct FB2_READER_BOOK_VIEW
	{
		GtkTextBuffer*			text_buff;
		GtkTextView*			text_view;

		GtkTreeStore*			sections_treestore;		// REFACTORING

		GHashTable*				binary_hash_table;
		GHashTable*				links_hash_table;

		GKeyFile*				config;
		char*					config_path;

		BOOK_TYPE				type;

		char*					path;

	} FB2_READER_BOOK_VIEW;

	typedef struct FB2_READER
	{
		GtkWidget*				main_wnd;

		GtkCheckMenuItem*		color_check_item;

		FB2_READER_BOOK_VIEW	book_text_view;
		GtkTreeView*			sections_treeview;

		GtkFileChooserDialog*	filechooserdialog;
		GtkDialog*				navigation_dialog;
		GtkDialog*				notes_dialog;
		GtkAboutDialog*			about_dialog;
		GtkMessageDialog*		save_dialog;

		GdkCursor*				link_cursor;
		GdkCursor*				def_cursor;

		GtkClipboard* 			clipboard;

		GKeyFile*				app_config;
		char*					app_config_path;

	} FB2_READER;

	FB2_READER_ENCODE_DIALOG	GLOBAL_ENCODE_DIALOG;
	FB2_READER					GLOBAL_FB2_READER;
	FB2_READER_SEARCH_WINDOW	GLOBAL_SEARCH_WND;

	int create_fb2_tags(FB2_READER* obj);
	int create_config_dir();
	int init_main_reader_book_view(GtkBuilder* builder, FB2_READER* obj0);

	int reader_open_book(char* file_path);
	int reader_close_book();
	int reader_close_app();
	int get_book_config(char* file_path, GKeyFile** book_config, char** book_config_path);
	gboolean test_file_type(char* file_path, const char* file_ext);
	int get_scroll_line_offset(GtkTextView* text_view, gint* line, gint* offset);

	int init_main_wnd(GtkBuilder* builder, FB2_READER* obj);
	int init_search_wnd(GtkBuilder* builder, FB2_READER_SEARCH_WINDOW* obj);
	int init_encode_wnd(GtkBuilder* builder, FB2_READER_ENCODE_DIALOG* obj);
	int init_app_config(FB2_READER* obj);


	#include "fb2/fb2_chunks.h"
	#include "txt/txt_chunks.h"
	#include "fb2_zip/fb2_zip_chunks.h"

#endif /* CHUNKS_H_ */
