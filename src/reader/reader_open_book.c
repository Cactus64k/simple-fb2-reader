#include "reader_chunks.h"

gboolean reader_test_file_type(char* file_path, const char* file_ext);

int reader_open_book(char* book_path)
{
	FB2_READER_BOOK_VIEW* book_view		= &GLOBAL_FB2_READER.book_text_view;
	GtkDialog* encode_dialog			= GLOBAL_ENCODE_DIALOG.dialog;
	GtkTreeView* sections_treeview		= GLOBAL_FB2_READER.sections_treeview;
	GtkTextBuffer* text_buff			= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTreeView* tree_view				= GLOBAL_ENCODE_DIALOG.treeview;
	GtkTreeSelection* tree_selection	= gtk_tree_view_get_selection(tree_view);
	GtkTreeModel* tree_model			= GTK_TREE_MODEL(GLOBAL_ENCODE_DIALOG.liststore);


	//########################################################################################
	if(reader_test_file_type(book_path, ".txt") == TRUE)
	{
		if(reader_load_book_config(book_view, book_path) == 0)
		{
			GLOBAL_FB2_READER.book_text_view.type			= BOOK_TYPE_TXT;
			GLOBAL_FB2_READER.book_text_view.path			= book_path;

			gtk_text_buffer_set_text(text_buff, "", 0);

			GKeyFile* config = book_view->config;

			char* encode_name = g_key_file_get_string(config, "book", "encode", NULL);
			if(encode_name != NULL)
				parse_txt(book_path, encode_name);
			else
			{
				if(gtk_dialog_run(encode_dialog) == 2)
				{
					GtkTreeIter tree_iter;

					if(gtk_tree_selection_get_selected(tree_selection, NULL, &tree_iter) == TRUE)
					{
						gtk_tree_model_get(tree_model, &tree_iter, 0, &encode_name, -1);

						g_key_file_set_string(config, "book", "encode", encode_name);

						parse_txt(book_path, encode_name);
					}
					g_free(encode_name);

				}
				gtk_widget_hide(GTK_WIDGET(encode_dialog));
			}

			reader_set_scroll_from_config(book_view);
		}
		else
			fprintf(stderr, _C("ERROR: failed to open file: %s\n"), book_path);
	}
	//########################################################################################
	else if(reader_test_file_type(book_path, ".fb2") == TRUE)
	{
		if(reader_load_book_config(book_view, book_path) == 0)
		{
			GLOBAL_FB2_READER.book_text_view.type			= BOOK_TYPE_FB2;
			GLOBAL_FB2_READER.book_text_view.path			= book_path;

			gtk_text_buffer_set_text(text_buff, "", 0);

			parse_fb2(book_path);
			gtk_tree_view_expand_all(sections_treeview);

			reader_set_scroll_from_config(book_view);
		}
		else
			fprintf(stderr, _C("ERROR: failed to open file: %s\n"), book_path);
	}
	//########################################################################################
	else if(reader_test_file_type(book_path, ".fb2.zip") == TRUE)
	{
		if(reader_load_book_config(book_view, book_path) == 0)
		{
			GLOBAL_FB2_READER.book_text_view.type			= BOOK_TYPE_FB2_ZIP;
			GLOBAL_FB2_READER.book_text_view.path			= book_path;

			gtk_text_buffer_set_text(text_buff, "", 0);

			parse_fb2_zip(book_path);
			gtk_tree_view_expand_all(sections_treeview);

			reader_set_scroll_from_config(book_view);
		}
		else
			fprintf(stderr, _C("ERROR: failed to open file: %s\n"), book_path);
	}
	//########################################################################################


	return 0;
}



gboolean reader_test_file_type(char* file_path, const char* file_ext)
{
	size_t file_path_len = strlen(file_path);
	size_t file_ext_len	= strlen(file_ext);

	if(strcmp(file_ext, file_path + (file_path_len-file_ext_len)) == 0)
		return TRUE;

	return FALSE;
}
