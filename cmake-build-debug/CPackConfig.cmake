# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "C:/3D_Viewer;C:/3D_Viewer/cmake-build-debug")
set(CPACK_CMAKE_GENERATOR "MinGW Makefiles")
set(CPACK_COMPONENTS_ALL "")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "C:/Users/Requedaddy/AppData/Local/JetBrains/CLion 2023.2.2/bin/cmake/win/x64/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "3D_Viewer built using CMake")
set(CPACK_GENERATOR "ZIP")
set(CPACK_INSTALL_CMAKE_PROJECTS "C:/3D_Viewer/cmake-build-debug;3D_Viewer;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/3D_Viewer")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "3D_Viewer 0.1.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "3D_Viewer 0.1.1")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "C:/Users/Requedaddy/AppData/Local/JetBrains/CLion 2023.2.2/bin/mingw/bin/objcopy.exe")
set(CPACK_OBJDUMP_EXECUTABLE "C:/Users/Requedaddy/AppData/Local/JetBrains/CLion 2023.2.2/bin/mingw/bin/objdump.exe")
set(CPACK_OUTPUT_CONFIG_FILE "C:/3D_Viewer/cmake-build-debug/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Users/Requedaddy/AppData/Local/JetBrains/CLion 2023.2.2/bin/cmake/win/x64/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "3D_Viewer built using CMake")
set(CPACK_PACKAGE_FILE_NAME "3D_Viewer-0.1.1-win64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "3D_Viewer 0.1.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "3D_Viewer 0.1.1")
set(CPACK_PACKAGE_NAME "3D_Viewer")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "0.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PROJECT_VERSION_MAJOR "1")
set(CPACK_PROJECT_VERSION_MINOR "0")
set(CPACK_READELF_EXECUTABLE "C:/Users/Requedaddy/AppData/Local/JetBrains/CLion 2023.2.2/bin/mingw/bin/readelf.exe")
set(CPACK_RESOURCE_FILE_LICENSE "C:/3D_Viewer/License.txt")
set(CPACK_RESOURCE_FILE_README "C:/Users/Requedaddy/AppData/Local/JetBrains/CLion 2023.2.2/bin/cmake/win/x64/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/Users/Requedaddy/AppData/Local/JetBrains/CLion 2023.2.2/bin/cmake/win/x64/share/cmake-3.26/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/3D_Viewer/cmake-build-debug/CPackSourceConfig.cmake")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/3D_Viewer/cmake-build-debug/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
