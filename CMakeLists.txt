cmake_minimum_required(VERSION 2.4)
project(mainproject)

find_package(SDL2 REQUIRED)

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
)
######################################################

#ADD_CUSTOM_COMMAND(
#  OUTPUT checkdir
#  COMMAND echo ${alldirs}
#)
#ADD_CUSTOM_TARGET(check_dir DEPENDS checkdir)

ADD_CUSTOM_TARGET(debug
  COMMAND echo "====================================="
  #COMMAND echo "SDL: ${SDL_INCLUDE_DIR}"
  COMMAND echo "SDL2: ${SDL2_INCLUDE_DIRS}"
  #COMMAND echo "SDL: ${SDL_LIBRARY}"
  COMMAND echo "SDL2: ${SDL2_LIBRARIES}"
  COMMAND echo "====================================="
)

ADD_CUSTOM_TARGET(run 
  COMMAND echo "=====================================" 
  WORKING_DIRECTORY bin
  COMMAND echo `pwd`
  COMMAND LD_LIBRARY_PATH=. ./test2
  COMMAND echo "=====================================" 
)
