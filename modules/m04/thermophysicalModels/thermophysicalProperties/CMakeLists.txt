cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(thermophysicalProperties)

add_library(${PROJECT_NAME} SHARED
thermophysicalProperties.C
liquidProperties.C
liquidMixtureProperties.C
liquid.C
H2O.C
C7H16.C
C12H26.C
C10H22.C
C8H18.C
IC8H18.C
C4H10O.C
C2H6O.C
IDEA.C
aC10H7CH3.C
bC10H7CH3.C
C8H10.C
C16H34.C
C9H20.C
C6H6.C
C7H8.C
C6H14.C
C13H28.C
C14H30.C
C3H8.C
C3H6O.C
C2H6.C
CH3OH.C
C2H5OH.C
Ar.C
N2.C
MB.C
CH4N2O.C
nC3H8O.C
iC3H8O.C
solidProperties.C
solidPropertiesNew.C
solidMixtureProperties.C
ash.C
C.C
CaCO3.C
)

target_link_libraries(${PROJECT_NAME}
specie
)
