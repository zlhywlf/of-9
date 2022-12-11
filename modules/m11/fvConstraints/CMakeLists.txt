cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(fvConstraints)

add_library(${PROJECT_NAME} SHARED
fixedValueConstraint.C
fixedTemperatureConstraint.C
limitTemperature.C
limitPressure.C
limitVelocity.C
meanVelocityForce.C
patchMeanVelocityForce.C
)

target_link_libraries(${PROJECT_NAME}
finiteVolume
sampling
meshTools
momentumTransportModels
compressibleMomentumTransportModels
thermophysicalTransportModels
)