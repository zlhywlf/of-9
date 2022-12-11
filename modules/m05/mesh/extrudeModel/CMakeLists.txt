cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(extrudeModel)

add_library(${PROJECT_NAME} SHARED
extrudeModel.C
extrudeModelNew.C
linearNormal.C
planeExtrusion.C
linearDirection.C
linearRadial.C
radial.C
sigmaRadial.C
sector.C
cyclicSector.C
wedge.C
)

target_link_libraries(${PROJECT_NAME}
meshTools
)