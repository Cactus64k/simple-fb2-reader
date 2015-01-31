#ifndef CHUNKS_H_
#define CHUNKS_H_

	#include <stdlib.h>
	#include <stdio.h>
	#include <stdbool.h>
	#include <string.h>
	#include <stddef.h>
	#include <errno.h>
	#include <assert.h>
	#include <libxml/parser.h>
	#include <libxml/tree.h>
	#include <locale.h>
	#include <string.h>
	#include <libintl.h>
	#include <stdint.h>
	#include <gtk/gtk.h>

	enum
	{
		SECTION_NUM_COLUMN = 0,
		SECTION_NAME_COLUMN
	};

	enum
	{
		IS_ENCODE_COLUMN = 0,
		ENCODE_NAME_COLUMN
	};

	typedef struct SEARCH_WINDOW
	{
		GtkWidget*		search_wnd;
		bool			entry_edited;
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

	typedef struct FB2_READER
	{
		GtkWidget*				main_wnd;
		GtkTextBuffer*			text_buff;
		GtkTextView*			text_view;
		GtkFileChooserDialog*	filechooserdialog;
		GtkDialog*				navigation_dialog;
		GtkListStore*			sections_liststore;

		GtkTextTag*				default_tag;
		GtkTextTag*				title_tag;
		GtkTextTag*				strong_tag;
		GtkTextTag*				sub_tag;
		GtkTextTag*				strikethrough_tag;
		GtkTextTag*				sup_tag;
		GtkTextTag*				emphasis_tag;
		GtkTextTag*				code_tag;
		GtkTextTag*				subtitle_tag;
		GtkTextTag*				image_tag;
		GtkTextTag*				a_tag;
		GtkTextTag*				cite_tag;
		GtkTextTag*				text_author_tag;
		GtkTextTag*				epigraph_tag;
		GtkTextTag*				stanza_tag;

		GHashTable*				binary_hash_table;
		GHashTable*				links_hash_table;
		size_t					tag_table_default_size;
	} FB2_READER;

	#define EPIGRAPH_TAG_MARGIN 0.25f

	ENCODE_DIALOG	GLOBAL_ENCODE_DIALOG;
	FB2_READER		GLOBAL_FB2_READER;
	SEARCH_WINDOW	GLOBAL_SEARCH_WND;

	int open_book(char* file_path);

	int main_wnd_init(GtkBuilder* builder, FB2_READER* obj);
	int search_wnd_init(GtkBuilder* builder, SEARCH_WINDOW* obj);
	int encode_wnd_init(GtkBuilder* builder, ENCODE_DIALOG* obj);


	#include "fb2/fb2_chunks.h"
	#include "txt/txt_parser.h"

#endif /* CHUNKS_H_ */
