###############################################
# Project treemaker
###############################################

#cmake minimum requirement
cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

#Project name and version
project ( treemaker VERSION 1.0.0 LANGUAGES C CXX )

#CMake type
set(CMAKE_BUILD_TYPE Debug)

#External packages
find_package( ROOT COMPONENTS Matrix Hist RIO MathCore Physics ROOTDataFrame TMVA ROOTVecOps)
find_package( lwtnn REQUIRED)

#set run time output directory as bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#Add include directories
include_directories(./src)
include_directories(./include)
include_directories(${lwtnn_INCLUDE_DIRS})
include(${ROOT_USE_FILE})

#add executable
add_executable(treemaker src/main.cxx src/treemaker.cxx)
#link libraries
target_link_libraries(treemaker ${ROOT_LIBRARIES} lwtnn)
