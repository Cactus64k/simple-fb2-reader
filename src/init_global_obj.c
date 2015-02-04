#include "chunks.h"

int search_wnd_init(GtkBuilder* builder, SEARCH_WINDOW* obj)
{
	obj->search_wnd					= GTK_WIDGET(				gtk_builder_get_object(builder, "search_wnd"));
	obj->entry_edited				= false;
	obj->search_query_entry			= GTK_ENTRY(				gtk_builder_get_object(builder, "search_query_entry"));
	//obj->last_pos					=	??;

	assert(obj->search_wnd			!= NULL);
	assert(obj->search_query_entry	!= NULL);

	return 0;
}

int main_wnd_init(GtkBuilder* builder, FB2_READER* obj)
{
	obj->main_wnd					= GTK_WIDGET(				gtk_builder_get_object(builder, "main_wnd"));
	obj->text_buff					= GTK_TEXT_BUFFER(			gtk_builder_get_object(builder, "book_textbuff"));
	obj->text_view					= GTK_TEXT_VIEW(			gtk_builder_get_object(builder, "book_textview"));
	obj->filechooserdialog			= GTK_FILE_CHOOSER_DIALOG(	gtk_builder_get_object(builder, "book_filechooserdialog"));
	obj->navigation_dialog			= GTK_DIALOG(				gtk_builder_get_object(builder, "navigation_dialog"));
	obj->sections_liststore			= GTK_LIST_STORE(			gtk_builder_get_object(builder, "books_sections_liststore"));

	assert(obj->main_wnd			!= NULL);
	assert(obj->text_buff			!= NULL);
	assert(obj->text_view			!= NULL);
	assert(obj->filechooserdialog	!= NULL);
	assert(obj->navigation_dialog	!= NULL);
	assert(obj->sections_liststore	!= NULL);

	GtkAllocation allocated_size;
	gtk_widget_get_allocation(GTK_WIDGET(obj->text_view), &allocated_size);


	GtkTextTagTable* text_tag_table	= gtk_text_buffer_get_tag_table(obj->text_buff);

	obj->default_tag				= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"size-points",		15.f,
																						"family",			"DejaVu",
																						"wrap_mode",		GTK_WRAP_WORD_CHAR, NULL);
	//####################################################################################################################################
	obj->title_tag					= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"size-points",		17.f,
																						"justification",	GTK_JUSTIFY_CENTER, NULL);
	//####################################################################################################################################
	obj->strong_tag					= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"weight",			PANGO_WEIGHT_BOLD, NULL);
	//####################################################################################################################################
	obj->sub_tag					= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"size-points",		8.f,
																						"rise",				-5000, NULL);
	//####################################################################################################################################
	obj->sup_tag					= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"size-points",		8.f,
																						"rise",				7000, NULL);
	//####################################################################################################################################
	obj->strikethrough_tag			= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"strikethrough",	true, NULL);
	//####################################################################################################################################
	obj->emphasis_tag				= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"style",			PANGO_STYLE_ITALIC, NULL);
	//####################################################################################################################################
	obj->code_tag					= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"family",			"Mono", NULL);
	//####################################################################################################################################
	obj->subtitle_tag				= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"justification",	GTK_JUSTIFY_CENTER, NULL);
	//####################################################################################################################################
	obj->image_tag					= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"size-points",		10.f,
																						"justification",	GTK_JUSTIFY_CENTER, NULL);
	//####################################################################################################################################
	obj->cite_tag					= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"size-points",		15.f,
																						"style",			PANGO_STYLE_ITALIC, NULL);
	//####################################################################################################################################
	obj->text_author_tag			= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"size-points",		12.f,
																						"justification",	GTK_JUSTIFY_RIGHT, NULL);
	//####################################################################################################################################
	obj->epigraph_tag				= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"left-margin",		allocated_size.width * EPIGRAPH_TAG_MARGIN,
																						"right-margin",		allocated_size.width * EPIGRAPH_TAG_MARGIN, NULL);
	//####################################################################################################################################
	obj->stanza_tag					= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"style",			PANGO_STYLE_ITALIC,
																						"justification",	GTK_JUSTIFY_CENTER, NULL);

	/*obj->a_tag					= gtk_text_buffer_create_tag(obj->text_buff, NULL, 	"foreground",		"blue",
																						"underline",		PANGO_UNDERLINE_SINGLE,NULL);*/

	obj->tag_table_default_size		= gtk_text_tag_table_get_size(text_tag_table);

	obj->binary_hash_table			= g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_object_unref);
	obj->links_hash_table			= g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_object_unref);

	obj->link_cursor				= gdk_cursor_new(GDK_HAND2);
	obj->def_cursor					= gdk_cursor_new(GDK_XTERM);

	obj->clipboard					= gtk_clipboard_get(0);

	assert(obj->default_tag			!= NULL);
	assert(obj->title_tag			!= NULL);
	assert(obj->strong_tag			!= NULL);
	assert(obj->sub_tag				!= NULL);
	assert(obj->sup_tag				!= NULL);
	assert(obj->strikethrough_tag	!= NULL);
	assert(obj->emphasis_tag		!= NULL);
	assert(obj->code_tag			!= NULL);
	assert(obj->subtitle_tag		!= NULL);
	assert(obj->image_tag			!= NULL);
	assert(obj->epigraph_tag		!= NULL);
	assert(obj->binary_hash_table	!= NULL);
	assert(obj->links_hash_table	!= NULL);
	assert(obj->clipboard			!= NULL);

	gtk_widget_show_all(obj->main_wnd);

	return 0;
}


int encode_wnd_init(GtkBuilder* builder, ENCODE_DIALOG* obj)
{
	obj->dialog						= GTK_DIALOG(				gtk_builder_get_object(builder, "txt_encode_dialog"));
	obj->treestore					= GTK_TREE_STORE(			gtk_builder_get_object(builder, "encode_treestore"));
	obj->treeview					= GTK_TREE_VIEW(			gtk_builder_get_object(builder, "encode_treeview"));
	obj->buffer_data_size			= 0;
	obj->textbuffer					= GTK_TEXT_BUFFER(			gtk_builder_get_object(builder, "encode_textbuffer"));

	assert(obj->dialog		!= NULL);
	assert(obj->treestore	!= NULL);
	assert(obj->treeview	!= NULL);
	assert(obj->textbuffer	!= NULL);

	fill_encode_treestore(obj->treestore);

	return 0;
}
