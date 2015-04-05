#include "callbacks_chunk.h"

void encode_treeview_cursor_changed_cb(GtkTreeView* tree_view, gpointer user_data)
{
	GtkTreeSelection* tree_selection	= gtk_tree_view_get_selection(tree_view);
	GtkTreeModel* tree_model			= GTK_TREE_MODEL(GLOBAL_ENCODE_DIALOG.liststore);
	GtkTextBuffer* text_buffer			= GLOBAL_ENCODE_DIALOG.textbuffer;
	char* src_buffer					= GLOBAL_ENCODE_DIALOG.src_text;
	char dst_buffer[6*ENCODE_BUFF_SIZE];
	size_t dst_buff_size				= sizeof(dst_buffer);
	size_t buffer_data_size				= GLOBAL_ENCODE_DIALOG.src_text_size;

	GtkTreeIter tree_iter;

	if(gtk_tree_selection_get_selected(tree_selection, NULL, &tree_iter) == TRUE)
	{
		char* encode_name = NULL;
		gtk_tree_model_get(tree_model, &tree_iter, 0, &encode_name, -1);

		iconv_t cd = iconv_open("UTF-8", encode_name);

		char* in_buff	= src_buffer;
		char* out_buff	= dst_buffer;

		size_t src_buff_left = buffer_data_size;
		size_t dst_buff_left = dst_buff_size;

		size_t res = iconv(cd,	&in_buff,	&src_buff_left,
											&out_buff,	&dst_buff_left);
		if(res == (size_t)-1)
			gtk_text_buffer_set_text(text_buffer, _C("WRONG ENCODE"), -1);
		else
		{
			if(g_utf8_validate(dst_buffer, (dst_buff_size-dst_buff_left), NULL) == TRUE)
				gtk_text_buffer_set_text(text_buffer, dst_buffer, (dst_buff_size-dst_buff_left));
			else
				gtk_text_buffer_set_text(text_buffer, _C("WRONG ENCODE"), -1);
		}


		iconv_close(cd);

		g_free(encode_name);

	}
}

void txt_encode_dialog_show_cb(GtkWidget *widget, gpointer user_data)
{
	char* file_path			= GLOBAL_FB2_READER.book_text_view.path;
	char* src_text			= GLOBAL_ENCODE_DIALOG.src_text;
	size_t* src_text_size	= &(GLOBAL_ENCODE_DIALOG.src_text_size);

	FILE* f = fopen(file_path, "rb");
	*src_text_size = fread(src_text, 1, sizeof(GLOBAL_ENCODE_DIALOG.src_text), f);
	fclose(f);
}


