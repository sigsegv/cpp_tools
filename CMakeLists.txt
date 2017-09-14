cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

set(PROJECT_NAME cpp_tools)

project(${PROJECT_NAME} VERSION 0.0.0.1 LANGUAGES CXX)

set(local_settings_file ${CMAKE_SOURCE_DIR}/local_settings.cmake)
if(EXISTS ${local_settings_file})
	include(${local_settings_file})
endif()

if(${APPLE})
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++14)
endif()

#option(BUILD_SAMPLE "Generate Sample Project" ON)
option(BUILD_UNIT_TESTS "Generate Unit Tests Project" ON)

if(BUILD_SAMPLE)
  add_subdirectory(example)
endif()
if(BUILD_UNIT_TESTS)
  add_subdirectory(test)
endif()

#set(STATIC_LIBS)

#file(GLOB HDR *.hpp)
#file(GLOB SRC *.cpp)

#add_executable(${ROSS_PROJECT_NAME} ${SRC} ${HDR})
#target_link_libraries(${ROSS_PROJECT_NAME} ${STATIC_LIBS})
