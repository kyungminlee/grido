add_library(grido grido.cc)
target_include_directories(grido PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(grido PUBLIC /opt/homebrew/include)
