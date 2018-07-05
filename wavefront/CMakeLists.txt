cmake_minimum_required(VERSION 2.4)
project(WaveFront)

#find_package(SDL)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR} 
  ${PROJECT_SOURCE_DIR}/inc 
)

###########################

SET(WAVEFRONTLIB_SRCS
    src/objModel.c
    inc/objModel.h
)

ADD_LIBRARY(wavefront SHARED ${WAVEFRONTLIB_SRCS})
#ADD_LIBRARY(tcimg STATIC ${TCIMGLIB_SRCS})
#ADD_LIBRARY(testapi STATIC ${TESTLIB_SRCS})

#target_link_libraries(testapi
#)
#add_dependencies(testapi t2)

INSTALL(TARGETS wavefront DESTINATION ${CMAKE_BINARY_DIR}/bin)
############################

