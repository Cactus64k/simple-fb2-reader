#include "reader_chunks.h"

void text_tag_foreach_remove(GtkTextTag* tag, gpointer data);
void free_text_mark(gpointer ptr);

int reader_close_book()
{
	FB2_READER_BOOK_VIEW* book_view		= &GLOBAL_FB2_READER.book_text_view;
	GtkWidget* main_wnd					= GLOBAL_FB2_READER.main_wnd;
	GtkTreeStore* section_treestore		= GLOBAL_FB2_READER.book_text_view.sections_treestore;
	GHashTable* binary_hash_table		= GLOBAL_FB2_READER.book_text_view.binary_hash_table;
	GHashTable* links_hash_table		= GLOBAL_FB2_READER.book_text_view.links_hash_table;
	GtkTextBuffer* text_buff			= GLOBAL_FB2_READER.book_text_view.text_buff;
	GKeyFile* book_config				= GLOBAL_FB2_READER.book_text_view.config;
	BOOK_TYPE book_type					= GLOBAL_FB2_READER.book_text_view.type;
	char* book_config_path				= GLOBAL_FB2_READER.book_text_view.config_path;
	char* book_path						= GLOBAL_FB2_READER.book_text_view.path;
	GList* link_jump_list				= GLOBAL_FB2_READER.book_text_view.link_jump_list;

	if(book_type != BOOK_TYPE_NONE)
	{
		reader_scroll_save(book_view);

		gsize book_config_len	= 0;
		char* book_config_data	= g_key_file_to_data(book_config, &book_config_len, NULL);

		FILE* f = fopen(book_config_path, "wb");
		fwrite(book_config_data, 1, book_config_len,  f);
		fclose(f);
		g_free(book_config_data);

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

		g_free(book_config_path);
		g_free(book_path);
		g_key_file_free(book_config);

		GLOBAL_FB2_READER.book_text_view.path			= NULL;
		GLOBAL_FB2_READER.book_text_view.config_path	= NULL;
		GLOBAL_FB2_READER.book_text_view.config			= NULL;
		GLOBAL_FB2_READER.book_text_view.link_jump_list		= NULL;
		GLOBAL_FB2_READER.book_text_view.type			= BOOK_TYPE_NONE;
	}

	return 0;
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
