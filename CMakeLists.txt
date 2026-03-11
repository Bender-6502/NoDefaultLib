# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)
project ("NoDefaultLib")

# Include sub-projects.
add_subdirectory ("NoDefaultLib")
add_subdirectory ("NoDefaultLibTests")
add_subdirectory ("NoDefaultLibLibraries/MiniCRT")
#add_subdirectory ("NoDefaultLibLibraries/GoogleTest")
