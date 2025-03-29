cmake_minimum_required(VERSION 3.16)
project(calculator)

set(CMAKE_AUTOMOC ON)  # Ensure AUTOMOC is enabled
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Update UI file path to new location
qt_wrap_ui(UI_HEADERS source/calculator.ui)  # <-- Changed path

include_directories(
    source
    ${CMAKE_CURRENT_BINARY_DIR}  # For generated ui_calculator.h
)

set(SOURCE_SOURCES
    source/calculator.cpp
)

set(SOURCE_HEADERS
    source/calculator.h
)

set(MAIN_SOURCES
    Main/main.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCE_SOURCES}
    ${SOURCE_HEADERS}
    ${MAIN_SOURCES}
    ${UI_HEADERS}  # Include generated UI headers
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

# Update source_group to include the UI file
source_group("Source" FILES ${SOURCE_SOURCES} ${SOURCE_HEADERS} source/calculator.ui)
source_group("Main" FILES ${MAIN_SOURCES})
