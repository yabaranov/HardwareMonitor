project(Client)

find_package(Qt6 REQUIRED COMPONENTS Core Protobuf Grpc Quick)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    main.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI qtgrpc.examples.chat
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        Main.qml
        ChatInputField.qml
        ChatView.qml
)

qt_add_resources(${PROJECT_NAME}
    "assets"
    PREFIX "/"
    FILES
        "qt_logo_green_64x64px.png"
)

qt_add_protobuf(${PROJECT_NAME}
    PROTO_FILES
        ../proto/simplechat.proto
)

qt_add_grpc(${PROJECT_NAME} CLIENT
    PROTO_FILES
        ../proto/simplechat.proto
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Gui
        Qt::Quick
        Qt::Grpc
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()