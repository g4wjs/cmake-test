# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
#
# <g4wjs@classdesign.com> modified this file from the original by
# Poul-Henning Kamp <phk@FreeBSD.ORG>. As long as you retain this
# notice you can do whatever you want with this stuff. If we meet some
# day, and you think this stuff is worth it, you can buy me a beer in
# return Bill Somerville.
# ----------------------------------------------------------------------------

cmake_minimum_required (VERSION 2.8.9)

project (cmake-test C CXX)

#
# CMake policies
#
if (POLICY CMP0020)
  cmake_policy (SET CMP0020 NEW) # link to Qt winmain on Windows
endif (POLICY CMP0020)

#
# project sources
#
set (CXXSRCS
  main.cpp
  MainWindow.cpp
  )

set (UISRCS
  MainWindow.ui
  )

#
# versioning
#
include (Version.cmake)

#
# compiler setup
#
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

if (WIN32)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-keep-inline-dllexport")
endif (WIN32)

if (APPLE)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else (APPLE)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif (APPLE)

#
# Qt5 setup
#
find_package (Qt5Widgets REQUIRED)
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON) # pick up generated source files in binary directory

#
# generate sources
#
qt5_wrap_ui (GENUISRCS ${UISRCS})

#
# build product
#
add_executable (cmake-test WIN32 MACOSX_BUNDLE ${CXXSRCS} ${GENUISRCS})
qt5_use_modules (cmake-test Widgets)

#
# install
#
install (TARGETS cmake-test
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}
  )

#
# uninstall support
#
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  @ONLY
  )
add_custom_target (uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  )

#
# packaging
#
set (CPACK_PACKAGE_VENDOR "Class Design Ltd.")
set (CPACK_PACKAGE_VERSION_MAJOR ${cmake-test_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${cmake-test_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${cmake-test_VERSION_PATCH})
set (CPACK_PACKAGE_DESCRIPTION_FILE "${cmake-test_SOURCE_DIR}/cmake-test.txt")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "A CMake & CPack Qt5 Demo")
set (CPACK_PACKAGE_ICON "${cmake-test_SOURCE_DIR}/logo.png")
set (CPACK_PROJECT_CONFIG_FILE "${CMAKE_SOURCE_DIR}/CPackOptions.cmake")
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set (CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README")
set (CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/WELCOME")

include (CPack)