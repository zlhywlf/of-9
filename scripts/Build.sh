#!/bin/bash

sources=(${sourceDir//,/ })

doBuild(){
    echo -e "\n====================== "$buildType": "$1" ======================\n"
    cmake \
    --no-warn-unused-cli \
    -DWORKSPACE:STRING=$projectDir \
    -DLIBRARY_OUTPUT_PATH:STRING=$projectDir"/lib" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
    -DCMAKE_BUILD_TYPE:STRING=$buildType \
    -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
    -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
    -S$projectDir/$1 \
    -B$projectDir/build/$1 \
    -G "Unix Makefiles" && \
    cmake \
    --build $projectDir/build/$1 \
    --config $buildType \
    --clean-first -j 10 --
}

build(){
    if [ -e "$1"/"CMakeLists.txt" ];then
        doBuild $1
    else
        for f in `ls $1`
        do
            if [ -d $1"/"$f ]
            then
                build $1"/"$f
            fi
        done
    fi
}

for i in ${sources[*]}; do
    build $i
done