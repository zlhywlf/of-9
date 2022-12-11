cmake_minimum_required(VERSION 3.0.0)

include(${WORKSPACE}/etc/base.cmake)

project(laplacianFoam)

add_executable(${PROJECT_NAME} laplacianFoam.C)

target_link_libraries(${PROJECT_NAME}
finiteVolume
fvModels
fvConstraints
meshTools
)