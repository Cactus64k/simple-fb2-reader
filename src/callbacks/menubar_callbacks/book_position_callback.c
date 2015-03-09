#include "../../chunks.h"

void book_position_imagemenuitem_activate_cb(GtkMenuItem* menuitem, gpointer user_data)
{
	GKeyFile* book_config		= GLOBAL_FB2_READER.book_text_view.config;
	GtkTextBuffer* text_buff	= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view		= GLOBAL_FB2_READER.book_text_view.text_view;
	BOOK_TYPE book_type			= GLOBAL_FB2_READER.book_text_view.type;

	if(book_config != NULL)
	{
		if(book_type != BOOK_TYPE_NONE)
		{
			gint read_line				= g_key_file_get_int64(book_config, "book", "read_line", NULL);
			gint read_line_offset		= g_key_file_get_int64(book_config, "book", "read_line_offset", NULL);

			GtkTextIter iter;
			gtk_text_buffer_get_iter_at_line_offset(text_buff, &iter, read_line, read_line_offset);
			gtk_text_view_scroll_to_iter(text_view, &iter, 0.f, TRUE, 0.f, 0.0f);
		}
	}
}
