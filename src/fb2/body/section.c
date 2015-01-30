#include "../fb2_chunks.h"

int parse_body_section(xmlNode* node, GtkTextBuffer* text_buff, GtkTextIter* text_buff_end, size_t section_counter)
{
	assert(node != NULL);
	assert(text_buff != NULL);
	assert(text_buff_end != NULL);

	GtkListStore* section_list_store	= GLOBAL_FB2_READER.sections_liststore;

	node = node->children;

	GtkTreeIter list_pos;
	gtk_list_store_insert(section_list_store, &list_pos, section_counter);
	gtk_list_store_set(section_list_store, &list_pos,	SECTION_NUM_COLUMN, section_counter+1, -1);

	while(node != NULL)
	{
		if(strcmp((char*)node->name, "p") == 0)
			parse_p(node, text_buff, text_buff_end);
		else if(strcmp((char*)node->name, "empty-line") == 0)		// пустая строка
			gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
		else if(strcmp((char*)node->name, "title") == 0)
			parse_title(node, text_buff, text_buff_end, &list_pos, section_list_store);
		else if(strcmp((char*)node->name, "epigraph") == 0)
		{
			print_unsupported_tag("epigraph");
		}
		else if(strcmp((char*)node->name, "image") == 0)
			parse_image(node, text_buff, text_buff_end);
		else if(strcmp((char*)node->name, "poem") == 0)				// стихотворение
		{
			print_unsupported_tag("poem");
		}
		else if(strcmp((char*)node->name, "subtitle") == 0)			// подзаголовок
			parse_subtitle(node, text_buff, text_buff_end);
		else if(strcmp((char*)node->name, "cite") == 0)				// цитата
		{
			//print_unsupported_tag("cite");
			parse_cite(node, text_buff, text_buff_end);
		}
		else if(strcmp((char*)node->name, "table") == 0)			// таблица
		{
			print_unsupported_tag("table");
		}

		node = node->next;
	}
	return 0;
}

