
#ifndef CALLBACKS_CHUNK_H_
#define CALLBACKS_CHUNK_H_

	#include "../chunks.h"

	void encode_treeview_cursor_changed_cb		(GtkTreeView* tree_view, gpointer user_data);
	void txt_encode_dialog_show_cb				(GtkWidget* widget, gpointer user_data);

	gboolean main_wnd_delete_event_cb			(GtkWidget* widget, GdkEvent *event, gpointer user_data);
	void file_quit_imagemenuitem_activate_cb	(GtkMenuItem* menuitem, gpointer user_data);

	void main_wnd_size_allocate_cb				(GtkWidget* widget, GdkRectangle *allocation, gpointer user_data);
	gboolean main_wnd_key_press_event_cb		(GtkWidget* widget, GdkEventKey* event, gpointer user_data);

	void search_wnd_close_button_clicked_cb		(GtkButton* widget, gpointer user_data);
	gboolean search_wnd_key_press_event_cb		(GtkWidget* widget, GdkEvent* event, gpointer user_data);
	void search_wnd_search_button_clicked_cb	(GtkButton* button, gpointer user_data);
	void search_query_changed_cb				(GtkEditable* editable, gpointer user_data);

	void open_file_menuitem_activate_cb			(GtkMenuItem *menuitem, gpointer user_data);

	void search_menuitem_activate_cb			(GtkMenuItem* menuitem, gpointer user_data);
	void encoding_menuitem_activate_cb			(GtkMenuItem* menuitem, gpointer user_data);
	void navigation_treeview_row_activated_cb	(GtkTreeView* tree_view, GtkTreePath* path, GtkTreeViewColumn* column, gpointer user_data);
	void navigation_menuitem_activate_cb		(GtkMenuItem *menuitem, gpointer user_data);

	void forger_books_menuitem_activate_cb		(GtkMenuItem *menuitem, gpointer user_data);
	void about_menuitem_activate_cb				(GtkMenuItem *menuitem, gpointer user_data);
	void color_theme_checkmenuitem_toggled_cb	(GtkCheckMenuItem* checkmenuitem, gpointer user_data);

	void backward_itemmenu_cb					(GtkMenuItem* menuitem, gpointer user_data);

	void color_theme_activate_cb				(GtkMenuItem* checkmenuitem, gpointer user_data);
	void recent_books_activate_cb				(GtkMenuItem* checkmenuitem, gpointer user_data);
	void select_recent_book_activate_cb			(GtkMenuItem* checkmenuitem, gpointer user_data);


	gboolean a_tag_event_cb(GtkTextTag* tag, GObject* object, GdkEvent* event, GtkTextIter* iter, gpointer user_data);


#endif /* CALLBACKS_CHUNK_H_ */
