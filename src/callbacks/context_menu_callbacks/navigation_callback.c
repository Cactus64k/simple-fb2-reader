#include "../callbacks_chunk.h"

void navigation_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	FB2_READER_BOOK_VIEW* book_view	= &(GLOBAL_FB2_READER.book_text_view);
	GtkDialog* navigation_dialog	= GLOBAL_FB2_READER.navigation_dialog;
	GtkTreeStore* section_store		= GLOBAL_FB2_READER.book_text_view.sections_treestore;
	BOOK_TYPE book_type				= GLOBAL_FB2_READER.book_text_view.type;
	GtkTreeView* tree_view			= GLOBAL_FB2_READER.sections_treeview;

	GtkTreeIter tree_iter;
	gint line = 0;

	if((book_type != BOOK_TYPE_NONE) && (book_type != BOOK_TYPE_TXT))
	{
		gtk_widget_grab_focus(GTK_WIDGET(navigation_dialog));

		if(gtk_dialog_run(navigation_dialog) == 2)
		{
			gtk_widget_hide(GTK_WIDGET(navigation_dialog));

			GtkTreeModel* tree_model = GTK_TREE_MODEL(section_store);

			GtkTreeSelection* tree_selection = gtk_tree_view_get_selection(tree_view);
			gtk_tree_selection_get_selected(tree_selection, &tree_model, &tree_iter);
			gtk_tree_model_get(GTK_TREE_MODEL(section_store), &tree_iter, SECTION_STRING_COLUMN, &line, -1);

			reader_scroll_at_line_offset(book_view, line, 0);
		}

		gtk_widget_hide(GTK_WIDGET(navigation_dialog));
	}
}
