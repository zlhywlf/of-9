cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(fileFormats)

add_library(${PROJECT_NAME} SHARED
vtkWriteOps.C
vtkUnstructuredReader.C
NASCore.C
STARCDCore.C
OBJstream.C
)
