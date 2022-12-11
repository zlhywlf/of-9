cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(transportModels)

add_library(${PROJECT_NAME} SHARED
kinematicTransportModel.C
dynamicTransportModel.C
viscosityModel.C
viscosityModelNew.C
Newtonian.C
powerLaw.C
CrossPowerLaw.C
BirdCarreau.C
HerschelBulkley.C
Casson.C
strainRateFunction.C
singlePhaseTransportModel.C
)

target_link_libraries(${PROJECT_NAME}
finiteVolume
)