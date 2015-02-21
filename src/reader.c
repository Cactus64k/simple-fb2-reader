#include "chunks.h"

void text_tag_foreach_remove(GtkTextTag* tag, gpointer data);


int reader_open_book(char* file_path)
{
	GtkDialog* encode_dialog			= GLOBAL_ENCODE_DIALOG.dialog;
	GtkTreeView* sections_treeview		= GLOBAL_FB2_READER.book_text_view.sections_treeview;

	char* file_type = strrchr(file_path, '.');
	if(file_type != NULL)
	{
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
			assert(conf_dir != NULL);

			char* book_config_path		= g_strdup_printf("%s/simple-fb2-reader/books/%s", conf_dir, book_hash);
			GKeyFile* book_config		= g_key_file_new();

			if(g_key_file_load_from_file(book_config, book_config_path, G_KEY_FILE_NONE, NULL) == FALSE)
			{
				g_key_file_set_int64(book_config, "book", "read_line", 0);
				g_key_file_set_int64(book_config, "book", "read_line_offset", 0);
			}


			GLOBAL_FB2_READER.book_config		= book_config;
			GLOBAL_FB2_READER.book_config_path	= book_config_path;

			g_checksum_free(chsum);

			//###########################################################################################################

			if(strcmp(file_type, ".txt") == 0)
			{
				char* encode_name = g_key_file_get_string(GLOBAL_FB2_READER.book_config, "book", "encode", NULL);
				if(encode_name != NULL)
					parse_txt(file_path, encode_name);
				else
				{
					if(gtk_dialog_run(encode_dialog) == 2)
					{
						encode_name = encode_dialog_get_encode_name(&GLOBAL_ENCODE_DIALOG);
						if(encode_name != NULL)
						{
							g_key_file_set_string(GLOBAL_FB2_READER.book_config, "book", "encode", encode_name);

							parse_txt(file_path, encode_name);
						}
						g_free(encode_name);

					}
					gtk_widget_hide(GTK_WIDGET(encode_dialog));
				}
			}
			else if(strcmp(file_type, ".fb2") == 0)
			{
				parse_fb2(file_path);
				gtk_tree_view_expand_all(sections_treeview);
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
			fprintf(stderr, "Error reading file: %s\n", file_path);
	}
	else
		fputs("wrong file name\n", stderr);

	return 0;
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

	gint read_line			= 0;
	gint read_line_offset	= 0;

	get_scroll_line_offset(text_view, &read_line, &read_line_offset);

	g_key_file_set_int64(book_config, "book", "read_line", read_line);
	g_key_file_set_int64(book_config, "book", "read_line_offset", read_line);

	char* book_config_data = g_key_file_to_data(book_config, NULL, NULL);
	FILE* f = fopen(book_config_path, "wb");
	fputs(book_config_data, f);
	fclose(f);
	g_free(book_config_data);

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

	g_key_file_free(book_config);
	GLOBAL_FB2_READER.book_config		= NULL;

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
	gint scroll_pos		= gtk_adjustment_get_value(adj);

	gtk_text_view_get_iter_at_location(text_view, &scroll_iter, 0, scroll_pos);

	*line	= gtk_text_iter_get_line(&scroll_iter);
	*offset	= gtk_text_iter_get_line_offset(&scroll_iter);

	return 0;
}
