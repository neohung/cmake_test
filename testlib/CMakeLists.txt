cmake_minimum_required(VERSION 2.8)
project(Testlib)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/inc 
)

###########################

SET(TESTLIB_SRCS
    src/main.cpp
    inc/testapi.h
)

ADD_LIBRARY(testapi SHARED ${TESTLIB_SRCS})
#ADD_LIBRARY(testapi STATIC ${TESTLIB_SRCS})

#target_link_libraries(testapi
#)
#add_dependencies(testapi t2)

INSTALL(TARGETS testapi DESTINATION ${CMAKE_BINARY_DIR}/bin)
############################

