SET(EXTRA_C_FLAGS "")
SET(EXTRA_C_FLAGS_RELEASE "-DNDEBUG")
SET(EXTRA_C_FLAGS_DEBUG "-DDEBUG -O0")

IF (USE_CLANG)
   SET (CMAKE_C_COMPILER_ID            "Clang")
   SET (CMAKE_CXX_COMPILER_ID          "Clang")
   SET (CMAKE_C_COMPILER               "/usr/bin/clang")
   SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")

   SET (CMAKE_C_FLAGS                  "-Wall -std=c99")
   SET (CMAKE_C_FLAGS_DEBUG            "-g")
   SET (CMAKE_C_FLAGS_RELEASE          "-O2")

   SET (CMAKE_CXX_FLAGS                "-Wall")
   SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
   SET (CMAKE_CXX_FLAGS_RELEASE        "-O2")
ENDIF()

IF (USE_ANALYZE)
   SET (CMAKE_C_COMPILER_ID            "ccc-analyzer")
   SET (CMAKE_CXX_COMPILER_ID          "c++-analyzer")
   SET (CMAKE_C_COMPILER               "/usr/share/clang/scan-build/ccc-analyzer")
   SET (CMAKE_CXX_COMPILER             "/usr/share/clang/scan-build/c++-analyzer")

   SET (CMAKE_C_FLAGS                  "-Wall -std=c99")
   SET (CMAKE_C_FLAGS_DEBUG            "-g")
   SET (CMAKE_C_FLAGS_RELEASE          "-O2")

   SET (CMAKE_CXX_FLAGS                "-Wall")
   SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
   SET (CMAKE_CXX_FLAGS_RELEASE        "-O2")
ENDIF()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

   EXECUTE_PROCESS(
   COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
   IF (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
      message(FATAL_ERROR "${PROJECT_NAME} c++11 support requires g++ 4.7 or greater.")
   ENDIF ()

   SET(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wall -Werror=return-type -Wno-long-long -Wno-maybe-uninitialized")

   IF(WARNINGS_ANSI_ISO)
      SET(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wstrict-aliasing=3")
   ELSE()
      SET(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wno-narrowing -Wno-delete-non-virtual-dtor -Wno-unnamed-type-template-args")
   ENDIF()

   # Code Coverage
   IF(ENABLE_COVERAGE OR ENABLE_COVERAGE_XML)
      SET(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} --coverage")
   ENDIF()

   # Extra link libs if the user selects building static libs:
   IF(NOT BUILD_SHARED_LIBS AND CMAKE_COMPILER_IS_GNUCXX)
      SET(LINKER_LIBS ${LINKER_LIBS} stdc++)
   ENDIF()

ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

   IF(NOT EXISTS ${CMAKE_CXX_COMPILER})
      MESSAGE( FATAL_ERROR "Clang++ not found. " )
   ENDIF()

   IF(ENABLE_COVERAGE OR ENABLE_COVERAGE_XML)
      MESSAGE(FATAL_ERROR "Not use clang for generate code coverage. Use gcc. ")
   ENDIF()

ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "c++-analyzer")

   IF(NOT EXISTS ${CMAKE_CXX_COMPILER})
      MESSAGE( FATAL_ERROR "c++-analyzer not found. " )
   ENDIF()

   IF(ENABLE_COVERAGE OR ENABLE_COVERAGE_XML)
      MESSAGE(FATAL_ERROR "Not use c++-analyzer for generate code coverage. Use gcc. ")
   ENDIF()

ENDIF()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "c++-analyzer" )

   IF(WARNINGS_ANSI_ISO)
      SET(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -pedantic -Wcast-align -Wextra")
   ENDIF()

   IF(WARNINGS_ARE_ERRORS)
      SET(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Werror")
   ENDIF()

   SET(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -std=c++11")

ENDIF()

# Add user supplied extra options (optimization, etc...)
# ==========================================================
SET(EXTRA_C_FLAGS "${EXTRA_C_FLAGS}" CACHE INTERNAL "Extra compiler options")
SET(EXTRA_C_FLAGS_RELEASE "${EXTRA_C_FLAGS_RELEASE}" CACHE INTERNAL "Extra compiler options for Release build")
SET(EXTRA_C_FLAGS_DEBUG "${EXTRA_C_FLAGS_DEBUG}" CACHE INTERNAL "Extra compiler options for Debug build")

#combine all "extra" options
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_C_FLAGS}")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${EXTRA_C_FLAGS_DEBUG}")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${EXTRA_C_FLAGS_RELEASE}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_C_FLAGS}")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  ${EXTRA_C_FLAGS_RELEASE}")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${EXTRA_C_FLAGS_DEBUG}")
