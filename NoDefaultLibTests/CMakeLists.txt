project ("NoDefaultLibTests")

# Add source to this project's executable.
add_executable (${PROJECT_NAME}
	"tests/StringTests.cpp"
	"tests/FileStreamTests.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    MiniCRT
	gtest_main
)
