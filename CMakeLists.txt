PROJECT(TestXmlJoiner)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.10)

INCLUDE(cmake/versions.cmake REQUIRED)
INCLUDE(cmake/compileroptions.cmake REQUIRED)
INCLUDE(cmake/options.cmake REQUIRED)
INCLUDE(cmake/findDependencies.cmake REQUIRED)
INCLUDE(cmake/buildFiles.cmake REQUIRED)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)
#ADD_SUBDIRECTORY(utils)

INCLUDE(cmake/printInfo.cmake REQUIRED)

