set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${DIR_NAME})

file(GLOB ALL_FILE "*.h" "*.cpp")
add_executable(${DIR_NAME} ${ALL_FILE})

find_package(Qt5 REQUIRED COMPONENTS Widgets)
target_link_libraries(${DIR_NAME} Qt5::Widgets)
