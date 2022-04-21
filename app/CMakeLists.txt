cmake_minimum_required(VERSION 3.7)
project(ctest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions ("-Wall -Wextra -Wpedantic -Weffc++ -Wconversion -Wunreachable-code -Wold-style-cast -Wuninitialized")

set(SOURCES
        editor.c 
        load.c 
        show.c 
        text/append_line.c 
        text/create_text.c 
        text/process_forward.c 
        text/remove_all.c 
        save.c m.c 
        showwordendings.c 
        z.c 
        dd.c
        )

set(HEADERS
        common.h 
        text/_text.h
        text/text.h
        )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# target_link_libraries(${PROJECT_NAME})