#include "chunks.h"

int main(int argc,	char *argv[])
{
	//g_mem_set_vtable(glib_mem_profiler_table);

	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	setlocale(LC_ALL, "");

	char* domain = textdomain(PACKAGE_NAME);
	assert(domain != NULL);

	bind_textdomain_codeset(PACKAGE_NAME, "UTF-8");
	textdomain(PACKAGE_NAME);

	gtk_init(&argc, &argv);

	GtkBuilder* builder = gtk_builder_new();

	gtk_builder_set_translation_domain(builder, PACKAGE_NAME);

	guint result = gtk_builder_add_from_file(builder, GUI_CONSTRUCT_PATH, NULL);
	if(result == 0)
	{
		fprintf(stderr, "ERROR: Failed to load gui construct file %s\n", GUI_CONSTRUCT_PATH);
		exit(EXIT_FAILURE);
	}

	gtk_builder_connect_signals(builder, NULL);

	//**********************************************************************************************

	init_main_wnd(builder, &GLOBAL_FB2_READER);
	init_search_wnd(builder, &GLOBAL_SEARCH_WND);
	init_encode_wnd(builder, &GLOBAL_ENCODE_DIALOG);

	g_object_unref(G_OBJECT(builder));

	if(argc == 2)
	{
		reader_open_book(argv[1]);
	}

	#ifdef DEBUG
		//char test_path[] = "/home/cactus/Книги/example.fb2";

		//reader_open_book(test_path);
		//open_book("/home/cactus/gamilton_piter_obnazhyonnyi_bog_fenomen.fb2");
	#endif

	gtk_main();

	return 0;
}
