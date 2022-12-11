cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(specie)

add_library(${PROJECT_NAME} SHARED
atomicWeights.C
specie.C
specieCoeffs.C
reaction.C
integratedNonUniformTable1.C
APIdiffCoef.C
NSRDS0.C
NSRDS1.C
NSRDS2.C
NSRDS3.C
NSRDS4.C
NSRDS5.C
NSRDS6.C
NSRDS7.C
NSRDS14.C
)

target_link_libraries(${PROJECT_NAME}
OpenFOAM
)
