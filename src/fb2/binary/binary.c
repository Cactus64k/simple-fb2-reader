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

	GdkPixbufLoader* loader = gdk_pixbuf_loader_new();

	guchar out_buff[(READ_CHUNK_SIZE/4)*3];

	char* image_data	= (char*)node->children->content;
	ssize_t data_len	= strlen(image_data);

	gint state = 0;
	guint save = 0;

	while(data_len > 0)
	{
		size_t count = (data_len > READ_CHUNK_SIZE)? READ_CHUNK_SIZE : data_len;
		size_t bytes_count = g_base64_decode_step(image_data, count, out_buff, &state, &save);

		if(gdk_pixbuf_loader_write(loader, out_buff, bytes_count, NULL) == false)
		{
			fprintf(stderr, "failed to parse image %s\n", image_id);
			break;
		}

		image_data	+= READ_CHUNK_SIZE;
		data_len	-= READ_CHUNK_SIZE;

	}

	GdkPixbuf* pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);
	if(pixbuf != NULL)
	{
		g_object_ref(pixbuf);		// почему то добавление в хеш таблицу не увеличивает счетчик ссылок
		g_hash_table_insert(binary_table, image_id, pixbuf);
	}
	else
		fprintf(stderr, "failed to get image %s from pixbuf loader\n", image_id);

	gdk_pixbuf_loader_close(loader, NULL);
	g_object_unref(G_OBJECT(loader));

	return 0;
}
