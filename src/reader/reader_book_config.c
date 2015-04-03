#include "reader_chunks.h"

int reader_load_book_config(FB2_READER_BOOK_VIEW* obj, char* file_path)
{
	g_return_val_if_fail(file_path != NULL, -1);
	g_return_val_if_fail(obj != NULL, -2);

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

		char* config_path		= g_strdup_printf("%s/simple-fb2-reader/books/%s", conf_dir, book_hash);
		GKeyFile* config		= g_key_file_new();

		g_key_file_load_from_file(config, config_path, G_KEY_FILE_NONE, NULL);

		if(g_key_file_has_key(config, "book",				"read_line", NULL) == FALSE)
			g_key_file_set_integer(config, "book",			"read_line", 0);

		if(g_key_file_has_key(config, "book",				"read_line_offset", NULL) == FALSE)
			g_key_file_set_integer(config, "book",			"read_line_offset", 0);

		g_checksum_free(chsum);

		obj->config			= config;
		obj->config_path	= config_path;

		return 0;
	}

	return 1;
}
