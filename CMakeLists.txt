cmake_minimum_required(VERSION 3.1)

project(
    InputLatencyTester
    VERSION 0.1
    LANGUAGES C
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(src)

add_executable(${PROJECT_NAME} src/main.c)

IF (WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_SEARCH_START_STATIC ON
    LINK_SEARCH_END_STATIC ON
  )
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static -Wl,-subsystem,windows")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc -static -Wl,-subsystem,windows")

ENDIF()

set(CMAKE_DISABLE_TESTING ON)
set(RAYLIB_LIBTYPE "STATIC")
add_subdirectory(deps/raylib)





target_link_directories( ${PROJECT_NAME}
    PRIVATE deps/raylib/src
)

target_link_libraries(${PROJECT_NAME} raylib)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -Wall")