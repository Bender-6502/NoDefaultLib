project ("MiniCRT")

include(cmake/utils.cmake)
config_compiler_and_linker()

# Add source to this project's executable.
add_library (${PROJECT_NAME} STATIC
	"src/BasicAllocatorImpl.cpp"
	"src/BasicFileStreamImpl.cpp"
	"src/BasicFileSystemImpl.cpp"
	"src/BasicStringFunctionsImpl.cpp"
 "inc/BasicThread.h" "src/BasicThread.cpp" "MiniCRT/Thread.h" "inc/BasicMutex.h" "MiniCRT/Mutex.h" "src/BasicMutex.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC 
	"inc"
)

target_include_directories(${PROJECT_NAME} INTERFACE
	"."
)
