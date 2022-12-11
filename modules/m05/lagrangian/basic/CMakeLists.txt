cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(lagrangian)

add_library(${PROJECT_NAME} SHARED
particle.C
particleIO.C
IOPositionName.C
passiveParticleCloud.C
indexedParticleCloud.C
referredWallFace.C
)

target_link_libraries(${PROJECT_NAME}
meshTools
)