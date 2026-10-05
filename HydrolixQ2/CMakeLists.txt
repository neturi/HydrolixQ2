# CMakeList.txt : CMake project for HydrolixQ2, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (HydrolixQ2 "HydrolixQ2.cpp" "HydrolixQ2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HydrolixQ2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
