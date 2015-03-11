#include "../chunks.h"

int init_search_wnd(GtkBuilder* builder, FB2_READER_SEARCH_WINDOW* obj)
{
	memset(obj, 0, sizeof(*obj));

	obj->search_wnd					= GTK_WIDGET(				gtk_builder_get_object(builder, "search_wnd"));
	obj->search_query_entry			= GTK_ENTRY(				gtk_builder_get_object(builder, "search_query_entry"));
	obj->forward					= GTK_RADIO_BUTTON(			gtk_builder_get_object(builder, "search_forward_radiobutton"));
	obj->backward					= GTK_RADIO_BUTTON(			gtk_builder_get_object(builder, "search_backward_radiobutton"));
	obj->case_sensitive				= GTK_CHECK_BUTTON(			gtk_builder_get_object(builder, "search_case_sensitive_checkbutton"));

	assert(obj->search_wnd			!= NULL);
	assert(obj->search_query_entry	!= NULL);

	return 0;
}


int init_encode_wnd(GtkBuilder* builder, FB2_READER_ENCODE_DIALOG* obj)
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
