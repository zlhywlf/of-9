cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(surfMesh)

add_library(${PROJECT_NAME} SHARED
surfZone.C
surfZoneIOList.C
surfZoneIdentifier.C
MeshedSurfaceIOAllocator.C
MeshedSurfaceCore.C
MeshedSurfaces.C
UnsortedMeshedSurfaces.C
MeshedSurfaceProxyCore.C
surfaceRegistry.C
surfMesh.C
surfMeshClear.C
surfMeshIO.C
surfFields.C
surfPointFields.C
surfaceFormatsCore.C
AC3DsurfaceFormatCore.C
AC3DsurfaceFormatRunTime.C
GTSsurfaceFormatRunTime.C
NASsurfaceFormatRunTime.C
OBJsurfaceFormatRunTime.C
OFFsurfaceFormatRunTime.C
OFSsurfaceFormatCore.C
OFSsurfaceFormatRunTime.C
SMESHsurfaceFormatRunTime.C
STARCDsurfaceFormatCore.C
STARCDsurfaceFormatRunTime.C
STLsurfaceFormatCore.C
STLsurfaceFormatRunTime.C
STLsurfaceFormatASCII.C
TRIsurfaceFormatCore.C
TRIsurfaceFormatRunTime.C
VTKsurfaceFormatCore.C
VTKsurfaceFormatRunTime.C
WRLsurfaceFormatCore.C
WRLsurfaceFormatRunTime.C
X3DsurfaceFormatCore.C
X3DsurfaceFormatRunTime.C
)

target_link_libraries(${PROJECT_NAME}
fileFormats
)
