include(cmake/utils.cmake)
config_compiler_and_linker()

# Add source to this project's executable.
add_executable (${PROJECT_NAME} WIN32
	"src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    MiniCRT
)
