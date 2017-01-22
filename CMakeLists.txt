cmake_minimum_required (VERSION 3.0.2) 
 
set (PROJECT simple-fb2-reader) 
 
project (${PROJECT} C) 
 
set (HEADERS 
	src/reader/reader_app/reader_app.h
	src/reader/reader_chunks.h
	src/reader/reader_book/reader_book_chunks.h
	src/callbacks/callbacks_chunk.h
	src/formats/formats_chunks.h
	src/formats/fb2/fb2_chunks.h
	src/formats/fb2/FictionBook/attributes/attributes_chunks.h
	src/formats/fb2/FictionBook/description/description_chunks.h
	src/formats/fb2/FictionBook/body/section/table/table_chunks.h
	src/formats/fb2/FictionBook/body/section/section_chunks.h
	src/formats/fb2/FictionBook/body/section/p/p_chunks.h
	src/formats/fb2/FictionBook/body/body_chunks.h
	src/formats/fb2/FictionBook/FictionBook_chunks.h
	src/formats/fb2_zip/fb2_zip_chunks.h
	src/chunks.h)

set (SOURCES 
	src/reader/reader_app/reader_app_config.c
	src/reader/reader_app/reader_close_app.c
	src/reader/reader_app/reader_app_gui.c
	src/reader/reader_app/reader_search_wnd.c
	src/reader/reader_color_theme.c
	src/reader/reader_scroll.c
	src/reader/reader_text_tags.c
	src/reader/reader_start_screen.c
	src/reader/reader_book/reader_open_book.c
	src/reader/reader_book/reader_books_db.c
	src/reader/reader_book/reader_close_book.c
	src/reader/reader_book/reader_book_hash.c
	src/reader/reader_book/reader_add_book_to_start_screen.c
	src/callbacks/text_view_callback/popup_menu_callback.c
	src/callbacks/text_view_callback/link_tag_enevt_callback.c
	src/callbacks/text_view_callback/motion_event_callback.c
	src/callbacks/text_view_callback/scroll_event_callback.c
	src/callbacks/text_view_callback/tooltip_callback.c
	src/callbacks/main_wnd_callbacks.c
	src/callbacks/search_wnd_callbacks.c
	src/callbacks/context_menu_callbacks/navigation_section_callback.c
	src/callbacks/context_menu_callbacks/exit_callback.c
	src/callbacks/context_menu_callbacks/auto_scroll_callback.c
	src/callbacks/context_menu_callbacks/open_file_callback.c
	src/callbacks/context_menu_callbacks/close_book_callback.c
	src/callbacks/context_menu_callbacks/backward_callback.c
	src/callbacks/context_menu_callbacks/navigation_callback.c
	src/callbacks/context_menu_callbacks/about_callback.c
	src/callbacks/context_menu_callbacks/color_theme_callback.c
	src/callbacks/context_menu_callbacks/book_search_callback.c
	src/formats/fb2/fb2_parser.c
	src/formats/fb2/FictionBook/attributes/id.c
	src/formats/fb2/FictionBook/description/book_title.c
	src/formats/fb2/FictionBook/description/title-info.c
	src/formats/fb2/FictionBook/description/coverpage.c
	src/formats/fb2/FictionBook/description/annotation.c
	src/formats/fb2/FictionBook/description/description.c
	src/formats/fb2/FictionBook/body/section/subtitle.c
	src/formats/fb2/FictionBook/body/section/date.c
	src/formats/fb2/FictionBook/body/section/table/table.c
	src/formats/fb2/FictionBook/body/section/table/table_put_line.c
	src/formats/fb2/FictionBook/body/section/table/tr.c
	src/formats/fb2/FictionBook/body/section/table/table_tr_next.c
	src/formats/fb2/FictionBook/body/section/table/table_size.c
	src/formats/fb2/FictionBook/body/section/style.c
	src/formats/fb2/FictionBook/body/section/cite.c
	src/formats/fb2/FictionBook/body/section/empty_line.c
	src/formats/fb2/FictionBook/body/section/p/p_length.c
	src/formats/fb2/FictionBook/body/section/p/p_text.c
	src/formats/fb2/FictionBook/body/section/p/p.c
	src/formats/fb2/FictionBook/body/section/poem.c
	src/formats/fb2/FictionBook/body/section/text_autor.c
	src/formats/fb2/FictionBook/body/section/image_inline.c
	src/formats/fb2/FictionBook/body/section/section.c
	src/formats/fb2/FictionBook/body/section/a.c
	src/formats/fb2/FictionBook/body/image.c
	src/formats/fb2/FictionBook/body/title.c
	src/formats/fb2/FictionBook/body/body.c
	src/formats/fb2/FictionBook/body/epigraph.c
	src/formats/fb2/FictionBook/FictionBook.c
	src/formats/fb2/FictionBook/binary/binary.c
	src/formats/fb2_zip/fb2_zip_parser.c
	src/main.c) 

set (LIBRARIES
	ssh
	pthread)
	
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
 
add_executable (${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries (${PROJECT} ${LIBRARIES})

install (TARGETS ${PROJECT} RUNTIME DESTINATION /usr/bin)
