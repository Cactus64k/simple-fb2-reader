#include "../chunks.h"

int create_config_dir()
{
	char buff[4069];
	int res = 0;
	const char* conf_dir = g_get_user_config_dir();
	assert(conf_dir != NULL);

	snprintf(buff, sizeof(buff), "%s/simple-fb2-reader/", conf_dir);
	res = mkdir(buff, 0766);
	if(res == -1 && errno != EEXIST)
		fprintf(stderr, "failed to create folder: %s\n %s\n", buff, strerror(errno));

	snprintf(buff, sizeof(buff), "%s/simple-fb2-reader/books/", conf_dir);
	res = mkdir(buff, 0766);
	if(res == -1 && errno != EEXIST)
		fprintf(stderr, "failed to create folder: %s\n %s\n", buff, strerror(errno));

	return 0;
}
