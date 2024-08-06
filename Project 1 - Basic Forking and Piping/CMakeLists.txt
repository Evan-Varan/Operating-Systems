cmake_minimum_required(VERSION 3.27)
project(OperatingSystems C)

set(CMAKE_C_STANDARD 11)

#add_executable(OperatingSystems
#        linkedList.c
#        linkedList.h
#        sort.c
#        sort.h
#        pre.c
#        pre.h
#        vector.c
#        vector.h
#        pipe.c
#)

set(SOURCES
        vector.c
        vector.h
        linkedList.c
        linkedList.h
)

# Add executables
add_executable(pipe pipe.c ${SOURCES})
add_executable(pre pre.c ${SOURCES})
add_executable(sort sort.c ${SOURCES})
add_executable(parent parent.c ${SOURCES})

