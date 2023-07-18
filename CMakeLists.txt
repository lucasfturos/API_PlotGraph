cmake_minimum_required(VERSION 3.5)  # CMake version check

set(PROJECT_NAME                      # Define all project info
  Plot
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project "Plot"

set(CMAKE_CXX_STANDARD 17)            # Enable c++11 standard

set(PROJECT_HEADER                    # Directory of all header file
  src/ScatterChart/scatter_chart.hpp
  src/DonutChart/donut_chart.hpp
  src/LineChart/line_chart.hpp
  src/BarChart/bar_chart.hpp
  src/PieChart/pie_chart.hpp
)

set(PROJECT_SOURCE                    # Directory of all source file
  src/ScatterChart/scatter_chart.cpp
  src/DonutChart/donut_chart.cpp
  src/LineChart/line_chart.cpp
  src/BarChart/bar_chart.cpp
  src/PieChart/pie_chart.cpp
  src/main.cpp
)

# Source folder location
set(FONT_DIR 
  ${CMAKE_CURRENT_SOURCE_DIR}/font
)

# Browse the font *.ttf inside the font folder
file(GLOB 
  FONT_FILES ${FONT_DIR}/*.ttf
)

# Copy the source to the build directory
file(COPY 
  ${FONT_FILES} DESTINATION ${CMAKE_BINARY_DIR}/font
)

# Add executable target with source and header files listed in PROJECT_HEADER and PROJECT_SOURCE variable
add_executable(${PROJECT_NAME} 
  ${PROJECT_HEADER} 
  ${PROJECT_SOURCE}
)

# Specifies include directories to use when compiling a given target
target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_BINARY_DIR}/font
  PRIVATE src
)

# Specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries(${PROJECT_NAME}
  PRIVATE sfml-graphics
  PRIVATE sfml-window
  PRIVATE sfml-system
)
