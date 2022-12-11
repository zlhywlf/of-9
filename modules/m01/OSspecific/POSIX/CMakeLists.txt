cmake_minimum_required(VERSION 3.17)

include(${WORKSPACE}/etc/base.cmake)

project(OSspecific)

add_library(${PROJECT_NAME} SHARED
sigFpe.C
sigSegv.C
sigInt.C
sigQuit.C
sigStopAtWriteNow.C
sigWriteNow.C
regExp.C
timer.C
fileStat.C
POSIX.C
cpuTime.C
clockTime.C
memInfo.C

# Note: fileMonitor assumes inotify by default. Compile with -DFOAM_USE_STAT
# to use stat (=timestamps) instead of inotify
fileMonitor.C

# ifeq "$(WM_ARCH)" "SunOS64"
#    dummyPrintStack.C
# else
    printStack.C
# endif
)
