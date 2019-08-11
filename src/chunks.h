#ifndef CHUNKS_H_
#define CHUNKS_H_

	//#include "config.h"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <stddef.h>
	#include <assert.h>
	#include <locale.h>
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

	#ifndef PACKAGE_NAME
		#define PACKAGE_NAME "simple-fb2-reader"
	#endif

	#ifndef PACKAGE_VERSION
		#define PACKAGE_VERSION "1.0.0"
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
		GtkTextIter				last_pos;
		GtkCheckButton*			case_sensitive;
		GtkRadioButton*			forward;
	} SEARCH_WINDOW;

	typedef struct APP
	{
		sqlite3*				book_db;
		BOOK_TYPE				book_type;
		char*					book_title;
		char*					book_hash;
		int64_t					book_index;
		GList*					book_jump_list;
		GHashTable*				book_id_table;
		GHashTable*				book_img_table;

		SEARCH_WINDOW			search_window;

		GtkWidget*				main_wnd;

		GtkTextBuffer*			text_buff;
		GtkTextView*			text_view;
		GtkScrolledWindow*		text_scrolledwindow;

		GtkTreeStore*			sections_treestore;
		GtkTreeView*			sections_treeview;
		GtkDialog*				navigation_dialog;

		GtkFileChooserDialog*	filechooserdialog;
		GtkAboutDialog*			about_dialog;

		GdkCursor*				cursor_link;
		GdkCursor*				cursor_watch;

		GtkClipboard* 			clipboard;

		GKeyFile*				app_config;
		char*					app_config_path;

		char*					app_css_path;

		gboolean				auto_scroll;
		int						auto_scroll_period;

	} APP;

	#include "reader/reader_chunks.h"
	#include "formats/formats_chunks.h"
	#include "callbacks/callbacks_chunk.h"

#endif /* CHUNKS_H_ */
