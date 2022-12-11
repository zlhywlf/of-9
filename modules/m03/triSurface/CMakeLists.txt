cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(triSurface)

add_library(${PROJECT_NAME} SHARED
meshTriangulation.C
triSurface.C
triSurfaceAddressing.C
stitchTriangles.C
writeSTL.C
readSTL.C
readSTLASCII.C
readSTLBINARY.C
writeGTS.C
readGTS.C
readOBJ.C
writeOBJ.C
writeSMESH.C
readOFF.C
writeOFF.C
writeTRI.C
readTRI.C
readAC.C
writeAC.C
readVTK.C
writeVTK.C
readNAS.C
geometricSurfacePatch.C
surfacePatch.C
surfacePatchIOList.C
sortLabelledTri.C
triSurfaceFields.C
)

target_link_libraries(${PROJECT_NAME}
fileFormats
surfMesh
)
