cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(Pstream)

add_library(${PROJECT_NAME} SHARED
UPstream.C
UIPread.C
UOPwrite.C
)
