#include "../chunks.h"

void text_tag_foreach_remove(GtkTextTag* tag, gpointer data);

int reader_close_book()
{
	GtkWidget* main_wnd					= GLOBAL_FB2_READER.main_wnd;
	GtkTreeStore* section_treestore		= GLOBAL_FB2_READER.book_text_view.sections_treestore;
	GHashTable* binary_hash_table		= GLOBAL_FB2_READER.book_text_view.binary_hash_table;
	GHashTable* links_hash_table		= GLOBAL_FB2_READER.book_text_view.links_hash_table;
	GtkTextBuffer* text_buff			= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view				= GLOBAL_FB2_READER.book_text_view.text_view;
	GKeyFile* book_config				= GLOBAL_FB2_READER.book_text_view.config;
	char* book_config_path				= GLOBAL_FB2_READER.book_text_view.config_path;

	GtkTextIter text_buff_end_iter;
	GtkTextIter text_buff_start_iter;
	GtkTextTagTable* text_tag_table		= gtk_text_buffer_get_tag_table(text_buff);

	//###############################

	if(book_config != NULL)
	{
		gint read_line			= 0;
		gint read_line_offset	= 0;

		get_scroll_line_offset(text_view, &read_line, &read_line_offset);

		g_key_file_set_integer(book_config, "book", "read_line", read_line);
		g_key_file_set_integer(book_config, "book", "read_line_offset", read_line_offset);

		gsize book_config_len	= 0;
		char* book_config_data	= g_key_file_to_data(book_config, &book_config_len, NULL);

		FILE* f = fopen(book_config_path, "wb");
		fwrite(book_config_data, 1, book_config_len,  f);
		fclose(f);
		g_free(book_config_data);
	}

	//###############################

	gtk_text_buffer_get_bounds(text_buff, &text_buff_start_iter, &text_buff_end_iter);
	gtk_text_buffer_delete(text_buff, &text_buff_start_iter, &text_buff_end_iter);

	gtk_text_tag_table_foreach(text_tag_table, text_tag_foreach_remove, text_tag_table);

	g_hash_table_remove_all(binary_hash_table);
	g_hash_table_remove_all(links_hash_table);

	gtk_window_set_title(GTK_WINDOW(main_wnd), "Simple FB2 reader");

	gtk_tree_store_clear(section_treestore);

	g_free(book_config_path);
	GLOBAL_FB2_READER.book_text_view.config_path	= NULL;

	if(book_config != NULL)
	{
		g_key_file_free(book_config);
		GLOBAL_FB2_READER.book_text_view.config		= NULL;
	}

	return 0;
}

int get_scroll_line_offset(GtkTextView* text_view, gint* line, gint* offset)
{
	GtkTextIter scroll_iter;
	GtkAdjustment* adj	= gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(text_view));
	gint scroll_pos		= (gint)gtk_adjustment_get_value(adj);

	gtk_text_view_get_iter_at_location(text_view, &scroll_iter, 0, scroll_pos);

	*line	= gtk_text_iter_get_line(&scroll_iter);
	*offset	= gtk_text_iter_get_line_offset(&scroll_iter);

	return 0;
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
