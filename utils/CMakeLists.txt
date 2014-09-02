IF(BUILD_TESTS)

   IF(NOT GTEST_FOUND)
      MESSAGE(WARNING "GTest is not installed in your system so tests can't be compiled")
   ELSE()

   INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
   INCLUDE_DIRECTORIES(SYSTEM ${GTEST_INCLUDE_DIRS})
   LINK_LIBRARIES(${ARGTABLE} ${GTEST_BOTH_LIBRARIES} ${PROJECT_NAME})

   ADD_EXECUTABLE(tests tests_main.cpp)

   ADD_CUSTOM_TARGET(tests_xml COMMAND tests --xml --gtest_output=xml
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
   ENDIF()

ENDIF()


