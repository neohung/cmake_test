cmake_minimum_required(VERSION 2.8)
#project(Test)
#USE FOLDER NAME AS PROJECT NAME
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

set(CMAKE_INSTALL_RPATH "./")
#set(CMAKE_INSTALL_RPATH "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if (APPLE)
  message(STATUS ">>> MAC")
  set(CMAKE_MACOSX_RPATH 0)
  find_package(SDL2 REQUIRED)
elseif(UNIX AND NOT APPLE)
  message(STATUS ">>> Linux")
  find_package(PkgConfig)
  if(PKG_CONFIG_FOUND)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
  endif()
elseif(WIN32)
  message(STATUS ">>> WIN32")
endif()

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${SDL2_INCLUDE_DIRS}
  #${SDL2IMAGE_INCLUDE_DIRS}
  #${SDL2TTF_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/inc 
  ${CMAKE_SOURCE_DIR}/winlib/inc 
  ${CMAKE_SOURCE_DIR}/testlib/inc 
  ${CMAKE_SOURCE_DIR}/tcimg 
  ${CMAKE_SOURCE_DIR}/simplemathlib/inc 
)


###########################

SET(SRCS
    src/main.cpp
    src/a.c
)


###########################
ADD_EXECUTABLE(${ProjectId} ${SRCS})
TARGET_LINK_LIBRARIES(${ProjectId}
  ${LIBSDL2_LIBRARIES_PATH}
  ${SDL2_LIBRARIES}
  #${SDL2IMAGE_LIBRARIES}
  #${SDL2TTF_LIBRARIES}
  testapi
  tcimg
  winapi
  smathapi
)
ADD_DEPENDENCIES(${ProjectId} 
  winapi
  testapi
  tcimg
  smathapi
)

INSTALL(TARGETS ${ProjectId} DESTINATION ${CMAKE_BINARY_DIR}/bin)
############################

