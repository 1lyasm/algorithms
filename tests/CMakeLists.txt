add_executable(test_dsa test_dsa.cpp)
target_link_libraries(test_dsa lib)
add_test(NAME test_dsa COMMAND test_dsa)