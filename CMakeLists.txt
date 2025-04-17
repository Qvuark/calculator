cmake_minimum_required(VERSION 3.16)
project(calculator)

set(CMAKE_AUTOMOC ON)  # Ensure AUTOMOC is enabled
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Update UI file path to new location
qt_wrap_ui(UI_ ui/calculator.ui)  # <-- Changed path

include_directories(
    src
    commands
    ui
    main
    ${CMAKE_CURRENT_BINARY_DIR}  # For generated ui_calculator.h
)
set(UI_
    ui/calculator.ui
)
set(SRC
    src/calculator.cpp
    src/calculator.h
)

set(COMMANDS
    commands/command.h
    commands/digitshandling.cpp
    commands/digitshandling.h
    commands/commandhandeling.h
    commands/commandhandeling.cpp
    commands/clearbutton.h
    commands/clearbutton.cpp
    commands/equalbutton.h
    commands/equalbutton.cpp
    commands/backspacebutton.h
    commands/backspacebutton.cpp
)
set(MAIN_SOURCES
    Main/main.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${SRC}
    ${COMMANDS}
    ${MAIN_SOURCES}
    ${UI_}

)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

# Update source_group to include the UI file
source_group("ui" FILES ${UI_})
source_group("src" FILES ${SRC})
source_group("commands" FILES ${COMMANDS})
source_group("main" FILES ${MAIN_SOURCES})
