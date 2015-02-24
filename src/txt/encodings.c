#include "txt_chunks.h"

const char* european_enc[]	= {"ISO-8859-1", "ISO-8859-2", "ISO-8859-3", "ISO-8859-4", "ISO-8859-5", "ISO-8859-7", \
								"ISO-8859-9", "ISO-8859-10", "ISO-8859-13", "ISO-8859-14", "ISO-8859-15", "ISO-8859-16", \
								"ASCII", "KOI8-R", "KOI8-U", "KOI8-RU", "CP1250", "CP1251", "CP1252", "CP1253", "CP1254", \
								"CP1257", "CP850", "CP866", "CP1131", NULL};

const char* semitic_enc[]	= {"ISO-8859-6", "ISO-8859-8", "CP1255", "CP1256", "CP862", "CP864", NULL};

const char* japanece_enc[]	= {"EUC-JP", "SHIFT_JIS", "CP932", "ISO-2022-JP", "ISO-2022-JP-2", "ISO-2022-JP-1", \
								"EUC-JISX0213", "Shift_JISX0213", "ISO-2022-JP-3", NULL};

const char* chanece_enc[]	= {"EUC-CN", "HZ", "GBK", "CP936", "GB18030", "EUC-TW", "BIG5", "CP950", "BIG5-HKSCS", \
								"BIG5-HKSCS:2004", "BIG5-HKSCS:2001", "BIG5-HKSCS:1999", "ISO-2022-CN", "ISO-2022-CN-EXT", "BIG5-2003", NULL};

const char* korean_enc[]	= {"EUC-KR", "CP949", "ISO-2022-KR", "JOHAB", NULL};

const char* armenian_enc[]	= {"ARMSCII-8", NULL};

const char* gorgean_enc[]	= {"Georgian-Academy", "Georgian-PS", NULL};

const char* tajik_enc[]		= {"KOI8-T", NULL};

const char* turkmen_enc[]	= {"TDS565", NULL};

const char* kazah_enc[]		= {"PT154", "RK1048", NULL};

const char* thai_enc[]		= {"ISO-8859-11", "TIS-620", "CP874", NULL};

const char* laotian_enc[]	= {"MuleLao-1", "CP1133", NULL};

const char* vietnamece_enc[]= {"VISCII", "TCVN", "CP1258", NULL};

const char* unicode_enc[]	= {"UTF-8", "UCS-2", "UCS-2BE", "UCS-2LE", "UCS-4", "UCS-4BE", "UCS-4LE", "UTF-16", \
								"UTF-16BE", "UTF-16LE", "UTF-32", "UTF-32BE", "UTF-32LE", "UTF-7", NULL};


const char** encodings[] = {european_enc, semitic_enc, japanece_enc, chanece_enc, korean_enc, armenian_enc, gorgean_enc, \
							tajik_enc, turkmen_enc, kazah_enc, thai_enc, laotian_enc, vietnamece_enc, unicode_enc, NULL};

const char* human_language[] = {"European", "Semitic", "Japanece", "Chanece", "Korean", "Armenian", "Gorgean", "Tajik", "Turkmen", \
								"Kazah", "Thai", "Laotian", "Vietnamece", "Unicode"};

int fill_encode_treestore(GtkTreeStore* tree_store)
{
	size_t enc_type = 0;

	while(encodings[enc_type] != NULL)
	{
		size_t enc_pos = 0;
		GtkTreeIter iter;
		gtk_tree_store_append(tree_store, &iter, NULL);
		gtk_tree_store_set(tree_store, &iter,	ENCODE_NAME_COLUMN, human_language[enc_type],
												IS_ENCODE_COLUMN, FALSE, -1);

		while(encodings[enc_type][enc_pos] != NULL)
		{
			GtkTreeIter child_iter;
			const char* encode_name = encodings[enc_type][enc_pos];
			gtk_tree_store_append(tree_store, &child_iter, &iter);
			gtk_tree_store_set(tree_store, &child_iter,	ENCODE_NAME_COLUMN, encode_name,
														IS_ENCODE_COLUMN, TRUE, -1);

			enc_pos++;
		}

		enc_type++;
	}

	return 0;
}

int fill_encode_test_buffer(ENCODE_DIALOG* obj, char* file_path)
{
	char* buffer				= obj->src_buffer;
	size_t buff_size			= sizeof(obj->src_buffer);
	size_t* buffer_data_size	= &(obj->buffer_data_size);
	GtkTextBuffer* text_buff	= obj->textbuffer;

	FILE* f = fopen(file_path, "r");

	*buffer_data_size = fread(buffer, 1, buff_size, f);
	gtk_text_buffer_set_text(text_buff, "", -1);

	fclose(f);

	return 0;
}

char* encode_dialog_get_encode_name(ENCODE_DIALOG* obj)
{
	GtkTreeView* tree_view				= obj->treeview;
	GtkTreeSelection* tree_selection	= gtk_tree_view_get_selection(tree_view);
	GtkTreeModel* tree_model			= GTK_TREE_MODEL(obj->treestore);

	GtkTreeIter tree_iter;
	gboolean is_encode = FALSE;

	if(gtk_tree_selection_get_selected(tree_selection, NULL, &tree_iter) == TRUE)
	{
		gtk_tree_model_get(tree_model, &tree_iter, IS_ENCODE_COLUMN, &is_encode, -1);
		if(is_encode == TRUE)
		{
			char* encode_name = NULL;
			gtk_tree_model_get(tree_model, &tree_iter, ENCODE_NAME_COLUMN, &encode_name, -1);

			return encode_name;
		}
	}

	return NULL;
}
