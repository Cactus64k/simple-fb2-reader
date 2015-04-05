#include "chunks.h"

int main(int argc,	char *argv[])
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	setlocale(LC_ALL, "");

	char* domain = textdomain(PACKAGE_NAME);
	assert(domain != NULL);

	bind_textdomain_codeset(PACKAGE_NAME, "UTF-8");
	textdomain(PACKAGE_NAME);

	char* book_file_path = NULL;
	gboolean print_version = FALSE;

	GOptionEntry cmd_options[]		= {
									{"book",	'b',	0,	G_OPTION_ARG_FILENAME,	&book_file_path,	_C("Local path to book"), "/local/path/book.fb2"},
									{"version",	'v',	0,	G_OPTION_ARG_NONE, 		&print_version,		_C("Print reader version"), NULL},
									{NULL}
								};


	GError *error				= NULL;

	GOptionContext *cmd_context	= g_option_context_new(NULL);
	g_option_context_set_help_enabled(cmd_context, TRUE);
	g_option_context_add_main_entries(cmd_context, cmd_options, NULL);


	gchar **cmd_line = g_strdupv(argv);
	gint cmd_count = argc;

	if(g_option_context_parse(cmd_context, &cmd_count, &cmd_line, &error) == FALSE)
	{
		fprintf(stderr, _C("ERROR: %s\n\n"), error->message);

		g_error_free(error);
	}
	else
	{
		if(print_version == TRUE)
		{
			printf("Simple FB2 Reader: %s\n", PACKAGE_VERSION);
		}
		else
		{
			gtk_init(&argc, &argv);

			GtkBuilder* builder = gtk_builder_new();

			gtk_builder_set_translation_domain(builder, PACKAGE_NAME);

			guint result = gtk_builder_add_from_file(builder, GUI_CONSTRUCT_PATH, NULL);
			if(result == 0)
			{
				fprintf(stderr, _C("ERROR: Failed to load gui construct file %s\n"), GUI_CONSTRUCT_PATH);
				exit(EXIT_FAILURE);
			}

			gtk_builder_connect_signals(builder, NULL);

			//**********************************************************************************************

			init_main_wnd(builder, &GLOBAL_FB2_READER);
			init_search_wnd(builder, &GLOBAL_SEARCH_WND);
			init_encode_wnd(builder, &GLOBAL_ENCODE_DIALOG);

			g_object_unref(G_OBJECT(builder));

			if(book_file_path != NULL)
			{
				if(reader_open_book(book_file_path) != 0)
					g_free(book_file_path);
			}


			gtk_main();
		}
	}

	g_option_context_free(cmd_context);

	g_strfreev(cmd_line);

	return 0;
}
