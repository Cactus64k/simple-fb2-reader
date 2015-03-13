#include "../chunks.h"

void link_remove(gpointer pointer);

int init_main_reader_book_view(GtkBuilder* builder, FB2_READER* obj0)
{
	FB2_READER_BOOK_VIEW* obj		= &obj0->book_text_view;

	memset(obj, 0, sizeof(*obj));

	obj->text_buff					= GTK_TEXT_BUFFER(			gtk_builder_get_object(builder, "book_textbuff"));
	obj->text_view					= GTK_TEXT_VIEW(			gtk_builder_get_object(builder, "book_textview"));

	obj->sections_treestore			= GTK_TREE_STORE(			gtk_builder_get_object(builder, "books_sections_treestore"));

	obj->type						= BOOK_TYPE_NONE;

	assert(obj->text_buff			!= NULL);
	assert(obj->text_view			!= NULL);

	assert(obj->sections_treestore	!= NULL);

	create_fb2_tags(obj0);

	//#################################################################################################################

	GtkTextIter text_buff_end;
	gtk_text_buffer_get_end_iter(obj->text_buff, &text_buff_end);

	gtk_text_buffer_insert_with_tags_by_name(obj->text_buff, &text_buff_end, _C("\n\n\n\nHello! =P \n"), -1, "title_tag", "default_tag", NULL);

	obj->binary_hash_table			= g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_object_unref);
	obj->links_hash_table			= g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

	return 0;
}

void link_remove(gpointer pointer)
{
	GtkTextMark* mark			= GTK_TEXT_MARK(pointer);
	GtkTextBuffer* text_buff	= gtk_text_mark_get_buffer(mark);

	gtk_text_buffer_delete_mark(text_buff, mark);
}
