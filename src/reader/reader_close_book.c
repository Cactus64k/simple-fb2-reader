#include "reader_chunks.h"

void text_tag_foreach_remove(GtkTextTag* tag, gpointer data);
void free_text_mark(gpointer ptr);

int reader_close_book(APP* app)
{
	GtkWidget* main_wnd					= app->main_wnd;
	GtkTreeStore* section_treestore		= app->sections_treestore;
	GHashTable* binary_hash_table		= app->binary_hash_table;
	GHashTable* links_hash_table		= app->links_hash_table;
	GtkTextBuffer* text_buff			= app->text_buff;
	BOOK_TYPE book_type					= app->book_type;
	GList* link_jump_list				= app->link_jump_list;

	if(book_type != BOOK_TYPE_NONE)
	{
		reader_scroll_save(app);

		//******************************************************************

		GtkTextIter text_buff_end_iter;
		GtkTextIter text_buff_start_iter;
		GtkTextTagTable* text_tag_table		= gtk_text_buffer_get_tag_table(text_buff);

		gtk_text_buffer_get_bounds(text_buff, &text_buff_start_iter, &text_buff_end_iter);
		gtk_text_buffer_delete(text_buff, &text_buff_start_iter, &text_buff_end_iter);

		gtk_text_tag_table_foreach(text_tag_table, text_tag_foreach_remove, text_tag_table);

		g_hash_table_remove_all(binary_hash_table);
		g_hash_table_remove_all(links_hash_table);

		g_list_free_full(link_jump_list, free_text_mark);

		gtk_window_set_title(GTK_WINDOW(main_wnd), "Simple FB2 reader");

		gtk_tree_store_clear(section_treestore);

		app->link_jump_list			= NULL;
		app->book_type				= BOOK_TYPE_NONE;
		app->book_index				= -1;

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

void free_text_mark(gpointer ptr)
{
	GtkTextMark* mark			= GTK_TEXT_MARK(ptr);
	GtkTextBuffer* text_buff	= gtk_text_mark_get_buffer(mark);

	gtk_text_buffer_delete_mark(text_buff, mark);
}

void text_tag_foreach_remove(GtkTextTag* tag, gpointer data)
{
	GtkTextTagTable* text_tag_table = (GtkTextTagTable*)data;

	GValue tag_name = G_VALUE_INIT;
	g_value_init(&tag_name, G_TYPE_STRING);
	g_object_get_property(G_OBJECT(tag), "name", &tag_name);

	if(g_value_get_string(&tag_name) == NULL)
		gtk_text_tag_table_remove(text_tag_table, tag);

	g_value_unset(&tag_name);
}
