#------------------------------------------------------
# Build type
#------------------------------------------------------
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE)
   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES} )
ENDIF()

IF(NOT CMAKE_BUILD_TYPE )
   SET( CMAKE_BUILD_TYPE "Debug" )
ENDIF()

# ----------------------------------------------------------------------------
#   PROJECT CONFIGURATION
#   force some variables that could be defined in the command line to be written to cache
# ----------------------------------------------------------------------------
OPTION(USE_CLANG           "Use Clang compiler"                                        OFF)
OPTION(USE_QT5             "If you prefer to use Qt5 to Qt4"                           OFF)

OPTION(WARNINGS_ARE_ERRORS "Treat warnings as errors"                                  ON)
OPTION(WARNINGS_ANSI_ISO   "Issue all the mandatory diagnostics Listed in C standard"  ON)
OPTION(ENABLE_COVERAGE     "Perform code coverage in HTML"                             OFF)
OPTION(ENABLE_COVERAGE_XML "Perform code coverage in XML for jenkins integration"      OFF)

OPTION(BUILD_SHARED_LIBS   "Build shared libraries"                                    ON)
OPTION(BUILD_TESTS         "Build unitary & integration tests with gtest"              OFF)

# ----------------------------------------------------------------------------
#   Code coverage
# ----------------------------------------------------------------------------
IF (ENABLE_COVERAGE)
   INCLUDE(cmake_stuff/code_coverage.cmake REQUIRED)
ENDIF()
IF (ENABLE_COVERAGE_XML)
   INCLUDE(cmake_stuff/code_coverage_xml.cmake REQUIRED)
ENDIF()

IF (ENABLE_COVERAGE OR ENABLE_COVERAGE_XML)
   ADD_CUSTOM_TARGET(cleanCoverage
      COMMAND find -name *.gcda -delete
      COMMAND find -name *.gcno -delete
      COMMAND rm -rf coverage
      COMMAND rm -f *info*
      COMMAND make clean
      )
ENDIF()

SET(CMAKE_INCLUDE_DIRS_CONFIGCMAKE ${CMAKE_INSTALL_PREFIX}/include      CACHE PATH "Output directory for headers")
SET(CMAKE_LIB_DIRS_CONFIGCMAKE     ${CMAKE_INSTALL_PREFIX}/lib          CACHE PATH "Output directory for libraries")
SET(EXECUTABLE_OUTPUT_PATH         ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH            ${PROJECT_BINARY_DIR}/lib)
