cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME Kinect)
project(${PROJECT_NAME})

#���·��
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

#D:/eigen/eigen·���´��C++���������Eigen
#$ENV{OPENCV_DIR}/newbuild/install/include;$ENV{OPENCV_DIR}/newbuild/install/include/opencv2;$ENV{OPENCV_DIR}/newbuild/install/include/opencv;
set(OPENCV_INCLUDE "$ENV{KINECTSDK20_DIR}/inc;D:/eigen/eigen")


#��CMake�ҵ�ͷ�ļ�
include_directories(${OPENCV_INCLUDE})   


#��CMake�ҵ�Դ�ļ�
aux_source_directory(src DIR_SRCS)  
file(GLOB_RECURSE HEADERS *.h)
source_group("Header Files" FILES ${HEADERS})

#����һ����ִ���ļ�����Ŀ��
add_executable(${PROJECT_NAME} ${DIR_SRCS} ${HEADERS})

#���ӿ�D:\opencv\newbuild\install\x64\vc14\lib
set(OPENCV_LIB_DIRS $ENV{OPENCV_DIR}/newbuild/install/x64/vc14/lib)
#GLOBѡ���Ϊ����ƥ���ѯ����ʽ���ļ�����һ���ļ�list��������list�洢������LIBS��
file(GLOB LIBSD "${OPENCV_LIB_DIRS}/*330d.lib")
file(GLOB LIBS "${OPENCV_LIB_DIRS}/*330.lib")
file(GLOB LIBKINECTS "$ENV{KINECTSDK20_DIR}/Lib/x64/*.lib")

target_link_libraries(${PROJECT_NAME} debug ${LIBSD})
target_link_libraries(${PROJECT_NAME} optimized ${LIBS})
target_link_libraries(${PROJECT_NAME} ${LIBKINECTS})