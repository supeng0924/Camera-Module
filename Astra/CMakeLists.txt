cmake_minimum_required(VERSION 2.6)
project(image)
add_definitions(-std=c++11)
FIND_PACKAGE(OpenCV  REQUIRED )
FIND_PACKAGE(Threads)
set(OPENNI2_INCLUDE "/home/supeng/Program/orbbec/Astra/Include")
set(OPENNI2_REDIST "/home/supeng/Program/orbbec/Astra/lib_sp/OpenNI2/Drivers")
set(OPENNI2_REDIST_2 "/home/supeng/Program/orbbec/Astra/lib_sp")
link_directories(${OPENNI2_REDIST})
link_directories(${OPENNI2_REDIST_2})
include_directories(${OPENNI2_INCLUDE})
include_directories("/usr/include/eigen3")
include_directories(src/)

file(GLOB DIR_SRCS "src/*.cpp")
# aux_source_directory(src/ DIR_SRCS)

add_executable(image main.cpp ${DIR_SRCS})

# TARGET_LINK_LIBRARIES(image ${OPENNI2_REDIST}/libOniFile.so)
# TARGET_LINK_LIBRARIES(image ${OPENNI2_REDIST}/liborbbec.so)
# TARGET_LINK_LIBRARIES(image ${OPENNI2_REDIST}/libPSLink.so)
# TARGET_LINK_LIBRARIES(image ${OPENNI2_REDIST_2}/libOpenNI2.jni.so)
TARGET_LINK_LIBRARIES(image ${OPENNI2_REDIST_2}/libOpenNI2.so)



TARGET_LINK_LIBRARIES(image ${OpenCV_LIBS})
target_link_libraries (image ${CMAKE_THREAD_LIBS_INIT})
message(${OpenCV_LIBS})
install(TARGETS image RUNTIME DESTINATION bin)


