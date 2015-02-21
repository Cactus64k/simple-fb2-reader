#include "../chunks.h"

void encode_treeview_cursor_changed_cb(GtkTreeView* tree_view, gpointer user_data)
{
	GtkTreeSelection* tree_selection	= gtk_tree_view_get_selection(tree_view);
	GtkTreeModel* tree_model			= GTK_TREE_MODEL(GLOBAL_ENCODE_DIALOG.treestore);
	GtkTextBuffer* text_buffer			= GLOBAL_ENCODE_DIALOG.textbuffer;
	char* src_buffer					= GLOBAL_ENCODE_DIALOG.src_buffer;
	char* dst_buffer					= GLOBAL_ENCODE_DIALOG.dst_buffer;
	size_t dst_buff_size				= sizeof(GLOBAL_ENCODE_DIALOG.dst_buffer);
	size_t buffer_data_size				= GLOBAL_ENCODE_DIALOG.buffer_data_size;

	GtkTreeIter tree_iter;
	gboolean is_encode = FALSE;

	if(gtk_tree_selection_get_selected(tree_selection, NULL, &tree_iter) == TRUE)
	{
		gtk_tree_model_get(tree_model, &tree_iter, IS_ENCODE_COLUMN, &is_encode, -1);
		if(is_encode == TRUE)
		{
			char* encode_name = NULL;
			gtk_tree_model_get(tree_model, &tree_iter, ENCODE_NAME_COLUMN, &encode_name, -1);


			iconv_t cd = iconv_open("UTF-8", encode_name);

			char* in_buff	= src_buffer;
			char* out_buff	= dst_buffer;

			size_t src_buff_left = buffer_data_size;
			size_t dst_buff_left = dst_buff_size;

			size_t res = iconv(cd,	&in_buff,	&src_buff_left,
												&out_buff,	&dst_buff_left);
			if(res == (size_t)-1)
			{
				char* error_text = strerror(errno);
				fprintf(stderr, "TXT encode error: %s\n", error_text);
			}
			else
				gtk_text_buffer_set_text(text_buffer, dst_buffer, (dst_buff_size-dst_buff_left));



			iconv_close(cd);

			g_free(encode_name);
		}

	}
}


