#include "../callbacks_chunk.h"

void navigation_treeview_row_activated_cb(GtkTreeView* tree_view, GtkTreePath* path, GtkTreeViewColumn* column, gpointer user_data)
{
	FB2_READER_BOOK_VIEW* book_view	= &(GLOBAL_FB2_READER.book_text_view);
	GtkDialog* dialog				= GLOBAL_FB2_READER.navigation_dialog;
	GtkTreeStore* section_store		= GLOBAL_FB2_READER.book_text_view.sections_treestore;
	GtkTreeIter tree_iter;
	gint line = 0;

	gtk_widget_hide(GTK_WIDGET(dialog));

	if(gtk_tree_model_get_iter(GTK_TREE_MODEL(section_store), &tree_iter, path) == TRUE)
	{
		gtk_tree_model_get(GTK_TREE_MODEL(section_store), &tree_iter, SECTION_STRING_COLUMN, &line, -1);

		reader_scroll_at_line_offset(book_view, line, 0);
	}
}
