project(Utils LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup()
qt_add_library(${PROJECT_NAME} STATIC
    Logger/Logger.cpp
    Logger/Logger.h
    DataBase/Database.h
    DataBase/Database.cpp
)

add_subdirectory(
    "${CMAKE_SOURCE_DIR}/third-party/spdlog"
    "${CMAKE_BINARY_DIR}/third-party/spdlog"
)

add_subdirectory(
    "${CMAKE_SOURCE_DIR}/third-party/sqlite"
    "${CMAKE_BINARY_DIR}/third-party/sqlite"
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        spdlog::spdlog_header_only
    PRIVATE
        Qt::Core
        Qt::Quick
        sqlite3
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
