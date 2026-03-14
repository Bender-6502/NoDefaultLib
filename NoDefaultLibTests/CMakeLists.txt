cmake_minimum_required (VERSION 3.30)
project ("NoDefaultLibTests")

include(FetchContent)

# 1. Declare the dependency
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)

# 2. Make it available (downloads, configures, adds subdirectory)
FetchContent_MakeAvailable(googletest)

# Add source to this project's executable.
add_executable (${PROJECT_NAME}
	"tests/StringTests.cpp"
	"tests/FileStreamTests.cpp"
 "tests/ListTests.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC
    MiniCRT
	gtest_main
)
