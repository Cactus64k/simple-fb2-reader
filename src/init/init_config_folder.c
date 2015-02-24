#include "../chunks.h"

int create_config_dir()
{
	char buff[1024];
	int res = 0;
	const char* conf_dir = g_get_user_config_dir();
	assert(conf_dir != NULL);

	snprintf(buff, sizeof(buff), "%s/simple-fb2-reader/books/", conf_dir);
	g_mkdir_with_parents(buff, 0766);
	if(res == -1 && errno != EEXIST)
		fprintf(stderr, "failed to create folder: %s\n %s\n", buff, strerror(errno));

	return 0;
}
