#include "fb2_chunks.h"

int parse_fb2_file(char* file_path)
{
	g_return_val_if_fail(file_path != NULL, -1);

	FB2_READER_BOOK_VIEW* book_text_view	= &(GLOBAL_FB2_READER.book_text_view);
	GtkTextBuffer* text_buff				= book_text_view->text_buff;


	xmlDocPtr file_tree = xmlReadFile(file_path, NULL, XML_PARSE_COMPACT | XML_PARSE_NONET);

	if(file_tree != NULL)
	{
		xmlNode* root = file_tree->children;

		while(root != NULL)		// ищем рут
		{
			if((root->type == XML_ELEMENT_NODE) && (strcmp((char*)root->name, "FictionBook") == 0))
				break;

			root = root->next;
		}

		gtk_text_buffer_set_text(text_buff, "", 0);

		GtkTextIter text_buff_end;
		gtk_text_buffer_get_end_iter(text_buff, &text_buff_end);

		parse_fb2_function_book(book_text_view, root, &text_buff_end);

		xmlFreeDoc(file_tree);
	}
	else
		fprintf(stderr, _C("ERROR: Failed to parsing fb2 file: %s\n"), file_path);

	xmlCleanupParser();

	return 0;
}
