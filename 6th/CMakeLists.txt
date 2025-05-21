cmake_minimum_required(VERSION 3.5)

project(6th LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(6th main.cpp
    checkpoint.h checkpoint.cpp
    checkpointbuilder.h
    concretecheckpointbuilder.h concretecheckpointbuilder.cpp
    checkpointdirector.h checkpointdirector.cpp )

include(GNUInstallDirs)
install(TARGETS 6th
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
