#include "txt_parser.h"

int parse_txt(char* file_path, char* encode)
{
	assert(file_path != NULL);
	assert(encode != NULL);

	GtkTextBuffer* text_buff = GLOBAL_FB2_READER.book_text_view.text_buff;

	const size_t buff_src_size = 1024;
	char buff_src[buff_src_size];
	char buff_dst[buff_src_size*6];

	FILE* f = fopen(file_path, "r");

	if(f != NULL)
	{

		GtkTextIter text_buff_end;
		gtk_text_buffer_get_end_iter(text_buff, &text_buff_end);

		iconv_t cd = iconv_open("UTF-8", encode);

		while(!feof(f))
		{
			char* in_buff	= buff_src;
			char* out_buff	= buff_dst;

			size_t read_count = fread(in_buff, 1, buff_src_size, f);

			size_t in_buff_left = read_count;
			size_t out_buff_left = sizeof(buff_dst);

			size_t res = iconv(cd,	&in_buff,	&in_buff_left,
									&out_buff,	&out_buff_left);
			if(res == (size_t)-1)
			{
				char* error_text = strerror(errno);
				fprintf(stderr, "TXT encode error: %s\n", error_text);

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
		fprintf(stderr, "Error reading file: %s\n", file_path);
	return 0;
}
