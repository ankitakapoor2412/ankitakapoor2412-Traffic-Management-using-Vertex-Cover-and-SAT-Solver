cmake_minimum_required(VERSION 2.8)
project(ece650-a3)

## ECE650 Specific configuration start here
## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/run)

# create the main executable
## add additional .cpp files if needed
set (SOURCES ece650-a2.cpp UserInput.cpp ShortestPath.cpp)
add_executable(ece650-a2 ${SOURCES})
set (SOURCES rgen rgen.cpp CoordinateGenerator.cpp CoordinatesValidation.cpp)
add_executable(rgen ${SOURCES})
add_executable(ece650-a3 ece650-a3.cpp )

# create the executable for tests
add_executable(tests test.cpp)
install(PROGRAMS ece650-a1.py InputValidation.py DESTINATION bin)
install(TARGETS rgen ece650-a2 ece650-a3 RUNTIME DESTINATION bin)
