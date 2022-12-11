cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(fluidThermophysicalModels)

add_library(${PROJECT_NAME} SHARED
basicThermo.C
fluidThermo.C
hydrostaticInitialisation.C
psiThermo.C
psiThermos.C
rhoThermo.C
rhoThermos.C
liquidThermo.C
fixedEnergyFvPatchScalarField.C
gradientEnergyFvPatchScalarField.C
gradientEnergyCalculatedTemperatureFvPatchScalarField.C
mixedEnergyFvPatchScalarField.C
mixedEnergyCalculatedTemperatureFvPatchScalarField.C
energyJumpFvPatchScalarField.C
energyJumpAMIFvPatchScalarField.C
)

target_link_libraries(${PROJECT_NAME}
transportModels
specie
thermophysicalProperties
finiteVolume
meshTools
)