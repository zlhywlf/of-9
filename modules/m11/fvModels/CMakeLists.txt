cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(fvModels)

add_library(${PROJECT_NAME} SHARED
codedFvModel.C
semiImplicitSource.C
actuationDiskSource.C
effectivenessHeatExchangerSource.C
explicitPorositySource.C
radialActuationDiskSource.C
rotorDiskSource.C
bladeModel.C
profileModel.C
profileModelList.C
lookupProfile.C
seriesProfile.C
trimModel.C
trimModelNew.C
fixedTrim.C
targetCoeffTrim.C
solidificationMeltingSource.C
sixDoFAccelerationSource.C
buoyancyForce.C
buoyancyEnergy.C
damping.C
isotropicDamping.C
verticalDamping.C
phaseLimitStabilisation.C
accelerationSource.C
volumeFractionSource.C
solidEquilibriumEnergySource.C
massSource.C
heatSource.C
heatTransfer.C
interRegionModel.C
interRegionExplicitPorositySource.C
interRegionHeatTransfer.C
heatTransferModel.C
constant.C
function1.C
function2.C
variable.C
)

target_link_libraries(${PROJECT_NAME}
finiteVolume
sampling
meshTools
momentumTransportModels
compressibleMomentumTransportModels
thermophysicalTransportModels
)