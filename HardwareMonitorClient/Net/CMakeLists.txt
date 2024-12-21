project(Net LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Protobuf ProtobufTools Grpc GrpcTools)

qt_standard_project_setup()

qt_add_library(${PROJECT_NAME} STATIC
    SensorTask.h
    SensorTask.cpp
    NetClient.h
    NetClient.cpp
)

qt_add_protobuf(${PROJECT_NAME}
    PROTO_FILES
        Protos/HardwareService.proto
)

qt_add_grpc(${PROJECT_NAME} CLIENT
    PROTO_FILES
        Protos/HardwareService.proto
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Protobuf
        Qt::Grpc
        Utils
)


target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
