cmake_minimum_required(VERSION 3.7.0)

project(QGitTag LANGUAGES CXX)

set(AUTOMOC ON)

find_package(Qt5 COMPONENTS Network REQUIRED)

add_library(${PROJECT_NAME} STATIC
    src/qgitasset.cpp
    src/qgittag.cpp
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Network)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
