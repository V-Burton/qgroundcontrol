add_subdirectory(LibEvents)

find_package(Qt6 REQUIRED COMPONENTS Core Gui QmlIntegration)

qt_add_library(MAVLink STATIC
    ImageProtocolManager.cc
    ImageProtocolManager.h
    MAVLinkFTP.cc
    MAVLinkFTP.h
    MAVLinkLib.h
    MAVLinkSigning.cc
    MAVLinkSigning.h
    MAVLinkStreamConfig.cc
    MAVLinkStreamConfig.h
    QGCMAVLink.cc
    QGCMAVLink.h
    StatusTextHandler.cc
    StatusTextHandler.h
    SysStatusSensorInfo.cc
    SysStatusSensorInfo.h
)

target_link_libraries(MAVLink
    PRIVATE
        Utilities
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::QmlIntegration
)

target_include_directories(MAVLink 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/libs/mavlink/generated/include
        ${CMAKE_SOURCE_DIR}/libs/mavlink/generated/include/mavlink/v2.0/hylight
)
# TODO: Last line with hylight still needed? Try to remove it.