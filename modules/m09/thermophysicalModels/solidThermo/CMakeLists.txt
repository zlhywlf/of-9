cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(solidThermo)

add_library(${PROJECT_NAME} SHARED
solidThermo.C
solidThermos.C
)

target_link_libraries(${PROJECT_NAME}
meshTools
finiteVolume
specie
fluidThermophysicalModels
reactionThermophysicalModels
)