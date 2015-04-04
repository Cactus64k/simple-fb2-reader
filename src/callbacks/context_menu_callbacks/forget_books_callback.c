#include "../callbacks_chunk.h"

int rrmdirs(char* path_buff, size_t path_buff_max_size);

void forger_books_imagemenuitem_activate_cb(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkMessageDialog* forget_book_dialog	= GLOBAL_FB2_READER.forget_books_dialog;

	if(gtk_dialog_run(GTK_DIALOG(forget_book_dialog)) == 2)
	{
		const char* conf_dir = g_get_user_config_dir();
		assert(conf_dir != NULL);

		char buff[4096];
		snprintf(buff, sizeof(buff), "%s/simple-fb2-reader/books", conf_dir);

		rrmdirs(buff, sizeof(buff));

		mkdir(buff, 0766);
	}

	gtk_widget_hide(GTK_WIDGET(forget_book_dialog));

}

int rrmdirs(char* path_buff, size_t path_buff_max_size)
{
	struct stat st;
	struct dirent* cur_dir;

	if(stat(path_buff, &st) == 0)
	{
		if(S_ISDIR(st.st_mode))
		{
			size_t path_buff_size = strlen(path_buff);

			DIR* d = opendir(path_buff);
			if(d != NULL)
			{
				while((cur_dir = readdir(d)) != NULL)
				{
					if(strcmp(cur_dir->d_name, "..") && strcmp(cur_dir->d_name, "."))
					{
						strncat(path_buff, "/",				path_buff_max_size-1);
						strncat(path_buff, cur_dir->d_name,	path_buff_max_size-1);

						rrmdirs(path_buff, path_buff_max_size);

						path_buff[path_buff_size] = 0;
					}
				}

				closedir(d);

				rmdir(path_buff);
			}
			else
				return -2;
		}
		else
			remove(path_buff);

	}
	else
		return -1;

	return 0;
}
