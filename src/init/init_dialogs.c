#include "../chunks.h"

int search_wnd_init(GtkBuilder* builder, SEARCH_WINDOW* obj)
{
	obj->search_wnd					= GTK_WIDGET(				gtk_builder_get_object(builder, "search_wnd"));
	obj->entry_edited				= FALSE;
	obj->search_query_entry			= GTK_ENTRY(				gtk_builder_get_object(builder, "search_query_entry"));
	//obj->last_pos					=	??;

	assert(obj->search_wnd			!= NULL);
	assert(obj->search_query_entry	!= NULL);

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
