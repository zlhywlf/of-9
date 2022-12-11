cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(compressibleMomentumTransportModels)

add_library(${PROJECT_NAME} SHARED
compressibleMomentumTransportModel.C
dynamicMomentumTransportModels.C
)

target_link_libraries(${PROJECT_NAME}
transportModels
finiteVolume
meshTools
)