#include "chunks.h"

void text_tag_foreach_remove(GtkTextTag* tag, gpointer data);

int open_new_book(char* file_path)
{
	GtkTextBuffer* text_buff			= GLOBAL_FB2_READER.text_buff;
	GtkListStore* section_liststore		= GLOBAL_FB2_READER.sections_liststore;
	GHashTable* binary_hash_table		= GLOBAL_FB2_READER.binary_hash_table;
	GHashTable* links_hash_table		= GLOBAL_FB2_READER.binary_hash_table;
	GtkWidget* main_wnd					= GLOBAL_FB2_READER.main_wnd;
	GtkDialog* encode_dialog			= GLOBAL_ENCODE_DIALOG.dialog;
	GtkTextIter text_buff_end_iter;
	GtkTextIter text_buff_start_iter;
	GtkTextTagTable* text_tag_table		= gtk_text_buffer_get_tag_table(text_buff);

	gtk_text_buffer_get_bounds(text_buff, &text_buff_start_iter, &text_buff_end_iter);


	gtk_text_buffer_delete(text_buff, &text_buff_start_iter, &text_buff_end_iter);

	gtk_text_tag_table_foreach(text_tag_table, text_tag_foreach_remove, text_tag_table);

	g_hash_table_remove_all(binary_hash_table);
	g_hash_table_remove_all(links_hash_table);

	gtk_window_set_title(GTK_WINDOW(main_wnd), "Simple FB2 reader");

	gtk_list_store_clear(section_liststore);

	char* file_type = g_utf8_strrchr(file_path, -1, '.');

	if(strcmp(file_type, ".txt") == 0)
	{
		fill_encode_test_buffer(&GLOBAL_ENCODE_DIALOG, file_path);
		if(gtk_dialog_run(encode_dialog) == 2)
		{
			char* encode_name = get_encode_name(&GLOBAL_ENCODE_DIALOG);
			if(encode_name != NULL)
				parse_txt(file_path, text_buff, encode_name);
			g_free(encode_name);
		}
		gtk_widget_hide(GTK_WIDGET(encode_dialog));
	}
	else if(strcmp(file_type, ".fb2") == 0)
		parse_fb2(file_path, text_buff);
	return 0;
}

void text_tag_foreach_remove(GtkTextTag* tag, gpointer data)
{
	GtkTextTagTable* text_tag_table = (GtkTextTagTable*)data;
	size_t tag_table_default_size	= GLOBAL_FB2_READER.tag_table_default_size;

	int priority = gtk_text_tag_get_priority(tag);
	if(priority >= tag_table_default_size)
		gtk_text_tag_table_remove(text_tag_table, tag);

}
