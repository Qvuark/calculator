cmake_minimum_required(VERSION 3.16)
project(calculator)

set(CMAKE_AUTOMOC ON)  # Ensure AUTOMOC is enabled
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Update UI file path to new location
qt_wrap_ui(UI_H ui/calculator.ui)  # <-- Changed path

include_directories(
    src
    commands
    ui
    main
    ${CMAKE_CURRENT_BINARY_DIR}  # For generated ui_calculator.h
)
set(UI_H
    ui/calculator.ui
)
set(SRC_CPP
    src/calculator.cpp
)
set(SRC_H
    src/calculator.h
)

set(COMMANDS_H
    commands/command.h
    commands/digitshandling.cpp
    commands/digitshandling.h
)
set(MAIN_SOURCES
    Main/main.cpp
)

add_executable(${PROJECT_NAME}
    ${SRC_CPP}
    ${SRC_H}
    ${COMMANDS_H}
    ${MAIN_SOURCES}
    ${UI_H}
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

# Update source_group to include the UI file
source_group("ui" FILES ${UI_H})
source_group("src" FILES ${SRC_CPP} ${SRC_H})
source_group("commands" FILES ${COMMANDS_H})
source_group("main" FILES ${MAIN_SOURCES})
