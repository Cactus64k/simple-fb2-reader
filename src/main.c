#include "chunks.h"

#define TRANSLATION_DOMAIN "simple-fb2-reader"
#define TRANSLATION_DIR_NAME "/usr/share/locale/"


extern char _binary_simple_fb2_reader_glade_start;
extern char _binary_simple_fb2_reader_glade_end;


int main(int argc,	char *argv[])
{
	//g_mem_set_vtable(glib_mem_profiler_table);

	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	setlocale(LC_ALL, "");
	bindtextdomain(TRANSLATION_DOMAIN, TRANSLATION_DIR_NAME);
	bind_textdomain_codeset(TRANSLATION_DOMAIN, "UTF-8");
	textdomain(TRANSLATION_DOMAIN);

	gtk_init(&argc, &argv);

	GtkBuilder* builder = gtk_builder_new();

	gtk_builder_set_translation_domain(builder, TRANSLATION_DOMAIN);

	char* gui_start		= &_binary_simple_fb2_reader_glade_start;
	char* gui_end		= &_binary_simple_fb2_reader_glade_end;
	uintptr_t gui_len	= (uintptr_t)(gui_end-gui_start);

	guint result = gtk_builder_add_from_string(builder, gui_start, gui_len, NULL);
	assert(result != 0);

	gtk_builder_connect_signals(builder, NULL);

	//**********************************************************************************************

	main_wnd_init(builder, &GLOBAL_FB2_READER);
	search_wnd_init(builder, &GLOBAL_SEARCH_WND);
	encode_wnd_init(builder, &GLOBAL_ENCODE_DIALOG);

	g_object_unref(G_OBJECT(builder));

	if(argc == 2)
	{
		reader_open_book(argv[1]);
	}

	#ifdef DEBUG
		char test_path[] = "/home/cactus/example.fb2";

		reader_open_book(test_path);
		//open_book("/home/cactus/gamilton_piter_obnazhyonnyi_bog_fenomen.fb2");
	#endif

	gtk_main();

	return 0;
}
