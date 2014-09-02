IF(NOT GTEST_FOUND)

   MESSAGE(WARNING "GTest is not installed in your system so tests can't be compiled")

ELSEIF(BUILD_TESTS)

   INCLUDE_DIRECTORIES(SYSTEM ${GTEST_INCLUDE_DIRS})
   INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
   LINK_LIBRARIES(${ARGTABLE} ${GTEST_BOTH_LIBRARIES} ${PROJECT_NAME})

   FILE(GLOB SRCS "*.cpp")

   ADD_EXECUTABLE(tests ${SRCS})

   ADD_CUSTOM_TARGET(tests_xml COMMAND tests --xml --gtest_output=xml:tests.xml
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

   IF(ENABLE_COVERAGE)
      SETUP_TARGET_FOR_COVERAGE(coverageHtml tests coverage)
   ENDIF()

   IF(ENABLE_COVERAGE_XML)
      SETUP_TARGET_FOR_COVERAGE(coverageXml tests coverageXml --gtest_output=xml:tests.xml)
   ENDIF()

ENDIF()
