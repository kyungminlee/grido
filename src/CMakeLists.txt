add_library(grido grido.cc)
target_include_directories(grido PUBLIC /opt/homebrew/include)

add_executable(range_test range_test.cc)
target_link_libraries(range_test PUBLIC grido)

add_executable(algorithm_test algorithm_test.cc)
target_link_libraries(algorithm_test PUBLIC grido)

add_executable(multirange_test multirange_test.cc)
target_link_libraries(multirange_test PUBLIC grido)

