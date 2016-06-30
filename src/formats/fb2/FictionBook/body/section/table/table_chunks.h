#ifndef FB2_FICTIONBOOK_BODY_SECTION_TABLE_TABLE_CHUNKS_H_
#define FB2_FICTIONBOOK_BODY_SECTION_TABLE_TABLE_CHUNKS_H_

	#include "../section_chunks.h"

	int parse_fb2_table					(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_table_put_line		(APP* app, GtkTextIter* text_buff_end, glong* cells_width, size_t cells_count, const char* start, const char* middle, const char* end);
	int parse_fb2_table_get_size		(APP* app, xmlNode* parent_node, glong** width, size_t* cells_count);
	int parse_fb2_table_tr_is_next		(xmlNode* node);

	#define MAX_CELL_LENGTH 25


#endif /* FB2_FICTIONBOOK_BODY_SECTION_TABLE_TABLE_CHUNKS_H_ */
