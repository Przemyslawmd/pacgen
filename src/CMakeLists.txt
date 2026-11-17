
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(
    Pacgen
    main.cpp
    pacgen.cpp
    controller.cpp
    gui/controlPanel.cpp
    gui/packetPanel.cpp
    gui/messagePanel.cpp
    gui/tabLink.cpp
    gui/tabInternet.cpp
    gui/tabTransport.cpp
)

target_include_directories(Pacgen PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(Pacgen Qt6::Widgets)

