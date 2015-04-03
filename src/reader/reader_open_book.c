#include "reader_chunks.h"

int reader_open_book(char* book_path)
{
	FB2_READER_BOOK_VIEW* book_view		= &GLOBAL_FB2_READER.book_text_view;
	GtkDialog* encode_dialog			= GLOBAL_ENCODE_DIALOG.dialog;
<<<<<<< HEAD
=======
	GtkTreeView* sections_treeview		= GLOBAL_FB2_READER.sections_treeview;
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
	GtkTreeView* tree_view				= GLOBAL_ENCODE_DIALOG.treeview;
	GtkTreeSelection* tree_selection	= gtk_tree_view_get_selection(tree_view);
	GtkTreeModel* tree_model			= GTK_TREE_MODEL(GLOBAL_ENCODE_DIALOG.liststore);

	BOOK_TYPE book_type = reader_get_book_type(book_path);

	if(book_type != BOOK_TYPE_NONE)
	{
<<<<<<< HEAD
		book_view->type = book_type;
		book_view->path = book_path;

=======
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
		if(reader_load_book_config(book_view, book_path) == 0)
		{
			GKeyFile* config = book_view->config;

			//*****************************************************
			if(book_type == BOOK_TYPE_FB2)
				parse_fb2(book_path);
			//*****************************************************
			else if(book_type == BOOK_TYPE_FB2_ZIP)
				parse_fb2_zip(book_path);
			//*****************************************************
			else if(book_type == BOOK_TYPE_TXT)
			{
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
			}
			//*****************************************************

<<<<<<< HEAD
			//gtk_tree_view_expand_all(sections_treeview);

			reader_scroll_restore(book_view);
=======
			gtk_tree_view_expand_all(sections_treeview);

			reader_scroll_restore(book_view);

			book_view->type = book_type;
			book_view->path = book_path;
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
		}
		else
			fprintf(stderr, _C("ERROR: failed to open file: %s\n"), book_path);
	}

	return 0;
}

int _strncmpr(const char *str1, const char *str2, size_t count)
{
	size_t str1_len = strlen(str1);
	size_t str2_len = strlen(str2);

	str1 += str1_len-1;
	str2 += str2_len-1;

	size_t pos = (str1_len < str2_len)? str1_len: str2_len;
	pos = (pos < count)? pos: count;

	while(pos != 0)
	{
		if(*str1 != *str2)
			return str1_len - str2_len;

		str1--;
		str2--;
		pos--;
	}

	return 0;
}

BOOK_TYPE reader_get_book_type(char* file_path)
{
	if(_strncmpr(".fb2", file_path, sizeof(".fb2")-1) == 0)
		return BOOK_TYPE_FB2;
	else if(_strncmpr(".fb2.zip", file_path, sizeof(".fb2.zip")-1) == 0)
		return BOOK_TYPE_FB2_ZIP;
	else if(_strncmpr(".txt", file_path, sizeof(".txt")-1) == 0)
		return BOOK_TYPE_TXT;

	return BOOK_TYPE_NONE;
}
