#ifndef READER_READER_APP_READER_APP_H_
	#define READER_READER_APP_READER_APP_H_
	#include "../reader_chunks.h"

	int reader_app_config		(APP* app);
	int reader_app_gui			(APP* app, GtkBuilder* builder);
	int reader_close_app		(APP* app);
	int reader_search_wnd		(APP* app, GtkBuilder* builder);



#endif /* READER_READER_APP_READER_APP_H_ */
