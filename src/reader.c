#include "chunks.h"

void text_tag_foreach_remove(GtkTextTag* tag, gpointer data);

int reader_open_book(char* file_path)
{
	GtkDialog* encode_dialog			= GLOBAL_ENCODE_DIALOG.dialog;
	GtkTreeView* sections_treeview		= GLOBAL_FB2_READER.book_text_view.sections_treeview;

	GChecksum* chsum = g_checksum_new(G_CHECKSUM_SHA1);
	FILE* f = fopen(file_path, "rb");
	if(f != NULL)
	{
		char buff[1024];

		while(!feof(f))
		{
			size_t read_count = fread(buff, 1, sizeof(buff), f);

			const unsigned char* buff_pointer = (unsigned char*)buff;
			g_checksum_update(chsum, buff_pointer, (gssize)read_count);
		}

		fclose(f);

		const char* book_hash	= g_checksum_get_string(chsum);
		const char* conf_dir	= g_get_user_config_dir();
		g_return_val_if_fail(conf_dir != NULL, -1);

		char* book_config_path		= g_strdup_printf("%s/simple-fb2-reader/books/%s", conf_dir, book_hash);
		GKeyFile* book_config		= g_key_file_new();
		GError* key_file_error		= NULL;

		if(g_key_file_load_from_file(book_config, book_config_path, G_KEY_FILE_NONE, &key_file_error) == FALSE)
		{
			g_key_file_set_int64(book_config, "book", "read_line", 0);
			g_key_file_set_int64(book_config, "book", "read_line_offset", 0);

			fprintf(stderr, _C("ERROR: GKeyFile %s\n"), key_file_error->message);

			g_error_free(key_file_error);
		}


		GLOBAL_FB2_READER.book_config		= book_config;
		GLOBAL_FB2_READER.book_config_path	= book_config_path;

		g_checksum_free(chsum);

		//###########################################################################################################

		if(test_file_type(file_path, ".txt") == TRUE)
		{
			char* encode_name = g_key_file_get_string(book_config, "book", "encode", NULL);
			if(encode_name != NULL)
				parse_txt(file_path, encode_name);
			else
			{
				if(gtk_dialog_run(encode_dialog) == 2)
				{
					encode_name = encode_dialog_get_encode_name(&GLOBAL_ENCODE_DIALOG);
					if(encode_name != NULL)
					{
						g_key_file_set_string(book_config, "book", "encode", encode_name);

						parse_txt(file_path, encode_name);
					}
					g_free(encode_name);

				}
				gtk_widget_hide(GTK_WIDGET(encode_dialog));
			}
		}
		else if(test_file_type(file_path, ".fb2") == TRUE)
		{
			parse_fb2(file_path);
			gtk_tree_view_expand_all(sections_treeview);
		}
		else if(test_file_type(file_path, ".fb2.zip") == TRUE)
		{
			parse_fb2_zip(file_path);
		}
		else
		{
			g_key_file_free(GLOBAL_FB2_READER.book_config);
			GLOBAL_FB2_READER.book_config		= NULL;

			g_free(book_config_path);
			GLOBAL_FB2_READER.book_config_path	= NULL;
		}

	}
	else
		fprintf(stderr, _C("ERROR: failed to open file: %s\n"), file_path);

	return 0;
}

gboolean test_file_type(char* file_path, const char* file_ext)
{
	size_t file_path_len = strlen(file_path);
	size_t file_ext_len	= strlen(file_ext);

	if(strcmp(file_ext, file_path + (file_path_len-file_ext_len)) == 0)
		return TRUE;

	return FALSE;
}

int reader_close_book()
{
	GtkTreeStore* section_treestore		= GLOBAL_FB2_READER.book_text_view.sections_treestore;
	GHashTable* binary_hash_table		= *GLOBAL_FB2_READER.book_text_view.binary_hash_table;
	GHashTable* links_hash_table		= GLOBAL_FB2_READER.book_text_view.links_hash_table;
	GtkWidget* main_wnd					= GLOBAL_FB2_READER.main_wnd;
	GtkTextBuffer* text_buff			= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view				= GLOBAL_FB2_READER.book_text_view.text_view;
	GKeyFile* book_config				= GLOBAL_FB2_READER.book_config;
	char* book_config_path				= GLOBAL_FB2_READER.book_config_path;

	GtkTextIter text_buff_end_iter;
	GtkTextIter text_buff_start_iter;
	GtkTextTagTable* text_tag_table		= gtk_text_buffer_get_tag_table(text_buff);

	//############################################################################################

	if(book_config != NULL)
	{
		gint read_line			= 0;
		gint read_line_offset	= 0;

		get_scroll_line_offset(text_view, &read_line, &read_line_offset);

		g_key_file_set_int64(book_config, "book", "read_line", read_line);
		g_key_file_set_int64(book_config, "book", "read_line_offset", read_line_offset);

		gsize book_config_len	= 0;
		char* book_config_data	= g_key_file_to_data(book_config, &book_config_len, NULL);

		FILE* f = fopen(book_config_path, "wb");
		fwrite(book_config_data, 1, book_config_len,  f);
		fclose(f);
		g_free(book_config_data);
	}

	//############################################################################################

	//gtk_text_buffer_set_text(text_buff, "", -1);

	gtk_text_buffer_get_bounds(text_buff, &text_buff_start_iter, &text_buff_end_iter);
	gtk_text_buffer_delete(text_buff, &text_buff_start_iter, &text_buff_end_iter);

	gtk_text_tag_table_foreach(text_tag_table, text_tag_foreach_remove, text_tag_table);

	g_hash_table_remove_all(binary_hash_table);
	g_hash_table_remove_all(links_hash_table);

	gtk_window_set_title(GTK_WINDOW(main_wnd), "Simple FB2 reader");

	gtk_tree_store_clear(section_treestore);

	g_free(book_config_path);
	GLOBAL_FB2_READER.book_config_path	= NULL;

	if(book_config != NULL)
	{
		g_key_file_free(book_config);
		GLOBAL_FB2_READER.book_config		= NULL;
	}

	return 0;
}

void text_tag_foreach_remove(GtkTextTag* tag, gpointer data)
{
	GtkTextTagTable* text_tag_table = (GtkTextTagTable*)data;
	gint tag_table_default_size	= GLOBAL_FB2_READER.book_text_view.tag_table_default_size;

	gint priority = gtk_text_tag_get_priority(tag);
	if(priority >= tag_table_default_size)
		gtk_text_tag_table_remove(text_tag_table, tag);

}

int get_scroll_line_offset(GtkTextView* text_view, gint* line, gint* offset)
{
	GtkTextIter scroll_iter;
	GtkAdjustment* adj	= gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(text_view));
	gint scroll_pos		= (gint)gtk_adjustment_get_value(adj);

	gtk_text_view_get_iter_at_location(text_view, &scroll_iter, 0, scroll_pos);

	*line	= gtk_text_iter_get_line(&scroll_iter);
	*offset	= gtk_text_iter_get_line_offset(&scroll_iter);

	return 0;
}
