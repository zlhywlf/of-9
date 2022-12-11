macro(FIND_INCLUDE_DIR result curdir)                                                                               # 定义函数,2个参数:存放结果result；指定路径curdir；
    file(GLOB_RECURSE children "${curdir}/*.C" "${curdir}/*.H" "${curdir}/*.c" "${curdir}/*.h")	                    # 遍历获取{curdir}文件列表
    set(dirlist "")														                                            # 定义dirlist中间变量，并初始化
    foreach(child ${children})											                                            # for循环
        string(REGEX REPLACE "(.*)/.*" "\\1" LIB_NAME ${child})			                                            # 字符串替换,获取文件所在目录
        if(IS_DIRECTORY ${LIB_NAME})									                                            # 判断是否为路径
            if(dirlist MATCHES "${LIB_NAME}$")                                                                      # 判断dirlist是否含有${LIB_NAME}
            else()
              LIST(APPEND dirlist ${LIB_NAME})							                                            # 将合法的路径加入dirlist变量中
            endif()
        endif()															                                            # 结束判断
    endforeach()														                                            # 结束for循环
    set(${result} ${dirlist})											                                            # dirlist结果放入result变量中
endmacro()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -m64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNoRepository -Dlinux64 -DWM_ARCH_OPTION=64 -DWM_DP -DWM_LABEL_SIZE=32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wold-style-cast -Wnon-virtual-dtor -Wno-unused-parameter -Wno-invalid-offsetof -Wno-attributes")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -ftemplate-depth-100 -fuse-ld=bfd -Xlinker --add-needed -Xlinker --no-as-needed")

if (CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    add_definitions(-DDEBUG)
endif()

FIND_INCLUDE_DIR(INCLUDE_DIR_LIST ${WORKSPACE})
include_directories(
    ${INCLUDE_DIR_LIST}
)

link_directories(
    ${WORKSPACE}/lib
)
