project(UI LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2 LinguistTools)

qt_standard_project_setup()

set(FILES_TO_TRANSLATE
    Qml/Main.qml

    Qml/LoginPage.qml

    Qml/SensorTableRepeater.qml

    Qml/NetMenu.qml
    Qml/ViewMenu.qml
    Qml/OptionsMenu.qml
)

set(TS_FILES
    Translations/translate_ru.ts
    Translations/translate_en.ts
)
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION "${CMAKE_BINARY_DIR}/bin/translations")

option(UPDATE_TRANSLATIONS
"Update source translation (Translations/*.ts)." ON
)

if(UPDATE_TRANSLATIONS)
    message(STATUS "UPDATE_TRANSLATIONS option is set.")
    qt6_create_translation(QM_FILES ${FILES_TO_TRANSLATE} ${TS_FILES})
else()
    qt6_add_translation(QM_FILES ${TS_FILES})
endif()

add_custom_target(Translations
    DEPENDS ${QM_FILES}
)

set_property(DIRECTORY
    PROPERTY CLEAN_NO_CUSTOM TRUE
)

qt_add_executable(${PROJECT_NAME}
    main.cpp

    Models/HardwareModel.h Models/HardwareModel.cpp
    Models/SensorModel.h Models/SensorModel.cpp
    Models/ModelManager.h Models/ModelManager.cpp

    DataMappers/SensorUnitProvider.h DataMappers/SensorUnitProvider.cpp
    DataMappers/SensorPrecisionProvider.h DataMappers/SensorPrecisionProvider.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "HardwareMonitorClient")

set_source_files_properties(Qml/AppSettings.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE true
)
qt_add_qml_module(${PROJECT_NAME}
    URI UI
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        Qml/Main.qml

        Qml/AppSettings.qml

        Qml/LoginPage.qml
        Qml/Error.qml

        Qml/HardwarePage.qml
        Qml/HardwareView.qml
        Qml/SensorTableRepeater.qml
        Qml/SensorTableView.qml
        Qml/HeaderOfSensorTableView.qml

        Qml/InputField.qml
        Qml/CustomLabel.qml

        Qml/AppMenuBar.qml
        Qml/NetMenu.qml
        Qml/ViewMenu.qml
        Qml/OptionsMenu.qml
        SOURCES DataMappers/LanguageChooser.h
        SOURCES DataMappers/LanguageChooser.cpp
)

qt_add_resources(${PROJECT_NAME}
    PREFIX "/"
    FILES
        "Resources/Images/icon.png"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        Qt::Core
        Qt::Quick
        Qt::Gui
        Qt::QuickControls2
        Net
        Utils
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
