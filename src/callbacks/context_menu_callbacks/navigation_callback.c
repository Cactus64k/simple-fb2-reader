#include "../callbacks_chunk.h"

G_MODULE_EXPORT void navigation_menuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GtkDialog* navigation_dialog	= app->navigation_dialog;
	GtkTreeStore* section_store		= app->sections_treestore;
	BOOK_TYPE book_type				= app->book_type;
	GtkTreeView* tree_view			= app->sections_treeview;

	GtkTreeIter tree_iter;
	gint line = 0;

	if(book_type != BOOK_TYPE_NONE)
	{
		gtk_widget_grab_focus(GTK_WIDGET(navigation_dialog));

		if(gtk_dialog_run(navigation_dialog) == 2)
		{
			gtk_widget_hide(GTK_WIDGET(navigation_dialog));

			GtkTreeModel* tree_model = GTK_TREE_MODEL(section_store);

			GtkTreeSelection* tree_selection = gtk_tree_view_get_selection(tree_view);
			gtk_tree_selection_get_selected(tree_selection, &tree_model, &tree_iter);
			gtk_tree_model_get(GTK_TREE_MODEL(section_store), &tree_iter, SECTION_STRING_COLUMN, &line, -1);

			reader_scroll_to_line_offset(app, line, 0);
		}

		gtk_widget_hide(GTK_WIDGET(navigation_dialog));
	}
}
