#include "../fb2_chunks.h"

#define READ_CHUNK_SIZE 1024

int parse_book_binary(xmlNode* node, GHashTable* binary_table)
{
	assert(node != NULL);
	assert(binary_table != NULL);

	char* image_id = NULL;
	xmlAttr* properties = node->properties;

	while(properties != NULL)
	{
		if((properties->type == XML_ATTRIBUTE_NODE) && (strcmp((char*)properties->name, "id") == 0))
		{
			image_id = (char*)properties->children->content;
			break;
		}

		properties = properties->next;
	}

	//***********************************************************************************************************

	guchar out_buff[(READ_CHUNK_SIZE/4)*3];

	char tmp_image_name[128];
	pid_t cur_pid = getpid();
	snprintf(tmp_image_name, sizeof(tmp_image_name), "/tmp/simple-fb2-reader-%d", cur_pid);

	FILE* f = fopen(tmp_image_name, "wb");

	char* image_data	= (char*)node->children->content;
	ssize_t data_len	= strlen(image_data);

	gint state = 0;
	guint save = 0;

	while(data_len > 0)
	{
		size_t count = (data_len > READ_CHUNK_SIZE)? READ_CHUNK_SIZE : data_len;
		size_t buff_pos = g_base64_decode_step(image_data, count, out_buff, &state, &save);

		fwrite(out_buff, 1, buff_pos, f);

		image_data	+= READ_CHUNK_SIZE;
		data_len	-= READ_CHUNK_SIZE;

	}

	fclose(f);

	GdkPixbuf* pixbuf = gdk_pixbuf_new_from_file(tmp_image_name, NULL);
	if(pixbuf == NULL)
		fprintf(stderr, "Failed to parse image(%s) from file\n", image_id);
	else
		g_hash_table_insert(binary_table, image_id, pixbuf);

	remove(tmp_image_name);

	return 0;
}
