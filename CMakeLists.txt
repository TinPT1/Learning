cmake_minimum_required(VERSION 3.19.7)
SET(PROJ_NAME "CMakeLearning")
PROJECT(${PROJ_NAME}
         DESCRIPTION "Very nice project"
         LANGUAGES CXX)

set(CMAKE_DEBUG_POSTFIX d)

include_directories(${PROJECT_SOURCE_DIR})
#add_library(applib foo.cpp foo.h)
add_executable(app src/main.cpp)
set_target_properties(app PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
#target_link_libraries(app PUBLIC applib)

#local variable
SET(MY_VARIABLE "Value")

#list
SET(MY_LIST "one;two")

#cache variable shifted as global variable
set(MY_CACHE_VARIABLE "VALUE" CACHE STRING "" FORCE)
mark_as_advanced(MY_CACHE_VARIABLE)

#property
#set_property(TARGET TargetName PROPERTY CXX_STANDARD 11)
#get_property(ResultValue TARGET TargetName PROPERTY CXX_STANDARD)

#function
function(SIMPLE REQUIRED_ARG)
   message(STATUS "Simple argument: ${REQUIRED_ARG}, followed by ${ARGV}")
   set(${REQUIRED_ARG} "From SIMPLE" PARENT_SCOPE)
endfunction()

simple(This)
message("output: ${This}")

function(COMPLEX)
   cmake_parse_arguments(
   COMPLEX_PREFIX
   "SINGLE;ANOTHER"
   "ONE_VALUE;ALSO_ONE_VALUE"
   "MULTI_VALUES"
   ${ARGV}
   )
endfunction()

complex(SINGLE ONE_VALUE value MULTI_VALUES some other values)
