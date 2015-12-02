cmake_minimum_required(VERSION 3.0.2)
project(distributed_makefile)

# Output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out")

# C++ Version Flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Source files & exec
set(SOURCE_FILES src/main.cpp src/Rule.cpp src/Rule.h src/Parser.cpp src/Parser.h src/Manager.cpp src/Manager.h src/PathUtils.cpp src/PathUtils.h)
add_executable(distributed_makefile ${SOURCE_FILES})

# Packages
find_package(OpenMP REQUIRED)
find_package(Boost REQUIRED)
find_package(MPI REQUIRED)

# OpenMP
if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Boost package
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# MPI
if(MPI_FOUND)
    set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
    set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
    include_directories(MPI_INCLUDE_PATH)
    target_link_libraries(distributed_makefile ${MPI_LIBRARIES})
endif()


