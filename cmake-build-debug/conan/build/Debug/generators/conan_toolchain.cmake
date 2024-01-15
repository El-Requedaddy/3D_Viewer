

# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()

message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")

if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()








set(CMAKE_C_COMPILER "C:/Users/Requedaddy/AppData/Local/JetBrains/CLion 2023.2.2/bin/mingw/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Users/Requedaddy/AppData/Local/JetBrains/CLion 2023.2.2/bin/mingw/bin/g++.exe")


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
list(PREPEND CMAKE_LIBRARY_PATH "C:/Users/Requedaddy/.conan2/p/b/imgui8546bfb0bd167/p/lib" "C:/Users/Requedaddy/.conan2/p/b/glfwcb4fc5973ece6/p/lib" "C:/Users/Requedaddy/.conan2/p/b/glewd04f5c945cc35/p/lib" "C:/Users/Requedaddy/.conan2/p/b/assima06af829737fa/p/lib" "C:/Users/Requedaddy/.conan2/p/b/minizac3c52884bbc4/p/lib" "C:/Users/Requedaddy/.conan2/p/b/bzip2104f6e66968ae/p/lib" "lib" "C:/Users/Requedaddy/.conan2/p/b/pugix9c9b0266e59f7/p/lib" "C:/Users/Requedaddy/.conan2/p/b/kuba-2f67d72086299/p/lib" "C:/Users/Requedaddy/.conan2/p/b/poly242f374bf282e1/p/lib" "C:/Users/Requedaddy/.conan2/p/rapid4cabb31a09329/p/lib" "C:/Users/Requedaddy/.conan2/p/b/zlib91dfc2309db4e/p/lib" "C:/Users/Requedaddy/.conan2/p/b/draco0ca26b2bc0d20/p/lib" "C:/Users/Requedaddy/.conan2/p/b/clipp5f92adfa1519a/p/lib" "lib" "C:/Users/Requedaddy/.conan2/p/b/opend2d652052fa042/p/lib")
list(PREPEND CMAKE_INCLUDE_PATH "C:/Users/Requedaddy/.conan2/p/b/imgui8546bfb0bd167/p/include" "C:/Users/Requedaddy/.conan2/p/b/glfwcb4fc5973ece6/p/include" "C:/Users/Requedaddy/.conan2/p/b/glewd04f5c945cc35/p/include" "C:/Users/Requedaddy/.conan2/p/glmdf97922a12435/p/include" "C:/Users/Requedaddy/.conan2/p/b/assima06af829737fa/p/include" "C:/Users/Requedaddy/.conan2/p/b/minizac3c52884bbc4/p/include" "C:/Users/Requedaddy/.conan2/p/b/minizac3c52884bbc4/p/include/minizip" "C:/Users/Requedaddy/.conan2/p/b/bzip2104f6e66968ae/p/include" "include" "C:/Users/Requedaddy/.conan2/p/b/pugix9c9b0266e59f7/p/include" "C:/Users/Requedaddy/.conan2/p/b/kuba-2f67d72086299/p/include" "C:/Users/Requedaddy/.conan2/p/b/poly242f374bf282e1/p/include" "C:/Users/Requedaddy/.conan2/p/rapid4cabb31a09329/p/include" "C:/Users/Requedaddy/.conan2/p/b/zlib91dfc2309db4e/p/include" "C:/Users/Requedaddy/.conan2/p/b/draco0ca26b2bc0d20/p/include" "C:/Users/Requedaddy/.conan2/p/b/clipp5f92adfa1519a/p/include" "include" "C:/Users/Requedaddy/.conan2/p/b/opend2d652052fa042/p/include")



if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};")
endif()




# Variables
# Variables  per configuration


# Preprocessor definitions
# Preprocessor definitions per configuration
