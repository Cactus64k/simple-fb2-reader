#include "../FictionBook_chunks.h"

#define READ_CHUNK_SIZE 1024
int get_pixbuf_from_base64(char* base64, GdkPixbuf** pixbuf);

int parse_fb2_book_binary(APP* app, xmlNode* parent_node)
{
	g_return_val_if_fail(parent_node	!= NULL, EXIT_FAILURE);

	GHashTable* book_img_table		= app->book_img_table;
	char* id_attr					= (char*)xmlGetProp(parent_node, (xmlChar*)"id");;

	if(id_attr != NULL)
	{
		if(g_hash_table_contains(book_img_table, id_attr) == FALSE)
		{
			if(parent_node->children != NULL)
			{
				char* image_data = (char*)xmlNodeGetContent(parent_node);

				if(image_data != NULL)
				{
					GdkPixbuf* pixbuf = NULL;

					get_pixbuf_from_base64(image_data, &pixbuf);

					if(pixbuf != NULL)
					{
						char* id_dup = g_strdup(id_attr);
						g_hash_table_insert(book_img_table, id_dup, pixbuf);
					}
				}

				xmlFree(image_data);
			}
			else
				g_log(NULL, G_LOG_LEVEL_WARNING, "No content in <image> tag");
		}
		else
			g_log(NULL, G_LOG_LEVEL_WARNING, "Image %s already exist in table", id_attr);
	}
	else
		g_log(NULL, G_LOG_LEVEL_WARNING, "No id properties in <image> tag");

	xmlFree(id_attr);

	return EXIT_SUCCESS;
}


int get_pixbuf_from_base64(char* base64, GdkPixbuf** pixbuf)
{
	g_return_val_if_fail(pixbuf	!= NULL, EXIT_FAILURE);
	g_return_val_if_fail(base64	!= NULL, EXIT_FAILURE);

	guchar* out_buff		= g_malloc((READ_CHUNK_SIZE/4)*3 + 3);
	GdkPixbufLoader* loader	= gdk_pixbuf_loader_new();
	GError* loader_error	= NULL;
	gboolean has_error		= FALSE;
	char* image_data		= base64;
	size_t data_len			= strlen(image_data);
	size_t position			= 0;
	gint state				= 0;
	guint save				= 0;


	while(data_len > position)
	{
		size_t in_count		= (position+READ_CHUNK_SIZE < data_len)? READ_CHUNK_SIZE : data_len%READ_CHUNK_SIZE;
		in_count			= (in_count == 0)? READ_CHUNK_SIZE : in_count;

		size_t out_count	= g_base64_decode_step(image_data, in_count, out_buff, &state, &save);

		if(gdk_pixbuf_loader_write(loader, out_buff, out_count, &loader_error) == FALSE)
		{
			g_log(NULL, G_LOG_LEVEL_ERROR, "GdkPixbufLoader: %s", loader_error->message);
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
		g_log(NULL, G_LOG_LEVEL_WARNING, "GdkPixbufLoader: %s", loader_error->message);
		g_error_free(loader_error);
		has_error = TRUE;
	}

	if(has_error == FALSE)
	{
		*pixbuf	= gdk_pixbuf_loader_get_pixbuf(loader);
		g_object_ref(*pixbuf);
	}

	g_object_unref(loader);
	g_free(out_buff);

	return EXIT_SUCCESS;
}
