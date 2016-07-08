#include "../FictionBook_chunks.h"

#define READ_CHUNK_SIZE 1024
int get_pixbuf_from_base64(char* base64, GdkPixbuf** pixbuf);

int parse_fb2_book_binary(APP* app, xmlNode* parent_node)
{
	g_return_val_if_fail(parent_node	!= NULL, EXIT_FAILURE);

	GHashTable* binary_hash_table	= app->binary_hash_table;

	const char* id_attr				= NULL;
	parse_fb2_attribute(app, parent_node, "id", &id_attr);

	if(id_attr != NULL)
	{
		if(g_hash_table_contains(binary_hash_table, id_attr) == FALSE)
		{
			if(parent_node->children != NULL)
			{
				char* image_data = (char*)parent_node->children->content;

				if(image_data != NULL)
				{
					GdkPixbuf* pixbuf = NULL;

					get_pixbuf_from_base64(image_data, &pixbuf);

					if(pixbuf != NULL)
					{
						char* id_dup = g_strdup(id_attr);
						g_hash_table_insert(binary_hash_table, id_dup, pixbuf);
					}
				}
			}
			else
				g_warning("No content in <image> tag");
		}
		else
			g_warning("Image %s already exist in table", id_attr);
	}
	else
		g_warning("No id properties in <image> tag");

	return EXIT_SUCCESS;
}


int get_pixbuf_from_base64(char* base64, GdkPixbuf** pixbuf)
{
	g_return_val_if_fail(pixbuf	!= NULL, EXIT_FAILURE);
	g_return_val_if_fail(base64	!= NULL, EXIT_FAILURE);

	guchar out_buff[(READ_CHUNK_SIZE/4)*3];

	GdkPixbufLoader* loader = gdk_pixbuf_loader_new();
	GError* loader_error = NULL;
	gboolean has_error = FALSE;

	char* image_data	= base64;
	size_t data_len		= strlen(image_data);
	size_t position		= 0;

	gint state = 0;
	guint save = 0;

	while(data_len > position)
	{
		size_t count = (position+READ_CHUNK_SIZE < data_len)? READ_CHUNK_SIZE : data_len%1024;

		size_t bytes_count = g_base64_decode_step(image_data, count, out_buff, &state, &save);

		if(gdk_pixbuf_loader_write(loader, out_buff, bytes_count, &loader_error) == FALSE)
		{
			g_error("GdkPixbufLoader: %s", loader_error->message);
			g_error_free(loader_error);
			has_error = TRUE;

			break;
		}

		image_data	+= READ_CHUNK_SIZE;
		position	+= READ_CHUNK_SIZE;

	}

	gdk_pixbuf_loader_close(loader, &loader_error);

	if(loader_error != NULL)
	{
		g_error("GdkPixbufLoader: %s", loader_error->message);
		g_error_free(loader_error);
		has_error = TRUE;
	}

	if(has_error == FALSE)
	{
		*pixbuf	= gdk_pixbuf_loader_get_pixbuf(loader);
		g_object_ref(*pixbuf);
	}

	g_object_unref(loader);

	return EXIT_SUCCESS;
}
