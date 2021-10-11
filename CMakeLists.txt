cmake_minimum_required(VERSION 3.15.0)

project(QGitTag LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(AUTOMOC ON)

find_package(Qt5 COMPONENTS Network REQUIRED)
find_package(Doxygen)

add_library(${PROJECT_NAME} STATIC
    src/qgitasset.cpp
    src/qgittag.cpp
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Network)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(DOXYGEN_FOUND)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)

    doxygen_add_docs(${PROJECT_NAME}Documentation
        src/qgitasset.h
        src/qgittag.h
        README.md
    )
endif()
