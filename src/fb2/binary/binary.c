#include "../fb2_chunks.h"

int parse_book_binary(xmlNode* node, GHashTable* binary_table)
{
	assert(node != NULL);
	assert(binary_table != NULL);

	gsize out_len = 0;
	unsigned char* image_b64 = g_base64_decode((char*)node->children->content, &out_len);

	char* image_id = NULL;
	xmlAttr* properties = node->properties;

	while(properties != NULL)
	{
		if(strcmp((char*)properties->name, "id") == 0)
		{
			image_id = (char*)properties->children->content;
			break;
		}

		properties = properties->next;
	}

	char* tmp_name = tmpnam(NULL);

	FILE* tmp_image = fopen(tmp_name, "w");
	assert(tmp_image != NULL);

	fwrite(image_b64, out_len, 1, tmp_image);
	fflush(tmp_image);

	GdkPixbuf* image = gdk_pixbuf_new_from_file(tmp_name, NULL);
	assert(image != NULL);

	g_hash_table_insert(binary_table, image_id, image);

	fclose(tmp_image);
	remove(tmp_name);
	g_free(image_b64);

	return 0;
}
