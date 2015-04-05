#include "../callbacks_chunk.h"

void encode_imagemenuitem_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	BOOK_TYPE book_type					= GLOBAL_FB2_READER.book_text_view.type;
	char* book_path						= GLOBAL_FB2_READER.book_text_view.path;
	GtkTextBuffer* text_buff			= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkDialog* encode_dialog			= GLOBAL_ENCODE_DIALOG.dialog;
	GKeyFile* book_config				= GLOBAL_FB2_READER.book_text_view.config;

	GtkTreeView* tree_view				= GLOBAL_ENCODE_DIALOG.treeview;
	GtkTreeSelection* tree_selection	= gtk_tree_view_get_selection(tree_view);
	GtkTreeModel* tree_model			= GTK_TREE_MODEL(GLOBAL_ENCODE_DIALOG.liststore);

	if(book_type == BOOK_TYPE_TXT)
	{
		if(gtk_dialog_run(encode_dialog) == 2)
		{
			gtk_widget_hide(GTK_WIDGET(encode_dialog));

			GtkTreeIter tree_iter;
			char* encode_name = NULL;

			if(gtk_tree_selection_get_selected(tree_selection, NULL, &tree_iter) == TRUE)
			{
				gtk_tree_model_get(tree_model, &tree_iter, 0, &encode_name, -1);

				gtk_text_buffer_set_text(text_buff, "", 0);
				g_key_file_set_string(book_config, "book", "encode", encode_name);

				parse_txt(book_path, encode_name);
			}
			g_free(encode_name);

		}
		gtk_widget_hide(GTK_WIDGET(encode_dialog));

	}

}
