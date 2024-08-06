cmake_minimum_required(VERSION 3.27)
project(OperatingSystems C)

set(CMAKE_C_STANDARD 11)


set(SOURCES
        vector.c
        vector.h
        linkedList.c
        linkedList.h
        pipe.h
        pipe.c
)

# Add executables
#add_executable(pipe pipe.c ${SOURCES})
add_executable(pre pre.c ${SOURCES})
add_executable(sort sort.c ${SOURCES})
add_executable(parent parent.c ${SOURCES})
add_executable(shhh shhh.c ${SOURCES})


