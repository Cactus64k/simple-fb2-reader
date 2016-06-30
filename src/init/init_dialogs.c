#include "../chunks.h"

int init_search_wnd(GtkBuilder* builder, SEARCH_WINDOW* obj)
{
	memset(obj, 0, sizeof(*obj));

	obj->search_wnd				= GTK_WIDGET(				gtk_builder_get_object(builder, "search_wnd"));
	obj->search_query_entry		= GTK_ENTRY(				gtk_builder_get_object(builder, "search_query_entry"));
	obj->forward				= GTK_RADIO_BUTTON(			gtk_builder_get_object(builder, "search_forward_radiobutton"));
	obj->backward				= GTK_RADIO_BUTTON(			gtk_builder_get_object(builder, "search_backward_radiobutton"));
	obj->case_sensitive			= GTK_CHECK_BUTTON(			gtk_builder_get_object(builder, "search_case_sensitive_checkbutton"));

	GtkTextIter text_iter;
	obj->last_pos				= gtk_text_iter_copy(&text_iter);

	assert(obj->search_wnd				!= NULL);
	assert(obj->search_query_entry		!= NULL);
	assert(obj->forward					!= NULL);
	assert(obj->backward				!= NULL);
	assert(obj->case_sensitive			!= NULL);

	return EXIT_SUCCESS;
}
