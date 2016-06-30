#include "reader_chunks.h"

char* reader_get_book_hash(APP* app, char* file_path)
{
	g_return_val_if_fail(file_path != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(app != NULL,		EXIT_FAILURE);

	char* hash_out	= NULL;
	FILE* f			= fopen(file_path, "rb");
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
		hash_out				= g_strdup(book_hash);

		g_checksum_free(chsum);
	}

	return hash_out;
}
