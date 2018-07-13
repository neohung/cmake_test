cmake_minimum_required(VERSION 2.8)
project(SimpleMatrixLib)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

if (APPLE)
  message(STATUS ">>> MAC")
  set(CMAKE_MACOSX_RPATH 0)
  #find_package(SDL2 REQUIRED)
elseif(UNIX AND NOT APPLE)
  message(STATUS ">>> Linux")
  find_package(PkgConfig)
  if(PKG_CONFIG_FOUND)
    #PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
  endif()
elseif(WIN32)
  message(STATUS ">>> WIN32")
endif()

include_directories(
  ${CMAKE_SOURCE_DIR}
  #${SDL2_INCLUDE_DIRS}
  #${SDL2IMAGE_INCLUDE_DIRS}
  #${SDL2TTF_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/inc 
)

###########################

SET(SMATRIXLIB_SRCS
    src/smatrix.cpp
    inc/smatrix.h
)



ADD_LIBRARY(smatrixapi SHARED ${SMATRIXLIB_SRCS})

#TARGET_LINK_LIBRARIES(smathapi
  #${SDL2_LIBRARIES}
  #${SDL2IMAGE_LIBRARIES}
  #${SDL2TTF_LIBRARIES}
  #tcimg
#)
#ADD_DEPENDENCIES(winapi
  #testapi
#  tcimg
#)

#ADD_LIBRARY(testapi STATIC ${TESTLIB_SRCS})

#target_link_libraries(testapi
#)
#add_dependencies(testapi t2)

INSTALL(TARGETS smatrixapi DESTINATION ${CMAKE_BINARY_DIR}/bin)
############################

