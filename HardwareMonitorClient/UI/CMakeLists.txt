project(UI LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    main.cpp
    Models/HardwareModel.h Models/HardwareModel.cpp
    Models/SensorModel.h Models/SensorModel.cpp
    Models/ModelManager.h Models/ModelManager.cpp
    DataMappers/SensorUnitProvider.h DataMappers/SensorUnitProvider.cpp
    DataMappers/SensorPrecisionProvider.h DataMappers/SensorPrecisionProvider.cpp
)

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
        Qml/InputField.qml
        Qml/HardwareView.qml
        Qml/TopMenuBar.qml
        Qml/LoginControl.qml
        Qml/ErrorText.qml
        Qml/AppSettings.qml
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
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
