#ifndef FB2_FICTIONBOOK_BODY_SECTION_P_P_CHUNKS_H_
#define FB2_FICTIONBOOK_BODY_SECTION_P_P_CHUNKS_H_

	#include "../section_chunks.h"

	int parse_p				(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_formated_text	(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int p_get_text			(xmlNode* parent_node, GString* buff);
	int p_get_length		(xmlNode* parent_node, glong* len);
	int parse_p_link		(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end);

#endif /* FB2_FICTIONBOOK_BODY_SECTION_P_P_CHUNKS_H_ */
