cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(conversion)

add_library(${PROJECT_NAME} SHARED
ensightFile.C
ensightGeoFile.C
ensightPart.C
ensightPartIO.C
ensightPartCells.C
ensightPartFaces.C
ensightParts.C
mergedCyclicPolyPatch.C
polyMeshUnMergeCyclics.C
boundaryRegion.C
cellTable.C
meshReader.C
meshReaderAux.C
calcPointCells.C
createPolyCells.C
createPolyBoundary.C
STARCDMeshReader.C
meshWriter.C
STARCDMeshWriter.C
polyDualMesh.C
)

target_link_libraries(${PROJECT_NAME}
fileFormats
finiteVolume
dynamicMesh
meshTools
)