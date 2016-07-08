#include "../fb2_zip/fb2_zip_chunks.h"

int parse_fb2_zip_file(APP* app, char* file_path)
{
	GtkTextBuffer* text_buff	= app->text_buff;

	int zip_error = 0;
	struct zip* f = zip_open(file_path, ZIP_CHECKCONS, &zip_error);
	if(f != NULL)
	{
		zip_int64_t file_count = zip_get_num_entries(f, 0);

		struct zip_stat st;
		zip_stat_init(&st);

		for(size_t i=0; i<file_count; i++)
		{
			zip_stat_index(f, i, 0,  &st);
			const char* z_file_name = st.name;
			if(reader_get_book_type((char*)z_file_name) == BOOK_TYPE_FB2)
			{
				struct zip_file* zf	= zip_fopen_index(f, i, 0);
				if(zf != NULL)
				{
					char buff[2048];
					zip_int64_t rc			= 0;
					xmlParserCtxtPtr ctxt	= xmlCreatePushParserCtxt(NULL, NULL, NULL, 0, NULL);

					while((rc = zip_fread(zf, buff, sizeof(buff))) > 0)
						xmlParseChunk(ctxt, buff, rc, 0);

					zip_fclose(zf);
					xmlParseChunk(ctxt, buff, 0, 1);

					int parsing_status = ctxt->wellFormed;

					if(parsing_status == 1)
					{
						xmlDocPtr xml_doc	= ctxt->myDoc;

						if(xml_doc != NULL)
						{
							xmlNode* file_tree	= xml_doc->children;

							gtk_text_buffer_set_text(text_buff, "", 0);

							GtkTextIter text_buff_end;
							gtk_text_buffer_get_end_iter(text_buff, &text_buff_end);

							parse_fb2_function_book(app, file_tree, &text_buff_end);

							xmlFreeDoc(xml_doc);
						}
						else
							g_error("Xml is well parsed, but pointer is NULL");
					}
					else
						g_error("Failed to parsing fb2 file");

					xmlFreeParserCtxt(ctxt);

					if(parsing_status == 1)
						break;
				}
				else
					g_error("Failed to unpack fb2 file");
			}
		}
		zip_close(f);
	}
	else
		g_error("Failed to open zip file");

	return EXIT_SUCCESS;
}
