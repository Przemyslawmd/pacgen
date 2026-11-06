
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(
    Pacgen
    "main.cpp"
    pacgen.cpp
        gui/control.h
        gui/panel.h
        gui/message.h
)

target_include_directories(Pacgen PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(Pacgen Qt6::Widgets)