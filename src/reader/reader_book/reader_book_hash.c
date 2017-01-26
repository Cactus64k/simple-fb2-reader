#include "reader_book_chunks.h"

char* reader_get_book_hash(char* file_path)
{
	g_return_val_if_fail(file_path != NULL,	NULL);

	char* hash_out	= NULL;
	FILE* f			= fopen(file_path, "rb");
	if(f != NULL)
	{
		GChecksum* chsum = g_checksum_new(G_CHECKSUM_SHA1);
		char buff[1024];

		while(!feof(f))
		{
			size_t read_count = fread(buff, 1, sizeof(buff), f);

			g_checksum_update(chsum, (const unsigned char*)buff, (gssize)read_count);
		}

		fclose(f);

		const char* book_hash	= g_checksum_get_string(chsum);
		hash_out				= g_strdup(book_hash);

		g_checksum_free(chsum);
	}

	return hash_out;
}
