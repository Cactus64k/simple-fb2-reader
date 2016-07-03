#include "callbacks_chunk.h"

G_MODULE_EXPORT void search_wnd_close_button_clicked_cb(GtkButton* widget, gpointer user_data)
{
	APP* app			= (APP*)user_data;
	GtkWidget* s_wnd	= app->search_window.search_wnd;
	gtk_widget_hide(s_wnd);
}

G_MODULE_EXPORT gboolean search_wnd_key_press_event_cb(GtkWidget* widget, GdkEvent* event, gpointer user_data)
{
	APP* app				= (APP*)user_data;
	GdkEventKey key_event	= event->key;
	if(key_event.keyval == GDK_KEY_Escape)
		gtk_widget_hide(widget);
	else if(key_event.keyval == GDK_KEY_Return)
		search_wnd_search_button_clicked_cb(NULL, app);

	return FALSE;
}


G_MODULE_EXPORT void search_wnd_search_button_clicked_cb(GtkButton* button, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GtkTextBuffer* text_buff		= app->text_buff;
	GtkTextView* text_view			= app->text_view;
	GtkEntry* search_entry			= app->search_window.search_query_entry;
	GtkTextIter* last_search_pos	= app->search_window.last_pos;
	GtkCheckButton* case_sensitive	= app->search_window.case_sensitive;
	GtkRadioButton* backward		= app->search_window.backward;
	GtkRadioButton* forward			= app->search_window.forward;

	GtkAdjustment* horisontal_adj	= gtk_scrollable_get_hadjustment(GTK_SCROLLABLE(text_view));

	const char* query = gtk_entry_get_text(search_entry);

	GtkTextIter text_buff_match_start_iter;
	GtkTextIter text_buff_match_end_iter;

	gboolean search_success = FALSE;
	GtkTextSearchFlags case_sensitive_flag;

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(case_sensitive)) == TRUE)
		case_sensitive_flag = GTK_TEXT_SEARCH_VISIBLE_ONLY;
	else
		case_sensitive_flag = GTK_TEXT_SEARCH_CASE_INSENSITIVE;

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(forward)) == TRUE)
		search_success = gtk_text_iter_forward_search(last_search_pos, query, case_sensitive_flag, &text_buff_match_start_iter, &text_buff_match_end_iter, NULL);
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backward)) == TRUE)
		search_success = gtk_text_iter_backward_search(last_search_pos, query, case_sensitive_flag, &text_buff_match_start_iter, &text_buff_match_end_iter, NULL);

	if(search_success == TRUE)
	{
		gtk_text_buffer_select_range(text_buff, &text_buff_match_start_iter, &text_buff_match_end_iter);

		gtk_text_view_scroll_to_iter(text_view, &text_buff_match_start_iter, 0.0, TRUE, 0.0, 0.0);

		gtk_adjustment_set_value(horisontal_adj, 0.0);

		//*last_search_pos = text_buff_match_end_iter;

		gtk_text_iter_free(last_search_pos);

		app->search_window.last_pos = gtk_text_iter_copy(&text_buff_match_end_iter);
		//FIXME ебота выше
	}
	else
	{
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(forward)) == TRUE)
			gtk_text_buffer_get_start_iter(text_buff, last_search_pos);
		else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backward)) == TRUE)
			gtk_text_buffer_get_end_iter(text_buff, last_search_pos);
	}
}


G_MODULE_EXPORT void search_query_changed_cb(GtkEditable* editable, gpointer user_data)
{
	APP* app						= (APP*)user_data;
	GtkTextBuffer* text_buff		= app->text_buff;
	GtkTextIter* last_search_pos	= app->search_window.last_pos;
	gtk_text_buffer_get_start_iter(text_buff, last_search_pos);
}

