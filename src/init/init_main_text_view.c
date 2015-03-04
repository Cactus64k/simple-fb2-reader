#include "../chunks.h"

void link_remove(gpointer pointer);

int init_main_reader_text_view(GtkBuilder* builder, FB2_READER* obj0)
{
	FB2_READER_TEXT_VIEW* obj		= &obj0->book_text_view;

	memset(obj, 0, sizeof(*obj));

	obj->save_section				= FALSE;
	obj->text_buff					= GTK_TEXT_BUFFER(			gtk_builder_get_object(builder, "book_textbuff"));
	obj->text_view					= GTK_TEXT_VIEW(			gtk_builder_get_object(builder, "book_textview"));

	obj->sections_treestore			= GTK_TREE_STORE(			gtk_builder_get_object(builder, "books_sections_treestore"));
	obj->sections_treeview			= GTK_TREE_VIEW(			gtk_builder_get_object(builder, "books_section_treeview"));

	assert(obj->text_buff			!= NULL);
	assert(obj->text_view			!= NULL);

	assert(obj->sections_treestore	!= NULL);
	assert(obj->sections_treeview	!= NULL);

	create_fb2_tags(obj->text_buff);

	//#################################################################################################################

	GtkTextIter text_buff_end;
	gtk_text_buffer_get_end_iter(obj->text_buff, &text_buff_end);

	gtk_text_buffer_insert_with_tags_by_name(obj->text_buff, &text_buff_end, _C("\n\n\n\nHello! =P \n"), -1, "title_tag", "default_tag", NULL);

	GtkTextTagTable* text_tag_table	= gtk_text_buffer_get_tag_table(obj->text_buff);

	obj->tag_table_default_size		= gtk_text_tag_table_get_size(text_tag_table);
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
