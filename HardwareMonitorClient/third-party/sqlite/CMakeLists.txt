project(sqlite3 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC sqlite3.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})