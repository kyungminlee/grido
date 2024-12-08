add_library(grido grido.cc)
target_include_directories(grido PUBLIC /opt/homebrew/include)

add_executable(range_test range_test.cc)
target_link_libraries(range_test PUBLIC grido)
