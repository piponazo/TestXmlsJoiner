if(BUILD_UTILS)
   include_directories(${PROJECT_SOURCE_DIR}/include)

   add_executable(xml_join xml_join.cpp)
   target_link_libraries(xml_join ${PROJECT_NAME} ${ARGTABLE})

endif()
