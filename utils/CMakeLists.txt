if(BUILD_UTILS)

   add_executable(xml_join xml_join.cpp)
   target_link_libraries(xml_join ${PROJECT_NAME})

endif()
