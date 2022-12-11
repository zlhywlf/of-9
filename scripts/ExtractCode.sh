#!/bin/bash

ExtractCode()
{
    for f in `ls $1`
    do
        if [ -d $1"/"$f ]
        then
            if [ $f != '.' ] && [ $f != '..' ]
            then
                ExtractCode $1"/"$f $2
            fi
        else
            if [ "${f##*.}" = "C" ] || [ "${f##*.}" = "H"  ] || [ "${f##*.}" = "c"  ] || [ "${f##*.}" = "h"  ] || [ "${f##*.}" = "Cver"  ] || [ "${f##*.}" = "L"  ]
            then
                mv $1"/"$f  $2"/"$f
                if [ "${f##*.}" = "Cver"  ] || [ "${f##*.}" = "L"  ]
                then
                    echo "存在需要转换的源码:"$f
                fi
            fi
        fi
    done
}

# 模块路径
to=$1

for f in `ls $to`
do
    if [ -d $to"/"$f ]
    then
        ExtractCode $to"/"$f $to
    fi
done