

# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()

message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")

if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()








set(CMAKE_C_COMPILER "C:/Program Files/JetBrains/CLion 2023.2.1/bin/mingw/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/JetBrains/CLion 2023.2.1/bin/mingw/bin/g++.exe")


string(APPEND CONAN_CXX_FLAGS " -m64")
string(APPEND CONAN_C_FLAGS " -m64")
string(APPEND CONAN_SHARED_LINKER_FLAGS " -m64")
string(APPEND CONAN_EXE_LINKER_FLAGS " -m64")



message(STATUS "Conan toolchain: C++ Standard 17 with extensions OFF")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Extra c, cxx, linkflags and defines


if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()

get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "C:/Users/carlo/.conan2/p/b/imgui41f8f659dc338/p/lib" "C:/Users/carlo/.conan2/p/b/glfw15951b9a4e9a5/p/lib" "C:/Users/carlo/.conan2/p/b/glewe2108c4c4b8ea/p/lib" "C:/Users/carlo/.conan2/p/b/assim1e0b242651fb1/p/lib" "C:/Users/carlo/.conan2/p/b/miniz44b0629ec0041/p/lib" "C:/Users/carlo/.conan2/p/b/bzip2e0b66714e23c1/p/lib" "lib" "C:/Users/carlo/.conan2/p/b/pugixb5f14d9ea4300/p/lib" "C:/Users/carlo/.conan2/p/b/kuba-282a1652f7463/p/lib" "C:/Users/carlo/.conan2/p/b/poly278e341adf315a/p/lib" "C:/Users/carlo/.conan2/p/rapid4cabb31a09329/p/lib" "C:/Users/carlo/.conan2/p/b/zlib75ffd3f86e5ba/p/lib" "C:/Users/carlo/.conan2/p/b/dracoe959de8e6ac3f/p/lib" "C:/Users/carlo/.conan2/p/b/clippf5e28f8e851d6/p/lib" "C:/Users/carlo/.conan2/p/b/opendd1ad6de6350a4/p/lib")
list(PREPEND CMAKE_INCLUDE_PATH "C:/Users/carlo/.conan2/p/b/imgui41f8f659dc338/p/include" "C:/Users/carlo/.conan2/p/b/glfw15951b9a4e9a5/p/include" "C:/Users/carlo/.conan2/p/b/glewe2108c4c4b8ea/p/include" "C:/Users/carlo/.conan2/p/glmb8583f8d3b716/p/include" "C:/Users/carlo/.conan2/p/b/assim1e0b242651fb1/p/include" "C:/Users/carlo/.conan2/p/b/miniz44b0629ec0041/p/include" "C:/Users/carlo/.conan2/p/b/miniz44b0629ec0041/p/include/minizip" "C:/Users/carlo/.conan2/p/b/bzip2e0b66714e23c1/p/include" "include" "C:/Users/carlo/.conan2/p/b/pugixb5f14d9ea4300/p/include" "C:/Users/carlo/.conan2/p/b/kuba-282a1652f7463/p/include" "C:/Users/carlo/.conan2/p/b/poly278e341adf315a/p/include" "C:/Users/carlo/.conan2/p/rapid4cabb31a09329/p/include" "C:/Users/carlo/.conan2/p/b/zlib75ffd3f86e5ba/p/include" "C:/Users/carlo/.conan2/p/b/dracoe959de8e6ac3f/p/include" "C:/Users/carlo/.conan2/p/b/clippf5e28f8e851d6/p/include" "C:/Users/carlo/.conan2/p/stbb3237e7146d86/p/include" "C:/Users/carlo/.conan2/p/b/opendd1ad6de6350a4/p/include")



if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};")
endif()




# Variables
# Variables  per configuration


# Preprocessor definitions
# Preprocessor definitions per configuration
