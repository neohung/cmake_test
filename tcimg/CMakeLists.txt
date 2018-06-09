cmake_minimum_required(VERSION 2.4)
project(Tcimg)

#find_package(SDL)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR} 
  ${PROJECT_SOURCE_DIR}/inc 
)

###########################

SET(TCIMGLIB_SRCS
    tcimg.c
    tcimg.h
)

ADD_LIBRARY(tcimg SHARED ${TCIMGLIB_SRCS})
#ADD_LIBRARY(testapi STATIC ${TESTLIB_SRCS})

#target_link_libraries(testapi
#)
#add_dependencies(testapi t2)

INSTALL(TARGETS tcimg DESTINATION ${CMAKE_BINARY_DIR}/bin)
############################

