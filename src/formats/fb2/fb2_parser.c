#include "fb2_chunks.h"

int parse_fb2_file(APP* app, char* file_path)
{
	g_return_val_if_fail(file_path != NULL,	EXIT_FAILURE);
	g_return_val_if_fail(app != NULL,		EXIT_FAILURE);

	GtkTextBuffer* text_buff	= app->text_buff;


	xmlDocPtr doc = xmlReadFile(file_path, NULL, XML_PARSE_COMPACT | XML_PARSE_NONET | XML_PARSE_NOERROR);

	if(doc != NULL)
	{
		xmlNode* root = xmlDocGetRootElement(doc);

		while(root != NULL)
		{
			if((root->type == XML_ELEMENT_NODE) && (strcmp((char*)root->name, "FictionBook") == 0))
				break;

			root = root->next;
		}

		gtk_text_buffer_set_text(text_buff, "", 0);

		GtkTextIter text_buff_end;
		gtk_text_buffer_get_end_iter(text_buff, &text_buff_end);

		parse_fb2_function_book(app, root, &text_buff_end);

		xmlFreeDoc(doc);
	}
	else
		g_log(NULL, G_LOG_LEVEL_ERROR, "Failed to parsing fb2 file");

	xmlCleanupParser();

	return EXIT_SUCCESS;
}
