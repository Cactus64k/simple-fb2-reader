#ifndef FB2_FICTIONBOOK_BODY_SECTION_TABLE_TABLE_CHUNKS_H_
#define FB2_FICTIONBOOK_BODY_SECTION_TABLE_TABLE_CHUNKS_H_

	#include "../section_chunks.h"

	int parse_table					(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int table_put_line				(FB2_READER_BOOK_VIEW* obj, GtkTextIter* text_buff_end, glong* cells_width, size_t cells_count, const char* start, const char* middle, const char* end);
	int table_get_size				(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, glong** width, size_t* cells_count);
	int table_tr_is_next			(xmlNode* node);


#endif /* FB2_FICTIONBOOK_BODY_SECTION_TABLE_TABLE_CHUNKS_H_ */
