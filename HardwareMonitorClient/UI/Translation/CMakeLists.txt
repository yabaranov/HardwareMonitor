cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(Translation LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Qml LinguistTools)

qt_standard_project_setup()

add_library(${PROJECT_NAME} STATIC
    LanguageChooser.h
    LanguageChooser.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Qml
)

set(FILES_TO_TRANSLATE
    ../Qml/Main.qml

    ../Qml/LoginPage.qml

    ../Qml/SensorTableRepeater.qml

    ../Qml/NetMenu.qml
    ../Qml/ViewMenu.qml
    ../Qml/OptionsMenu.qml
)

set(TS_FILES
    translate_ru.ts
    translate_en.ts
)
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Translations")

option(UPDATE_TRANSLATIONS
"Update source translation (Translation/*.ts)." ON
)

if(UPDATE_TRANSLATIONS)
    message(STATUS "UPDATE_TRANSLATIONS option is set.")
    qt6_create_translation(QM_FILES ${FILES_TO_TRANSLATE} ${TS_FILES})
else()
    qt6_add_translation(QM_FILES ${TS_FILES})
endif()

add_custom_target(GenerateTranslation
    DEPENDS ${QM_FILES}
)

set_property(DIRECTORY
    PROPERTY CLEAN_NO_CUSTOM TRUE
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
