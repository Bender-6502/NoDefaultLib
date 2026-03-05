
macro(config_compiler_and_linker)
  if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC|Clang")

    foreach (flag_var
             CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
             CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
             CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
             CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)

        string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
        string(REPLACE "-D_DLL" "" ${flag_var} "${${flag_var}}")
        string(REPLACE "/EHsc" "" ${flag_var} "${${flag_var}}")

    endforeach()
  
    set(CMAKE_CXX_STANDARD 20)

  endif()
endmacro()
