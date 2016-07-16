include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(verification)

add_definitions( -std=c++11 -g)

# add_executable(test1 test1.cpp)
# target_link_libraries(test1 VM)

# add_executable(test2 test2.cpp)
# target_link_libraries(test2 VM)

# INSTALL(TARGETS test.txt test1.txt DESTINATION tests)
