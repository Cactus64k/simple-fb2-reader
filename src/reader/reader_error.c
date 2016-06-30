#include "reader_chunks.h"

int reader_show_error(APP* app, const char* message)
{
	fprintf(stderr, message);
	gtk_message_dialog_format_secondary_markup(app->error_messagedialog, message);
	gtk_dialog_run(GTK_DIALOG(app->error_messagedialog));
	gtk_widget_hide(GTK_WIDGET(app->error_messagedialog));

	return EXIT_SUCCESS;
}
