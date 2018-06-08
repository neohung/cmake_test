cmake_minimum_required(VERSION 2.4)
#project(Test)
#USE FOLDER NAME AS PROJECT NAME
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C CXX)

find_package(SDL)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/inc 
  ${CMAKE_SOURCE_DIR}/testlib/inc 
)


###########################

SET(SRCS
    src/main.cpp
)

###########################
ADD_EXECUTABLE(${ProjectId} ${SRCS})
TARGET_LINK_LIBRARIES(${ProjectId}
  testapi
)
ADD_DEPENDENCIES(${ProjectId} testapi)

INSTALL(TARGETS ${ProjectId} DESTINATION ${CMAKE_BINARY_DIR}/bin)
############################

