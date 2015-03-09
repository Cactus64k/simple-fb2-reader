#include "../chunks.h"

gboolean test_file_type(char* file_path, const char* file_ext);
int get_book_config(char* file_path, GKeyFile** book_config, char** book_config_path);

int reader_open_book(char* file_path)
{
	GtkDialog* encode_dialog			= GLOBAL_ENCODE_DIALOG.dialog;
	GtkTreeView* sections_treeview		= GLOBAL_FB2_READER.book_text_view.sections_treeview;
	GtkTextBuffer* text_buff			= GLOBAL_FB2_READER.book_text_view.text_buff;

	GKeyFile* book_config = NULL;
	char* book_config_path = NULL;

	//########################################################################################
	if(test_file_type(file_path, ".txt") == TRUE)
	{
		if(get_book_config(file_path, &book_config, &book_config_path) == 0)
		{
			GLOBAL_FB2_READER.book_text_view.config			= book_config;
			GLOBAL_FB2_READER.book_text_view.config_path	= book_config_path;
			GLOBAL_FB2_READER.book_text_view.type			= BOOK_TYPE_TXT;

			gtk_text_buffer_set_text(text_buff, "", 0);

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
		else
			fprintf(stderr, _C("ERROR: failed to open file: %s\n"), file_path);
	}
	//########################################################################################
	else if(test_file_type(file_path, ".fb2") == TRUE)
	{
		if(get_book_config(file_path, &book_config, &book_config_path) == 0)
		{
			GLOBAL_FB2_READER.book_text_view.config			= book_config;
			GLOBAL_FB2_READER.book_text_view.config_path	= book_config_path;
			GLOBAL_FB2_READER.book_text_view.type			= BOOK_TYPE_FB2;

			gtk_text_buffer_set_text(text_buff, "", 0);

			parse_fb2(file_path);
			gtk_tree_view_expand_all(sections_treeview);
		}
		else
			fprintf(stderr, _C("ERROR: failed to open file: %s\n"), file_path);
	}
	//########################################################################################
	else if(test_file_type(file_path, ".fb2.zip") == TRUE)
	{
		if(get_book_config(file_path, &book_config, &book_config_path) == 0)
		{
			GLOBAL_FB2_READER.book_text_view.config			= book_config;
			GLOBAL_FB2_READER.book_text_view.config_path	= book_config_path;
			GLOBAL_FB2_READER.book_text_view.type			= BOOK_TYPE_FB2_ZIP;

			gtk_text_buffer_set_text(text_buff, "", 0);

			parse_fb2_zip(file_path);

		}
		else
			fprintf(stderr, _C("ERROR: failed to open file: %s\n"), file_path);
	}
	//########################################################################################


	return 0;
}

int get_book_config(char* file_path, GKeyFile** book_config, char** book_config_path)
{
	g_return_val_if_fail(file_path != NULL, -1);
	g_return_val_if_fail(book_config != NULL, -2);

	*book_config = NULL;

	FILE* f = fopen(file_path, "rb");
	if(f != NULL)
	{
		GChecksum* chsum = g_checksum_new(G_CHECKSUM_SHA1);
		char buff[1024];

		while(!feof(f))
		{
			size_t read_count = fread(buff, 1, sizeof(buff), f);

			const unsigned char* buff_pointer = (unsigned char*)buff;
			g_checksum_update(chsum, buff_pointer, (gssize)read_count);
		}

		fclose(f);

		//###############################

		const char* book_hash	= g_checksum_get_string(chsum);
		const char* conf_dir	= g_get_user_config_dir();
		g_return_val_if_fail(conf_dir != NULL, -1);

		char* config_path			= g_strdup_printf("%s/simple-fb2-reader/books/%s", conf_dir, book_hash);
		GKeyFile* config			= g_key_file_new();

		g_key_file_load_from_file(config, config_path, G_KEY_FILE_NONE, NULL);

		if(g_key_file_has_key(config, "book",				"read_line", NULL) == FALSE)
			g_key_file_set_integer(config, "book",			"read_line", 0);

		if(g_key_file_has_key(config, "book",				"read_line_offset", NULL) == FALSE)
			g_key_file_set_integer(config, "book",			"read_line_offset", 0);

		g_checksum_free(chsum);

		*book_config		= config;
		*book_config_path	= config_path;

		return 0;
	}

	return 1;
}

gboolean test_file_type(char* file_path, const char* file_ext)
{
	size_t file_path_len = strlen(file_path);
	size_t file_ext_len	= strlen(file_ext);

	if(strcmp(file_ext, file_path + (file_path_len-file_ext_len)) == 0)
		return TRUE;

	return FALSE;
}
