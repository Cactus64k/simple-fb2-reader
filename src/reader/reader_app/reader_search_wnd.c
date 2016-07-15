#include "reader_app.h"

int reader_search_wnd(APP* app, GtkBuilder* builder)
{
	SEARCH_WINDOW* search_wnd = &(app->search_window);

	memset(search_wnd, 0, sizeof(*search_wnd));

	search_wnd->search_wnd				= GTK_WIDGET(				gtk_builder_get_object(builder, "search_wnd"));
	search_wnd->search_query_entry		= GTK_ENTRY(				gtk_builder_get_object(builder, "search_query_entry"));
	search_wnd->forward					= GTK_RADIO_BUTTON(			gtk_builder_get_object(builder, "search_forward_radiobutton"));
	search_wnd->case_sensitive			= GTK_CHECK_BUTTON(			gtk_builder_get_object(builder, "search_case_sensitive_checkbutton"));

	assert(search_wnd->search_wnd				!= NULL);
	assert(search_wnd->search_query_entry		!= NULL);
	assert(search_wnd->forward					!= NULL);
	assert(search_wnd->case_sensitive			!= NULL);

	return EXIT_SUCCESS;
}
