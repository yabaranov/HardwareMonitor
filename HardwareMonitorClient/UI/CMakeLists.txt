cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(UI LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2)

qt_standard_project_setup()

add_subdirectory(Translation)
add_subdirectory(SensorDatabase)

qt_add_executable(${PROJECT_NAME}
    main.cpp

    Models/HardwareListModel.h Models/HardwareListModel.cpp
    Models/SensorTableModel.h Models/SensorTableModel.cpp
    Models/HardwarePageModel.h Models/HardwarePageModel.cpp
    Models/DataMappers/SensorUnitProvider.h Models/DataMappers/SensorUnitProvider.cpp
    Models/DataMappers/SensorPrecisionProvider.h Models/DataMappers/SensorPrecisionProvider.cpp
    Models/Types/Sensor.h    
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
        Translation
        SensorDatabase
)

add_custom_target(Deploy
    COMMAND windeployqt6 --qmldir="${CMAKE_CURRENT_SOURCE_DIR}/Qml" $<TARGET_FILE:${PROJECT_NAME}>
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
