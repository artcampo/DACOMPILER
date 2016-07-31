include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(verification)

# add_executable(test1 test1.cpp)
# target_link_libraries(test1 VM)

# add_executable(test2 test2.cpp)
# target_link_libraries(test2 VM)

INSTALL(FILES 
        test1.txt 
        test2.txt 
        test3.txt 
        test4.txt
        DESTINATION tests)