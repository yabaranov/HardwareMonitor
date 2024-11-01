project(Utils LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup()
qt_add_library(${PROJECT_NAME} STATIC
    Logger/Logger.cpp
    Logger/Logger.h
)

add_subdirectory(
    "${CMAKE_SOURCE_DIR}/third-party/spdlog"
    "${CMAKE_BINARY_DIR}/third-party/spdlog"
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Quick
        spdlog::spdlog_header_only
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
