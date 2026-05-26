cmake_minimum_required(VERSION 3.15)

project(TETRIS VERSION 0.1.0 
        DESCRIPTION "A tetris game implementation made with c."
        LANGUAGES C
)

set(CMAKE_C_STANDARD 99)

set(CORE_MODULE_PATH ${CMAKE_SOURCE_DIR}/src/core)
        set(CORE_MODULE_FILES 
                ${CORE_MODULE_PATH}/game.c
                ${CORE_MODULE_PATH}/renderer.c
                ${CORE_MODULE_PATH}/utils.c
                ${CORE_MODULE_PATH}/main.c
                ${CORE_MODULE_PATH}/int_queue.c

        )

set(SAVE_MODULE_PATH ${CMAKE_SOURCE_DIR}/src/save)
        set(SAVE_MODULE_FILES 
                ${SAVE_MODULE_PATH}/score_data.c
        )

set(TETRIS_MODULE_PATH ${CMAKE_SOURCE_DIR}/src/tetris)
        set(TETRIS_MODULE_FILES 
                ${TETRIS_MODULE_PATH}/piece_grid.c
                ${TETRIS_MODULE_PATH}/piece.c
        )

set(UI_MODULE_PATH ${CMAKE_SOURCE_DIR}/src/ui)
        set(UI_MODULE_FILES 
                ${UI_MODULE_PATH}/
                ${UI_MODULE_PATH}/
        )

set(TESTS_MODULE_PATH ${CMAKE_SOURCE_DIR}/src/tests)
        set(TESTS_MODULE_FILES 
                ${TESTS_MODULE_PATH}/tetris_tests.c
        )

#---------------------- CSFML LIB LINKING ---------------------------#
        
        set(CSFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/CSFML/include/)
        
        set(CSFML_LINK_DIR ${CMAKE_SOURCE_DIR}/CSFML/lib/gcc/)
        
        set(CSFML_LINK_LIBRARIES 
                ${CSFML_LINK_DIR}/libcsfml-graphics.a
                ${CSFML_LINK_DIR}/libcsfml-window.a
                ${CSFML_LINK_DIR}/libcsfml-system.a
        )

        set(CSFML_COMPILE_DEFINITIONS SFML_STATIC)
        
#----------------------------------------------------------------------#


add_executable(TETRIS 
        ${CORE_MODULE_FILES} 
        ${TETRIS_MODULE_FILES}
        ${TESTS_MODULE_FILES}
        ${SAVE_MODULE_FILES}
)

target_compile_definitions(TETRIS PUBLIC ${CSFML_COMPILE_DEFINITIONS})

target_compile_options(TETRIS PUBLIC -Wall -O3)

foreach(X IN ITEMS 
                ${CSFML_INCLUDE_DIR} 
                ${CORE_MODULE_PATH} 
                ${TETRIS_MODULE_PATH}
                ${TESTS_MODULE_PATH}
                ${SAVE_MODULE_PATH}

        )
        target_include_directories(TETRIS PUBLIC ${X})
        message(STATUS "[CMAKE TETRIS BUILD]\tMDOULE \"${X}\" ADDED")
endforeach()

target_link_libraries(TETRIS PUBLIC ${CSFML_LINK_LIBRARIES})

file(GLOB DLL_FILES "${CMAKE_SOURCE_DIR}/dlls/*.dll")

foreach(X IN LISTS DLL_FILES) 
        message(STATUS "[CMAKE DLL FILES] ${X} ADDED")
        file(COPY "${X}" DESTINATION ${CMAKE_BINARY_DIR})
endforeach()