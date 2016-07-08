#ifndef CHUNKS_H_
#define CHUNKS_H_

	#include "config.h"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <stddef.h>
	#include <assert.h>
	#include <locale.h>
	#include <string.h>
	#include <stdint.h>

	#include <libxml/parser.h>
	#include <libxml/tree.h>
	#include <libintl.h>
	#include <gtk/gtk.h>
	#include <zip.h>
	#include <sqlite3.h>

	#define _C(str) gettext(str)

	#ifdef DEBUG
		#undef GUI_CONSTRUCT_PATH
		#define GUI_CONSTRUCT_PATH "./res/simple-fb2-reader.glade"
	#endif


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
	} BOOK_TYPE;

	typedef struct SEARCH_WINDOW
	{
		GtkWidget*				search_wnd;
		GtkEntry*				search_query_entry;
		GtkTextIter*			last_pos;
		GtkCheckButton*			case_sensitive;
		GtkRadioButton*			forward;
		GtkRadioButton* 		backward;
	} SEARCH_WINDOW;

	typedef struct APP
	{
		GtkTextBuffer*			text_buff;
		GtkTextView*			text_view;

		sqlite3*				books_db;

		BOOK_TYPE				book_type;
		char*					book_path;
		GHashTable*				binary_hash_table;
		GHashTable*				links_hash_table;
		GList*					link_jump_list;
		GtkTreeStore*			sections_treestore;
		int64_t					book_index;

		GtkWidget*				main_wnd;

		SEARCH_WINDOW			search_window;

		GtkTreeView*			sections_treeview;
		GtkDialog*				navigation_dialog;

		GtkFileChooserDialog*	filechooserdialog;
		GtkAboutDialog*			about_dialog;
		GtkMessageDialog*		error_messagedialog;

		GdkCursor*				cursor_link;
		GdkCursor*				cursor_watch;

		GtkClipboard* 			clipboard;

		GKeyFile*				app_config;
		char*					app_config_path;

		gboolean				auto_scroll;
		double					auto_scroll_divider;

	} APP;

	#include "formats/formats_chunks.h"
	#include "callbacks/callbacks_chunk.h"
	#include "reader/reader_chunks.h"

#endif /* CHUNKS_H_ */
