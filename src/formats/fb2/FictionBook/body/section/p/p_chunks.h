#ifndef FB2_FICTIONBOOK_BODY_SECTION_P_P_CHUNKS_H_
#define FB2_FICTIONBOOK_BODY_SECTION_P_P_CHUNKS_H_

	#include "../section_chunks.h"

	int parse_fb2_p					(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_p__		(APP* app, xmlNode* parent_node, GtkTextIter* text_buff_end);
	int parse_fb2_p_get_text		(xmlNode* parent_node, GString* buff);
	int parse_fb2_p_get_length		(xmlNode* parent_node, glong* len);

#endif /* FB2_FICTIONBOOK_BODY_SECTION_P_P_CHUNKS_H_ */
