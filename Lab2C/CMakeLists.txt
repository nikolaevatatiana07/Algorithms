add_executable(Lab2CPP task.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME Test1Lab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test1_lab2.txt)
set_property(TEST Test1Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "ABC\\*\\+")

add_test(NAME Test2Lab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2_lab2.txt)
set_property(TEST Test2Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "AB\\+C\\*")

add_test(NAME Test3Lab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3_lab2.txt)
set_property(TEST Test3Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "Error")

add_test(NAME Test4Lab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test4_lab2.txt)
set_property(TEST Test4Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "ABC\\*\\+DE/-")

add_test(NAME Test5Lab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test5_lab2.txt)
set_property(TEST Test5Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "ABCD\\+-\\+")