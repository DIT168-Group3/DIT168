# Author Martin Chukaleski 28.03

cmake_minimum_required(VERSION 3.5)

project(RemoteGUI)

set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")


find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(
    ${GTKMM_LIBRARY_DIRS})

include_directories(
    ${GTKMM_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}.main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp )

target_link_libraries(${PROJECT_NAME}.main
    ${GTKMM_LIBRARIES}  )
