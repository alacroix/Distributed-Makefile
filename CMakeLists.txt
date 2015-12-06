cmake_minimum_required(VERSION 2.8)
project(distributed_makefile)

# C++ Version Flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out")

# Prefix
if (NOT PREFIX)
    set(PREFIX ${CMAKE_CURRENT_BINARY_DIR})
endif (NOT PREFIX)
set(CMAKE_INSTALL_PREFIX ${PREFIX} CACHE STRING "Installation prefix." FORCE)

if (CXX)
    set(CMAKE_CXX_COMPILER ${CXX})
endif (CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Release or Debug
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif ()

# Detect MPI
set(MPI_LIBS)
find_package(MPI REQUIRED)
if (MPI_C_FOUND AND MPI_CXX_FOUND)
    include_directories(${MPI_C_INCLUDE_PATH})
    include_directories(${MPI_CXX_INCLUDE_PATH})
    set (MPI_LIBS ${MPI_LIBS} ${MPI_C_LIBRARIES})
    set (MPI_LIBS ${MPI_LIBS} ${MPI_CXX_LIBRARIES})
else (MPI_C_FOUND AND MPI_CXX_FOUND)
    message(STATUS "MPI not found.")
endif (MPI_C_FOUND AND MPI_CXX_FOUND)

# Detect OMP
find_package(OpenMP QUIET)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS ${CMAKE_C_CFLAGS} ${OpenMP_C_FLAGS})
    set (CMAKE_CXX_FLAGS ${CMAKE_CXX_CFLAGS} ${OpenMP_CXX_FLAGS})
else (OPENMP_FOUND)
    message(STATUS "OpenMP not found.")
endif (OPENMP_FOUND)

# Detect Boost
find_package(Boost REQUIRED mpi serialization)
if (BOOST_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif(BOOST_FOUND)

# Source files & exec
set(SOURCE_FILES src/main.cpp src/Rule.cpp src/Rule.h src/Parser.cpp src/Parser.h src/Manager.cpp src/Manager.h src/PathUtils.cpp src/PathUtils.h src/QueueDoable.cpp src/QueueDoable.h)
add_executable(distributed_makefile ${SOURCE_FILES})
target_link_libraries(distributed_makefile ${Boost_LIBRARIES} ${MPI_LIBS})

# Print compiler flags
get_directory_property(DirDefs COMPILE_DEFINITIONS)
message(STATUS "COMPILE_DEFINITIONS = ${DirDefs}")
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "C++ Flags: ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}" )
    message(STATUS "C Flags: ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}" )
else()
    message(STATUS "C++ Flags: ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}" )
    message(STATUS "C Flags: ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}" )
endif()