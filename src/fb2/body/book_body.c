#include "../fb2_chunks.h"

int parse_book_body(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	GtkListStore* section_list_store = GLOBAL_FB2_READER.sections_liststore;

	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	node = node->children;

	size_t section_counter = 0;
	while(node != NULL)
	{
		if(strcmp((char*)node->name, "section") == 0)
		{
			parse_body_section(node, text_buff, text_buff_end, section_counter);
			section_counter++;
		}
		else if(strcmp((char*)node->name, "title") == 0)
		{
			GtkTreeIter list_pos;
			gtk_list_store_insert(section_list_store, &list_pos, section_counter);
			parse_title(node, text_buff, text_buff_end, &list_pos, section_list_store);
			section_counter++;
			//print_unsupported_tag("title");
		}
		else if(strcmp((char*)node->name, "epigraph") == 0)
		{
			print_unsupported_tag("epigraph");
		}
		else if(strcmp((char*)node->name, "image") == 0)
			parse_image(node, text_buff, text_buff_end);

		node = node->next;
	}
	return 0;
}

int parse_subtitle(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	GtkTextTag* subtitle_tag	= GLOBAL_FB2_READER.subtitle_tag;
	GtkTextMark* start_subtitle	= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, true);

	parse_p(node, text_buff, text_buff_end);

	GtkTextIter start_subtitle_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_subtitle_iter, start_subtitle);
	gtk_text_buffer_delete_mark(text_buff, start_subtitle);
	gtk_text_buffer_apply_tag(text_buff, subtitle_tag, &start_subtitle_iter, text_buff_end);

	return 0;
}


int parse_title(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end, GtkTreeIter* list_pos, GtkListStore* list_store)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	GtkTextTag* title_tag = GLOBAL_FB2_READER.title_tag;

	node = node->children;

	GtkTextMark* start_title = gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, true);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	while(node != NULL)
	{
		if(strcmp((char*)node->name, "p") == 0)
			parse_p(node, text_buff, text_buff_end);
		else if(strcmp((char*)node->name, "empty-line") == 0)
			gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

		node = node->next;
	}

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);

	GtkTextIter start_title_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_title_iter, start_title);
	gtk_text_buffer_delete_mark(text_buff, start_title);
	gtk_text_buffer_apply_tag(text_buff, title_tag, &start_title_iter, text_buff_end);

	char* title_text = gtk_text_buffer_get_text(text_buff, &start_title_iter, text_buff_end, false);
	gtk_list_store_set(list_store, list_pos, SECTION_NAME_COLUMN, title_text, -1);
	g_free(title_text);

	return 0;
}

int print_unsupported_tag(char* tag)
{
	fprintf(stderr, "Finde unsupported tag: %s\n", tag);
	return 0;
}
