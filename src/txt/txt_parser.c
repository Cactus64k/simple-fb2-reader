#include "txt_chunks.h"

int parse_txt(char* file_path, char* encode)
{
	g_return_val_if_fail(file_path != NULL, -1);
	g_return_val_if_fail(encode != NULL, -2);

	GtkTextBuffer* text_buff = GLOBAL_FB2_READER.book_text_view.text_buff;

	char buff_src[1024];
	char buff_dst[1024*6];

	FILE* f = fopen(file_path, "r");

	if(f != NULL)
	{

		gtk_text_buffer_set_text(text_buff, "", 0);

		GtkTextIter text_buff_end;
		gtk_text_buffer_get_end_iter(text_buff, &text_buff_end);

		iconv_t cd = iconv_open("UTF-8", encode);

		while(!feof(f))
		{
			char* in_buff	= buff_src;
			char* out_buff	= buff_dst;

			size_t read_count = fread(in_buff, 1, sizeof(buff_src), f);

			size_t in_buff_left = read_count;
			size_t out_buff_left = sizeof(buff_dst);

			size_t res = iconv(cd,	&in_buff,	&in_buff_left,
									&out_buff,	&out_buff_left);
			if(res == (size_t)-1)
			{
				char* error_text = strerror(errno);
				fprintf(stderr, _C("ERROR: failed to encode txt file: %s\n"), error_text);

				//break;
			}

			gtk_text_buffer_insert(text_buff, &text_buff_end, buff_dst, sizeof(buff_dst)-out_buff_left);

			if(in_buff_left != 0)
				fseek(f, -(ssize_t)in_buff_left, SEEK_CUR);
		}

		iconv_close(cd);
		fclose(f);

		GtkTextIter text_buff_start_iter;
		GtkTextIter text_buff_end_iter;

		gtk_text_buffer_get_bounds(text_buff, &text_buff_start_iter, &text_buff_end_iter);


		gtk_text_buffer_apply_tag_by_name(text_buff, "default_tag", &text_buff_start_iter, &text_buff_end_iter);
	}
	else
		fprintf(stderr, _C("ERROR: failed to open txt file: %s\n"), file_path);
	return 0;
}
