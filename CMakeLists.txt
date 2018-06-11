cmake_minimum_required(VERSION 2.8)
project(mainproject)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

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

######### List folders included CMakeLists.txt #########
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      IF(EXISTS "${curdir}/${child}/CMakeLists.txt")
        LIST(APPEND dirlist ${child})
      ELSE()
      ENDIF()
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(alldirs ${CMAKE_SOURCE_DIR})
######################################################

######################################################
subdirs(
  ${alldirs}
#  testlib
  #tcimg
  #test2
)
#add_subdirectory()
######################################################

#ADD_CUSTOM_COMMAND(
#  OUTPUT checkdir
#  COMMAND echo ${alldirs}
#)
#ADD_CUSTOM_TARGET(check_dir DEPENDS checkdir)

ADD_CUSTOM_TARGET(debug
  COMMAND echo "====================================="
  COMMAND echo "CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}"
  COMMAND echo "SDL2: ${SDL2_LIBRARY}"
  COMMAND echo "SDL2: ${SDL2_INCLUDE_DIRS}"
  #COMMAND echo "SDL2IMAGE: ${SDL2IMAGE_INCLUDE_DIR}"
  #COMMAND echo "SDL: ${SDL_LIBRARY}"
  COMMAND echo "SDL2: ${SDL2_LIBRARIES}"
  COMMAND echo "SDL2: ${LIBSDL2_LIBRARIES_PATH}"
  #COMMAND echo "SDL2IMAGE: ${SDL2IMAGE_LIBRARY}"
  COMMAND echo "====================================="
)

ADD_CUSTOM_TARGET(run 
  COMMAND echo "=====================================" 
  WORKING_DIRECTORY bin
  COMMAND echo `pwd`
  COMMAND LD_LIBRARY_PATH=. ./test2
  COMMAND echo "=====================================" 
)
