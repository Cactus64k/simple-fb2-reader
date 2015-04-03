#include "../chunks.h"

int fill_encode_liststore(GtkListStore* list_store);

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
	obj->liststore					= GTK_LIST_STORE(			gtk_builder_get_object(builder, "encode_liststore"));
	obj->treeview					= GTK_TREE_VIEW(			gtk_builder_get_object(builder, "encode_treeview"));
	obj->textbuffer					= GTK_TEXT_BUFFER(			gtk_builder_get_object(builder, "encode_textbuffer"));

	assert(obj->dialog		!= NULL);
	assert(obj->liststore	!= NULL);
	assert(obj->treeview	!= NULL);
	assert(obj->textbuffer	!= NULL);

	fill_encode_liststore(obj->liststore);

	return 0;
}

int fill_encode_liststore(GtkListStore* list_store)
{
	char buff[128];
	FILE* f = fopen(ENCODE_LIST_PATH, "rb");
	GtkTreeIter tree_iter;
	while(feof(f) == 0)
	{
		fgets(buff, sizeof(buff), f);
		char* line	= strchr(buff, '\n');
		if(line != NULL)
		{
			*line = 0;

			gtk_list_store_append(list_store, &tree_iter);
			gtk_list_store_set(list_store, &tree_iter, 0, buff, -1);
		}
	}

	fclose(f);

	return 0;
}





