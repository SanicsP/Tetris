

set(SRC_FILES
    piece.c
    piece_grid.c    
)

set(LIB_NAME lib_tetris)

set(CSFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/CSFML/include/)

set(CSFML_COMPILE_DEFINITIONS SFML_STATIC)


set(CSFML_LINK_DIR ${CMAKE_SOURCE_DIR}/CSFML/lib/gcc/)

set(CSFML_LINK_LIBRARIES 
    ${CSFML_LINK_DIR}/libcsfml-graphics.a
    ${CSFML_LINK_DIR}/libcsfml-window.a
    ${CSFML_LINK_DIR}/libcsfml-system.a
)



add_library(${LIB_NAME} STATIC ${SRC_FILES})

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CSFML_INCLUDE_DIR})
target_compile_definitions(${LIB_NAME} PUBLIC ${CSFML_COMPILE_DEFINITIONS})
target_link_libraries(${LIB_NAME} PUBLIC ${CSFML_LINK_LIBRARIES})



