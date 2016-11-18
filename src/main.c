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

	char* book_path = NULL;
	gboolean print_version = FALSE;

	GOptionEntry cmd_options[]	= {
									{"book",	'b',	0,	G_OPTION_ARG_FILENAME,	&book_path,	_C("Local path to book"), "/local/path/book.fb2"},
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
		g_log(NULL, G_LOG_LEVEL_ERROR, "%s", error->message);
		g_error_free(error);
		error = NULL;
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
				g_warning("Failed to load gui construct file %s", GUI_CONSTRUCT_PATH);
				exit(EXIT_FAILURE);
			}

			APP app;
			memset(&app, 0, sizeof(APP));

			reader_app_config(&app);
			reader_app_gui(&app, builder);
			reader_search_wnd(&app, builder);
			reader_create_text_tags(&app);
			reader_books_db_init(&app);

			char* color_theme	= g_key_file_get_string(app.app_config, "app", "color_theme", NULL);
			reader_set_color_theme(&app, color_theme);
			g_free(color_theme);

			gtk_builder_connect_signals(builder, &app);

			if((book_path != NULL) && (g_file_test(book_path, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_REGULAR) == TRUE))
				reader_open_book(&app, book_path);
			else
				reader_start_screen(&app);

			g_free(book_path);

			gtk_main();
		}
	}

	g_option_context_free(cmd_context);

	g_strfreev(cmd_line);

	return EXIT_SUCCESS;
}
