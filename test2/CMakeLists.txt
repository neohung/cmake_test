cmake_minimum_required(VERSION 2.8)
#project(Test)
#USE FOLDER NAME AS PROJECT NAME
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C CXX)


INCLUDE (FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${SDL2_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/inc 
  ${CMAKE_SOURCE_DIR}/testlib/inc 
  ${CMAKE_SOURCE_DIR}/tcimg 
)


###########################

SET(SRCS
    src/main.cpp
    src/a.c
)

###########################
ADD_EXECUTABLE(${ProjectId} ${SRCS})
TARGET_LINK_LIBRARIES(${ProjectId}
  ${SDL2_LIBRARIES}
  testapi
  tcimg
)
ADD_DEPENDENCIES(${ProjectId} 
  testapi
  tcimg
)

INSTALL(TARGETS ${ProjectId} DESTINATION ${CMAKE_BINARY_DIR}/bin)
############################

