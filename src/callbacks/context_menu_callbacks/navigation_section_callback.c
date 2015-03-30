#include "../callbacks_chunk.h"

void navigation_treeview_row_activated_cb(GtkTreeView* tree_view, GtkTreePath* path, GtkTreeViewColumn* column, gpointer user_data)
{
	GtkDialog* dialog			= GLOBAL_FB2_READER.navigation_dialog;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view		= GLOBAL_FB2_READER.book_text_view.text_view;
	GtkTreeStore* section_store	= GLOBAL_FB2_READER.book_text_view.sections_treestore;
	GtkTextIter text_iter;
	GtkTreeIter tree_iter;
	gint string_number = 0;

	gtk_widget_hide(GTK_WIDGET(dialog));


	GtkTreeModel* tree_model = GTK_TREE_MODEL(section_store);

	if(gtk_tree_model_get_iter(tree_model, &tree_iter, path) == TRUE)
	{
		gtk_tree_model_get(GTK_TREE_MODEL(section_store), &tree_iter, SECTION_STRING_COLUMN, &string_number, -1);

		gtk_text_buffer_get_iter_at_line(text_buff, &text_iter, string_number);
		gtk_text_view_scroll_to_iter(text_view, &text_iter, 0.f, TRUE, 0.f, 0.f);
	}
}
