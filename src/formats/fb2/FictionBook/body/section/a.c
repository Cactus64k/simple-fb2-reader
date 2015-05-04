#include "section_chunks.h"

int parse_fb2_a(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);


	GtkTextBuffer* text_buff		= obj->text_buff;
	xmlNode* node					= parent_node->children;

	GtkTextMark* start_tag_mark		= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);
	GtkTextTag* a_tag				= gtk_text_buffer_create_tag(text_buff, NULL, 	"foreground",		"blue",
																					"underline",		PANGO_UNDERLINE_SINGLE, NULL);

	const char* href_attr			= NULL;

	parse_fb2_attribute(obj, parent_node, "href", &href_attr);
	if(href_attr != NULL)
	{
		char* href_dup				= g_strdup(href_attr);
		g_signal_connect(G_OBJECT(a_tag), "event", G_CALLBACK(a_tag_event_cb), NULL);
		g_object_set_data_full(G_OBJECT(a_tag), "href", href_dup, g_free);
	}

	parse_fb2_p_link(obj, node, text_buff_end);

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag(text_buff, a_tag, &start_tag_iter, text_buff_end);

	return 0;
}
