#include "fb2_chunks.h"

int parse_fb2(char* path, GtkTextBuffer* text_buff)
{
	GHashTable* binary_hash_table	= GLOBAL_FB2_READER.binary_hash_table;

	assert(text_buff != NULL);
	assert(path != NULL);

	xmlDocPtr file_tree = xmlReadFile(path, NULL, XML_PARSE_COMPACT | XML_PARSE_NONET);

	if(file_tree != NULL)
	{
		xmlNode* root = file_tree->children;
		xmlNode* node = root->children;
		GtkTextIter text_buff_end;

		gtk_text_buffer_get_end_iter(text_buff, &text_buff_end);


		//**************************************************************************

		/*while(node != NULL)
		{
			if(strcmp((char*)node->name, "stylesheet") == 0)
			{

			}

			node = node->next;
		}
		*/

		//**************************************************************************

		node = root->children;

		while(node != NULL)
		{
			if(strcmp((char*)node->name, "binary") == 0)
				parse_book_binary(node, binary_hash_table);

			node = node->next;
		}

		//**************************************************************************

		node = root->children;

		while(node != NULL)
		{
			if(strcmp((char*)node->name, "description") == 0)
			{
				parse_book_description(node, text_buff, &text_buff_end);
			}

			node = node->next;
		}

		//**************************************************************************

		node = root->children;

		while(node != NULL)
		{
			if(strcmp((char*)node->name, "body") == 0)
			{
				if(node->properties == NULL)
				{
					GtkTextTag* default_tag	= GLOBAL_FB2_READER.default_tag;
					GtkTextIter text_buff_start;

					parse_book_body(node, text_buff, &text_buff_end);

					gtk_text_buffer_get_start_iter(text_buff, &text_buff_start);

					gtk_text_buffer_apply_tag(text_buff, default_tag, &text_buff_start, &text_buff_end);
				}

				else if(strcmp((char*)node->properties, "notes") == 0)
				{

				}
				else if(strcmp((char*)node->properties, "comments") == 0)
				{

				}
			}


			node = node->next;
		}

		//**************************************************************************

		printf("End read book\n");


		xmlFreeDoc(file_tree);
		xmlCleanupParser();
	}

	return 0;
}
