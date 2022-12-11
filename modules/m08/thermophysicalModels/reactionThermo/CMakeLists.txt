cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(reactionThermophysicalModels)

add_library(${PROJECT_NAME} SHARED
basicSpecieMixture.C
basicCombustionMixture.C
fluidReactionThermo.C
psiReactionThermo.C
psiReactionThermos.C
psiuReactionThermo.C
psiuReactionThermos.C
rhoReactionThermo.C
rhoReactionThermos.C
fixedUnburntEnthalpyFvPatchScalarField.C
gradientUnburntEnthalpyFvPatchScalarField.C
mixedUnburntEnthalpyFvPatchScalarField.C
moleFractionsFunctionObjects.C
)

target_link_libraries(${PROJECT_NAME}
fluidThermophysicalModels
specie
finiteVolume
)