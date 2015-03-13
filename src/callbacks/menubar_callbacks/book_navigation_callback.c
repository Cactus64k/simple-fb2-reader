#include "../../chunks.h"

void book_navigation_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkDialog* dialog			= GLOBAL_FB2_READER.navigation_dialog;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view		= GLOBAL_FB2_READER.book_text_view.text_view;
	GtkTreeStore* section_store	= GLOBAL_FB2_READER.book_text_view.sections_treestore;
	BOOK_TYPE book_type			= GLOBAL_FB2_READER.book_text_view.type;
	GtkTreeView* tree_view		= GLOBAL_FB2_READER.sections_treeview;

	GtkTextIter text_iter;
	GtkTreeIter tree_iter;
	gint string_number = 0;

	if((book_type != BOOK_TYPE_NONE) && (book_type != BOOK_TYPE_TXT))
	{
		gtk_widget_grab_focus(GTK_WIDGET(dialog));

		if(gtk_dialog_run(dialog) == 2)
		{
			gtk_widget_hide(GTK_WIDGET(dialog));
			GtkTreeModel* tree_model = GTK_TREE_MODEL(section_store);

			GtkTreeSelection* tree_selection = gtk_tree_view_get_selection(tree_view);
			gtk_tree_selection_get_selected(tree_selection, &tree_model, &tree_iter);
			gtk_tree_model_get(GTK_TREE_MODEL(section_store), &tree_iter, SECTION_STRING_COLUMN, &string_number, -1);

			gtk_text_buffer_get_iter_at_line(text_buff, &text_iter, string_number);
			gtk_text_view_scroll_to_iter(text_view, &text_iter, 0.f, TRUE, 0.f, 0.f);
		}

		gtk_widget_hide(GTK_WIDGET(dialog));
	}
}
