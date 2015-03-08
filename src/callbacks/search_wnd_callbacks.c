#include "../chunks.h"

void search_wnd_close_button_clicked_cb(GtkButton* widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(user_data));
}

gboolean search_wnd_key_press_event_cb(GtkWidget* widget, GdkEvent* event, gpointer user_data)
{
	GdkEventKey key_event = event->key;
	if(key_event.keyval == GDK_KEY_Escape)
		gtk_widget_hide(widget);

	return FALSE;
}


void search_wnd_search_button_clicked_cb(GtkButton *button, gpointer user_data)
{
	GtkTextBuffer* text_buff		= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view			= GLOBAL_FB2_READER.book_text_view.text_view;
	GtkTextIter* last_search_pos	= &GLOBAL_SEARCH_WND.last_pos;
	gboolean* entry_edited			= &GLOBAL_SEARCH_WND.entry_edited;
	GtkRadioButton* backward		= GLOBAL_SEARCH_WND.backward;
	GtkRadioButton* forward			= GLOBAL_SEARCH_WND.forward;

	const char* query = gtk_entry_get_text(GTK_ENTRY(user_data));

	if(*entry_edited == TRUE)
		gtk_text_buffer_get_start_iter(text_buff, last_search_pos);


	GtkTextIter text_buff_match_start_iter;
	GtkTextIter text_buff_match_end_iter;

	gboolean search_success = FALSE;

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(forward)) == TRUE)
		search_success = gtk_text_iter_forward_search(last_search_pos, query, GTK_TEXT_SEARCH_CASE_INSENSITIVE, &text_buff_match_start_iter, &text_buff_match_end_iter, NULL);
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backward)) == TRUE)
		search_success = gtk_text_iter_backward_search(last_search_pos, query, GTK_TEXT_SEARCH_CASE_INSENSITIVE, &text_buff_match_start_iter, &text_buff_match_end_iter, NULL);

	if(search_success == TRUE)
	{
		gtk_text_buffer_select_range(text_buff, &text_buff_match_start_iter, &text_buff_match_end_iter);

		gtk_text_view_scroll_to_iter(text_view, &text_buff_match_start_iter, 0.f, TRUE, 0.f, 0.5f);

		*last_search_pos = text_buff_match_end_iter;

		*entry_edited = FALSE;
	}
	else
		gtk_text_buffer_get_start_iter(text_buff, last_search_pos);
}


void search_query_changed_cb(GtkEditable* editable, gpointer user_data)
{
	gboolean* entry_edited	 = &GLOBAL_SEARCH_WND.entry_edited;
	*entry_edited = TRUE;
}

