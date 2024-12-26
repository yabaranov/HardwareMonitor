cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(SensorDatabase LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

add_library(${PROJECT_NAME} STATIC
    SensorDatabase.h SensorDatabase.cpp
    SensorLogTask.h SensorLogTask.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Core
        Utils
        Net
)

set(SENSOR_LOGS_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SensorLogs")

file(MAKE_DIRECTORY ${SENSOR_LOGS_DIR})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
