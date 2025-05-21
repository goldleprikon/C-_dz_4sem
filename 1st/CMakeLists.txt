cmake_minimum_required(VERSION 3.5)

project(1st LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(1st main.cpp


    System.h
    Manager.h
    manager.cpp)

include(GNUInstallDirs)
install(TARGETS 1st
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
