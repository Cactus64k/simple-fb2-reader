#include "fb2_chunks.h"

int parse_fb2(char* file_path)
{
	assert(file_path != NULL);

	FB2_READER_TEXT_VIEW* book_text_view	= &(GLOBAL_FB2_READER.book_text_view);
	GtkTextBuffer* text_buff				= book_text_view->text_buff;


	xmlDocPtr file_tree = xmlReadFile(file_path, NULL, XML_PARSE_COMPACT | XML_PARSE_NONET);

	if(file_tree != NULL)
	{
		xmlNode* root = file_tree->children;
		GtkTextIter text_buff_end;

		assert(root != NULL);

		gtk_text_buffer_get_end_iter(text_buff, &text_buff_end);

		while(root != NULL)		// ищем рут
		{
			if((root->type == XML_ELEMENT_NODE) && (strcmp((char*)root->name, "FictionBook") == 0))
				break;

			root = root->next;
		}

		if(root != NULL)
		{
			xmlNode* node = root->children;

			//**************************************************************************

			while(node != NULL)
			{
				if(node->type == XML_ELEMENT_NODE)
				{
					if(strcmp((char*)node->name, "stylesheet") == 0)
					{

					}
					else if(strcmp((char*)node->name, "binary") == 0)
						parse_book_binary(book_text_view, node);
				}

				node = node->next;
			}

			//**************************************************************************

			node = root->children;

			while(node != NULL)
			{
				if((node->type == XML_ELEMENT_NODE) && (strcmp((char*)node->name, "description") == 0))
				{
					parse_book_description(book_text_view, node, &text_buff_end);
				}

				node = node->next;
			}

			//**************************************************************************

			node = root->children;

			while(node != NULL)
			{
				if((node->type == XML_ELEMENT_NODE) && (strcmp((char*)node->name, "body") == 0))
				{
					if(node->properties == NULL)
					{
						GtkTextIter text_buff_start;

						book_text_view->save_section	= TRUE;

						parse_body(book_text_view, node, &text_buff_end);

						gtk_text_buffer_get_start_iter(text_buff, &text_buff_start);
						gtk_text_buffer_apply_tag_by_name(text_buff, "default_tag", &text_buff_start, &text_buff_end);
					}
					else
					{
						xmlAttr* node_properties = node->properties;

						while(node_properties != NULL)
						{
							if(strcmp((char*)node_properties->name, "name") == 0)
							{
								char* properties_value = (char*)(node_properties->children->content);
								if((strcmp(properties_value, "notes") == 0) || (strcmp(properties_value, "comments") == 0))
								{
									GtkTextIter text_buff_start;

									book_text_view->save_section	= FALSE;

									parse_body(book_text_view, node, &text_buff_end);

									gtk_text_buffer_get_start_iter(text_buff, &text_buff_start);
									gtk_text_buffer_apply_tag_by_name(text_buff, "default_tag", &text_buff_start, &text_buff_end);

								}
							}

							node_properties = node_properties->next;
						}
					}
				}

				node = node->next;
			}

			//**************************************************************************

			printf("End read book\n");
		}
		else
			fputs("Wrong fb2 book format. no FictionBook tag found\n", stderr);

		xmlFreeDoc(file_tree);
	}
	else
		fprintf(stderr, "Unable parsing file: %s\n", file_path);

	xmlCleanupParser();

	return 0;
}
