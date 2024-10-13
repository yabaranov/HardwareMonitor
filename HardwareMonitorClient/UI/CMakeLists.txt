project(UI LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    main.cpp
    HardwareModel.h HardwareModel.cpp
    SensorModel.h SensorModel.cpp
    ModelManager.h ModelManager.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI UI
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        Main.qml
        InputField.qml
        HardwareView.qml
)


#qt_add_resources(${PROJECT_NAME}
#    "assets"
#    PREFIX "/"
#    FILES
#        "qt_logo_green_64x64px.png"
#)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        Qt::Core
        Qt::Quick
        Qt::Gui
        Net
)


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
