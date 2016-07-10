#include "../callbacks_chunk.h"

G_MODULE_EXPORT void navigation_treeview_row_activated_cb(GtkTreeView* tree_view, GtkTreePath* path, GtkTreeViewColumn* column, gpointer user_data)
{

	APP* app						= (APP*)user_data;
	GtkDialog* dialog				= app->navigation_dialog;
	GtkTreeStore* section_store		= app->sections_treestore;
	GtkTreeIter tree_iter;
	gint line = 0;

	gtk_widget_hide(GTK_WIDGET(dialog));

	if(gtk_tree_model_get_iter(GTK_TREE_MODEL(section_store), &tree_iter, path) == TRUE)
	{
		gtk_tree_model_get(GTK_TREE_MODEL(section_store), &tree_iter, SECTION_STRING_COLUMN, &line, -1);

		reader_scroll_to_line_offset(app, line, 0);
	}
}
